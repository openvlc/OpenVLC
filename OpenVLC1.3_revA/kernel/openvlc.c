/*
 Copyright (c) 2014, IMDEA NETWORKS Institute
 
 This file is part of the OpenVLC's source codes.
 
 OpenVLC's source codes are free: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 OpenVLC's source codes are distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with the source codes of OpenVLC.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <linux/sched.h>
#include <linux/interrupt.h> // mark_bh 
#include <linux/in.h>
#include <linux/netdevice.h>   // struct device, and other headers 
#include <linux/skbuff.h>
#include <linux/in6.h>
#include <linux/delay.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/pci.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <asm/unistd.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <linux/iio/consumer.h>
#include <linux/iio/iio.h>
#include <asm/checksum.h>
#include <linux/kthread.h>
#include <linux/err.h>
#include <linux/wait.h>
#include <linux/timex.h>
#include <linux/clk.h>
#include <linux/pinctrl/consumer.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/module.h>
#include <asm/io.h>		// ioremap
#include <linux/proc_fs.h>
#include <linux/skbuff.h>
#include <linux/ip.h>          
#include <linux/tcp.h>         
#include <linux/if_arp.h>
#include <linux/rslib.h>
#include "openvlc.h"
#define DEVICE_NAME "vlc"
// start for ioctl
#include <linux/fs.h> // required for various structures related to files liked fops. 
#include <linux/semaphore.h>
#include <linux/cdev.h>
// end for ioctl
#include <linux/device.h>         // Header to support the kernel Driver Model



#define MAC 0
#define APP 1

static int mac_or_app = 1;
module_param(mac_or_app, int, 1);
static int block_size = 200;
module_param(block_size, int, 0);

uint16_t par[ECC_LEN];
int ecc_symsize = 8;
int ecc_poly = 0x11d;

// the Reed Solomon control structure 
static struct rs_control *rs_decoder;

// Module params
static int rx = 0;
static int dst_id = 8;
static int self_id = 7;
static int flag_exit = 0;
static int flag_lock = 0;
static int mtu = 1500;
module_param(flag_lock, int, 0);
module_param(self_id, int, 0);
module_param(dst_id, int, 0);
module_param(rx, int, 0);
module_param(mtu, int, 0);

const char *name = "any";

// Tasks
static struct task_struct *task_mac_tx = NULL;
static struct task_struct *task_phy_decoding = NULL;
static struct task_struct *task_frames_pru = NULL;

// For DATA frame
#define DB_BYTE_LEN 2000
#define DB_SYMBOL_LEN 2000*16
static unsigned char data_buffer_byte[DB_BYTE_LEN];
static _Bool data_buffer_symbol[DB_SYMBOL_LEN];
static int data_buffer_byte_len = 0;
static int data_buffer_symbol_len = 0;
static int tx_data_curr_index = 0;

MODULE_AUTHOR("Ander GALISTEO/Diego JUARA");
MODULE_LICENSE("Dual BSD/GPL");

// April 04

enum  state {SENSING, RX, TX, ILLUM, CHM, NONE} ; // Short sensing is implemented in tx state
enum  state phy_state;

/////////////////// PRU variables ///////////////////////////////////

#define PRU_ADDR 0x4A300000
#define PRU0 0x00000000
#define PRU1 0x00002000
#define PRU_SHARED 0x00010000

unsigned int *tx_pru;
unsigned int *rx_pru;

struct net_device *vlc_devs;

struct vlc_packet {
	struct vlc_packet *next;
	struct net_device *dev;
	int	datalen;
	u8 data[2000+10];
};

struct vlc_packet *tx_pkt;
struct vlc_packet *rx_pkt_check_dup;
struct vlc_packet *rx_pkt;

int pool_size = 10;
module_param(pool_size, int, 0);

struct vlc_priv {
	struct net_device_stats stats;
	int status;
	struct vlc_packet *ppool;
	int rx_int_enabled;
	struct vlc_packet *tx_queue; // List of tx packets
	int tx_packetlen;
	u8 *tx_packetdata;
	struct sk_buff *skb;
	spinlock_t lock;
    struct net_device *dev;
};

static struct vlchdr *vlc_hdr(const struct sk_buff *skb)
{
    return (struct vlchdr *) skb_mac_header(skb);
}

int vlc_header(struct sk_buff *skb, struct net_device *dev, unsigned short type,
                const void *daddr, const void *saddr, unsigned len)
{
	struct vlchdr *vlc = (struct vlchdr *)skb_push(skb, VLC_HLEN);

	vlc->h_proto = htons(type);
	memcpy(vlc->h_source, saddr ? saddr : dev->dev_addr, dev->addr_len);
	memcpy(vlc->h_dest,   daddr ? daddr : dev->dev_addr, dev->addr_len);
	vlc->h_dest[MAC_ADDR_LEN-1] ^= 0x01;   /* dest is us xor 1 */
	return (dev->hard_header_len);
}

static const struct header_ops vlc_header_ops= {
    .create  = vlc_header
	//.rebuild = vlc_rebuild_header
};

// Return statistics to the caller
struct net_device_stats *vlc_stats(struct net_device *dev)
{
	struct vlc_priv *priv = netdev_priv(dev);
	return &priv->stats;
}

// Configuration changes (passed on by ifconfig)
int vlc_config(struct net_device *dev, struct ifmap *map)
{
	if (dev->flags & IFF_UP) // can't act on a running interface 
		return -EBUSY;

	// Don't allow changing the I/O address 
	if (map->base_addr != dev->base_addr) {
		printk(KERN_WARNING "snull: Can't change I/O address\n");
		return -EOPNOTSUPP;
	}

	// Allow changing the IRQ 
	if (map->irq != dev->irq) {
		dev->irq = map->irq; // request_irq() is delayed to open-time 
	}

	// ignore other fields 
	return 0;
}

// Ioctl commands
int vlc_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	//printk("ioctl\n");
	return 0;
}


//Buffer/pool management.
struct vlc_packet *vlc_get_tx_buffer(struct net_device *dev)
{
	
	struct vlc_priv *priv = netdev_priv(dev);
	//unsigned long flags;
	struct vlc_packet *pkt;
    if (flag_lock)
        spin_lock_bh(&priv->lock);
	pkt = priv->ppool;
	priv->ppool = pkt->next;
	if (priv->ppool == NULL) {
		printk(KERN_INFO "The MAC layer queue is full!\n");
		netif_stop_queue(dev);
	}
    if (flag_lock)
        spin_unlock_bh(&priv->lock);
    
	return pkt;
}

void vlc_release_buffer(struct vlc_packet *pkt)
{
	//unsigned long flags;
	struct vlc_priv *priv = netdev_priv(pkt->dev);

	if (flag_lock)
        spin_lock_bh(&priv->lock);
	pkt->next = priv->ppool;
	priv->ppool = pkt;
	if (flag_lock)
        spin_unlock_bh(&priv->lock);
	if (netif_queue_stopped(pkt->dev) && pkt->next == NULL && flag_exit == 0)
		netif_wake_queue(pkt->dev);
}


// Departure a packet from the end of the MAC queue (FIFO)
struct vlc_packet *vlc_dequeue_pkt(struct net_device *dev)
{
    //unsigned long flags;
    struct vlc_priv *priv = netdev_priv(dev);
	struct vlc_packet *pkt;
    
    if (flag_lock)
        spin_lock_bh(&priv->lock);
	pkt = priv->tx_queue;
	if (pkt != NULL)
		priv->tx_queue = pkt->next;
	if (flag_lock)
        spin_unlock_bh(&priv->lock);
	printk("Dequeue a packet!\n");
    return pkt;
}

// Add a packet from upper layer to the beginning of the MAC queue
void vlc_enqueue_pkt(struct net_device *dev, struct vlc_packet *pkt)
{
    //unsigned long flags;
	struct vlc_priv *priv = netdev_priv(dev);
    struct vlc_packet *last_pkt; 
    
    /// Fix the misorder packets
    if (flag_lock)
        spin_lock_bh(&priv->lock);
    last_pkt = priv->tx_queue;
    if (last_pkt == NULL) {
        priv->tx_queue = pkt; // Enqueue the new packet
    } else {
        while (last_pkt != NULL && last_pkt->next != NULL) {
            last_pkt = last_pkt->next;
        }
        last_pkt->next = pkt; // Put new the pkt to the end of the queue
    }
    if (flag_lock)
        spin_unlock_bh(&priv->lock);
	printk("Enqueue a packet!\n");
    ///
}

int vlc_tx(struct sk_buff *skb, struct net_device *dev)
{
    struct vlc_packet *tmp_pkt;// TODO Commented so that it doesn't return!

    dev->trans_start = jiffies; //8.7 linux version
	//netif_trans_update(dev); // 9.4 linux version
    tmp_pkt = vlc_get_tx_buffer(dev);
    tmp_pkt->next = NULL; 
    tmp_pkt->datalen = skb->len;
    memcpy(tmp_pkt->data, skb->data, skb->len);
    vlc_enqueue_pkt(dev, tmp_pkt);
    dev_kfree_skb(skb);
	return 0; // Our simple device can not fail 
}

int vlc_release(struct net_device *dev)
{
	netif_stop_queue(dev); // can't transmit any more 
	return 0;
}

int vlc_open(struct net_device *dev)
{
	memcpy(dev->dev_addr, "\0\2", MAC_ADDR_LEN);
    netif_start_queue(dev);
	return 0;
}

static const struct net_device_ops vlc_netdev_ops = {
	.ndo_open            = vlc_open,
	.ndo_stop            = vlc_release,
	.ndo_start_xmit      = vlc_tx,
	.ndo_do_ioctl        = vlc_ioctl,
	.ndo_set_config      = vlc_config,
	.ndo_get_stats       = vlc_stats,
};

// Setup VLC network device
void vlc_setup(struct net_device *dev)
{
    dev->hard_header_len = VLC_HLEN;
    dev->mtu = mtu;
    dev->tx_queue_len = 100;
    dev->priv_flags |= IFF_TX_SKB_SHARING;
}


//Enable and disable receive interrupts.
static void vlc_rx_ints(struct net_device *dev, int enable)
{
	struct vlc_priv *priv = netdev_priv(dev);
	priv->rx_int_enabled = enable;
}


//Set up a device's packet pool.
void vlc_setup_pool(struct net_device *dev)
{
	struct vlc_priv *priv = netdev_priv(dev);
	int i;
	struct vlc_packet *pkt;

	priv->ppool = NULL;
	for (i = 0; i < pool_size; i++) {
		pkt = kmalloc (sizeof (struct vlc_packet), GFP_KERNEL);
		if (pkt == NULL) {
			printk (KERN_NOTICE "Ran out of memory allocating packet pool\n");
			return;
		}
		pkt->dev = dev;
		pkt->next = priv->ppool;
		priv->ppool = pkt;
	}
}

__be16 vlc_type_trans(struct sk_buff *skb, struct net_device *dev)
{
    struct vlchdr *vlc;
    skb->dev = dev;
    skb_reset_mac_header(skb);
    skb_pull_inline(skb, VLC_HLEN);
    vlc = vlc_hdr(skb);

    if (ntohs(vlc->h_proto) >= 1536)
        return vlc->h_proto;

    return htons(VLC_P_DEFAULT);
}

static void construct_frame_header(char* buffer, int buffer_len, int payload_len)
{
    int i;
    //unsigned short crc;

    for (i=0; i<PREAMBLE_LEN; i++)
        buffer[i] = 0xaa; // Preamble
    // SFD
	buffer[1]= 0xae; // Added to synchronize correctly with the frame
    buffer[PREAMBLE_LEN] = 0xa3; //10100011 0110011010100101
    // Length of payload
    buffer[PREAMBLE_LEN+1] = (unsigned char) ((payload_len>>8) & 0xff);
    buffer[PREAMBLE_LEN+2] = (unsigned char) (payload_len & 0xff);
    // Destination address
    buffer[PREAMBLE_LEN+3] = (unsigned char) ((dst_id>>8) & 0xff);
    buffer[PREAMBLE_LEN+4] = (unsigned char) (dst_id & 0xff);
    // Source address
    buffer[PREAMBLE_LEN+5] = (unsigned char) ((self_id>>8) & 0xff);
    buffer[PREAMBLE_LEN+6] = (unsigned char) (self_id & 0xff);
    // CRC
    //crc = crc16(buffer+PREAMBLE_LEN+SFD_LEN, MAC_HDR_LEN+payload_len);
    //buffer[buffer_len-2] = (char) ((0xff00&crc)>>8); // CRC byte 1
	//buffer[buffer_len-1] = (char) ((0x00ff&crc)); // CRC byte 2
}

static void OOK_with_Manchester_RLL(char *buffer_before_coding,
    _Bool *buffer_after_coding, int len_before_coding)
{
    int byte_index, symbol_index = 0;
    unsigned char curr_byte, mask;

    // Convert the preamble -- OOK w/o Manchester RLL code
    for (byte_index=0; byte_index<PREAMBLE_LEN; byte_index++) {
        mask = 0x80;
        curr_byte = buffer_before_coding[byte_index] & 0xff;
        while (mask) {
            buffer_after_coding[symbol_index++] = (_Bool) (curr_byte & mask);
            mask >>= 1;
        }
    }
    // Convert the parts after the preamble -- OOK w Manchester RLL code
    for (byte_index=PREAMBLE_LEN; byte_index<len_before_coding; byte_index++) {
        mask = 0x80;
        curr_byte = buffer_before_coding[byte_index] & 0xff;
        while (mask) {
            if ((_Bool) (curr_byte & mask)) { // Bit 1 -- LOW-HIGH
                buffer_after_coding[symbol_index++] = false;
                buffer_after_coding[symbol_index++] = true;
            } else { // Bit 0 -- HIGH-LOW
                buffer_after_coding[symbol_index++] = true;
                buffer_after_coding[symbol_index++] = false;
            }
            mask >>= 1;
        }
    }
}

static int write_to_pru(_Bool *symbols_to_send, int symbol_length)
{
	unsigned int mask = 0x80000000, actual_value = 0;
	int ind_pru = 1, i = 0;
	
	while(i<symbol_length)
	{
		if(symbols_to_send[i])
			actual_value += mask;
		mask = mask >> 1;
		if((mask==0)||(i==(symbol_length-1)))
		{
			tx_pru[ind_pru++]=actual_value;
			//printk("%x",actual_value);
			
			/*mask = 0x80000000;
			while(mask!=0)
			{
				if(mask&actual_value)
				{
					printk("1");
				}else{
					printk("0");
				}
				mask = mask >> 1;
			}*/
			actual_value = 0;
			mask = 0x80000000;
		}
		i++;
	}
	tx_pru[0]=data_buffer_symbol_len;
	return ind_pru-1;
}

static void generate_DATA_frame(struct vlc_packet *pkt)
{
    //printk("VLC: Generating DATA frame\n");
	int i, payload_len, index_block, encoded_len, num_of_blocks = 0, symbol_last_index = 0, group_32bit = 0;
    payload_len = pkt->datalen-(MAC_HDR_LEN-OCTET_LEN);
    encoded_len = payload_len+2*MAC_ADDR_LEN+PROTOCOL_LEN;
    // Calculate the number of blocks
    if (encoded_len % block_size)
        num_of_blocks = encoded_len / block_size + 1;
    else
        num_of_blocks = encoded_len / block_size;
        
    data_buffer_byte_len = FRAME_LEN_WO_PAYLOAD + payload_len + ECC_LEN*(num_of_blocks-1);
    memset (data_buffer_byte, 0, sizeof (unsigned char) * data_buffer_byte_len);
    data_buffer_symbol_len = (data_buffer_byte_len-PREAMBLE_LEN)*8*2 + PREAMBLE_LEN*8 + 1; // Send a BIT more, why? -- Avoid phy error
	
	if (data_buffer_byte==NULL || data_buffer_symbol==NULL) {
        printk ("Ran out of memory generating new frames.\n");
        return;
    }
    // Construct a new data frame
    memcpy(data_buffer_byte+PREAMBLE_LEN+SFD_LEN+OCTET_LEN, pkt->data, pkt->datalen); // Copy the payload
    vlc_release_buffer(pkt); // Return the buffer to the pool
    construct_frame_header(data_buffer_byte, data_buffer_byte_len, data_buffer_symbol_len);//construct_frame_header(data_buffer_byte, data_buffer_byte_len, payload_len);
    
    /// Encode the blocks of a frame
    for (index_block = 0; index_block < num_of_blocks; index_block++) {
        for (i = 0; i < ECC_LEN; i++)
            par[i] = 0;
        if (index_block < num_of_blocks-1) {
            encode_rs8(rs_decoder, 
                    data_buffer_byte+PREAMBLE_LEN+SFD_LEN+OCTET_LEN+index_block*block_size, 
                    block_size, par, 0);
        } else {
            encode_rs8(rs_decoder, 
                    data_buffer_byte+PREAMBLE_LEN+SFD_LEN+OCTET_LEN+index_block*block_size,
                    encoded_len%block_size, par, 0);
        }
        for (i = 0; i < ECC_LEN; i++)
            data_buffer_byte[FRAME_LEN_WO_PAYLOAD+payload_len+(index_block-1)*ECC_LEN+i] = par[i];
    }
    //Show data after coding
	/*for(i = 7;i<=data_buffer_byte_len;i++)
	{
		int mask = 0x00000080;
		unsigned int last = data_buffer_byte[i];
		//printk("%x",last);
		while(mask!=0)
		{
			if(mask&last)
			{
				printk("1");
			}else{
				printk("0");
			}
			mask = mask >> 1;
		}
		//printk("Data val %d\n",rx_data[i+2]);
	}*/
	//printk("\n\n");
    // Encoding the frame
    OOK_with_Manchester_RLL(data_buffer_byte, data_buffer_symbol, data_buffer_byte_len);
    tx_data_curr_index = data_buffer_symbol_len;
	//printk("VLC-> Data current index: %d\n",data_buffer_symbol_len);
	group_32bit = write_to_pru(data_buffer_symbol, tx_data_curr_index);
}

static int mac_tx(void *data)
{
    struct vlc_priv *priv = netdev_priv(vlc_devs);
	int backoff_timer = 0;
    
start: 
    for (; ;) {
		if (kthread_should_stop()) {
            goto ret;
        }
		if(phy_state == TX) {
			if (mac_or_app == APP) {
				if ((!priv->tx_queue) | (tx_pru[0]!=0)) {
					usleep_range(20,50);
					goto start;
				}
				else{
				tx_pkt = vlc_dequeue_pkt(vlc_devs);
				/// Transmit the packet
				generate_DATA_frame(tx_pkt); // Generate MAC frame
				}
			}else if (mac_or_app == MAC) {
			}
		}
    }
ret:
    printk("\n=======EXIT mac_tx=======\n");
    return 0;
}
 
 //Receive a packet: retrieve, encapsulate and pass over to upper levels
void mac_rx(struct net_device *dev, struct vlc_packet *pkt)
{
	struct sk_buff *skb;
	struct vlc_priv *priv = netdev_priv(dev);

	skb = dev_alloc_skb(pkt->datalen + 2);
	if (!skb) {
		if (printk_ratelimit())
			printk(KERN_NOTICE "snull rx: low on mem - packet dropped\n");
		priv->stats.rx_dropped++;
		goto out;
	}
	skb_reserve(skb, 2); // align IP on 16B boundary 
	memcpy(skb_put(skb, pkt->datalen), pkt->data, pkt->datalen);

	// Write metadata, and then pass to the receive level 
	skb->dev = dev;
	skb->protocol = vlc_type_trans(skb, dev);
	skb->ip_summed = CHECKSUM_UNNECESSARY; // don't check it 
	priv->stats.tx_packets++;
	priv->stats.tx_bytes += pkt->datalen;
	netif_rx(skb);
	//kfree(pkt);
  out:
	return;
}

static int cmp_packets(char *pkt_1, char *pkt_2, int len)
{
    int i = 0;
    for (i=0; i<len; i++) {
        if (pkt_1[i] != pkt_2[i])
            return 1; // Packets are not equal
    }
    return 0; // Packets are equal
}

static void get_the_data_rx(char * rx_data)
{
	uint16_t par_rx[ECC_LEN];
	struct vlc_priv *priv = netdev_priv(vlc_devs);
	unsigned int payload_len_rx = ((rx_data[0] & 0xff) << 8) | (rx_data[1] & 0xff);
	int encoded_len = payload_len_rx+2*MAC_ADDR_LEN+PROTOCOL_LEN;
	int num_of_blocks;
	int i,index_block, num_err=0;
	int j = OCTET_LEN+2*MAC_ADDR_LEN+PROTOCOL_LEN+payload_len_rx;
    int total_num_err = 0;
	
	// Calculate the number of blocks
    if (encoded_len % block_size)
        num_of_blocks = encoded_len / block_size + 1;
    else
        num_of_blocks = encoded_len / block_size;
	//printk("payload_len_rx=%d\n",payload_len_rx);
	//return;
	
	for (index_block=0; index_block < num_of_blocks; index_block++) {
        for (i = 0; i < ECC_LEN; i++) {
            par_rx[i] = rx_data[j+index_block*ECC_LEN+i];
            //printk(" %02x", par[i]);
        }
		
		if (index_block < num_of_blocks-1) {
            num_err = decode_rs8(rs_decoder, rx_data+OCTET_LEN+index_block*block_size, 
                par_rx, block_size, NULL, 0, NULL, 0, NULL);
        } else { // The last block
            num_err = decode_rs8(rs_decoder, rx_data+OCTET_LEN+index_block*block_size, 
                par_rx, encoded_len % block_size, NULL, 0, NULL, 0, NULL);
        }
        if (num_err < 0) {
            printk("*** ECC error. ***\n");
            //f_adjust_slot = 1;
            goto end;
        }
        total_num_err += num_err;
	}
	if (total_num_err > 0) {
        //printk("*** Has corrected %d error(s) *** ", total_num_err);
    }
	if (payload_len_rx>0) { // Data frame
        if (mac_or_app == APP) {// To upper layer
            //rx_pkt = kmalloc (sizeof (struct vlc_packet), GFP_KERNEL);
            rx_pkt->datalen = MAC_HDR_LEN-OCTET_LEN+payload_len_rx;
            // Copy the received data (omit the datalen octet)
            memcpy(rx_pkt->data, rx_data+OCTET_LEN, rx_pkt->datalen);
			if (cmp_packets(rx_pkt->data,rx_pkt_check_dup->data,rx_pkt->datalen)) {
                // Frist copy the packet; the rx_pkt will be released in max_rx
                memcpy(rx_pkt_check_dup->data, rx_pkt->data, rx_pkt->datalen);
                rx_pkt_check_dup->datalen = rx_pkt->datalen;
                mac_rx(vlc_devs, rx_pkt);
                //printk("Sent to the Internet layer.\n");
                priv->stats.rx_packets++;
                priv->stats.rx_bytes += rx_pkt->datalen;/**/
            }
			//else printk("Repeated packet\n");
		}
	}
end:
	return;
}

static int phy_decoding(void *data)
{
	
	char rx_data[2000];
	int symbol_len,byte_len,thelen1,thelen2,numofblocks, len_bit, group_32bit, rest_32bit, j = 0;
	int i=0;
	unsigned int last, current_reg, value, bits, l, mask;
		
	for (; ;) {
		
		if(rx_pru[0] != 0){
			
			
			symbol_len = rx_pru[1];
			//printk("Symbols received : %d\n",rx_pru[1]);

			if((symbol_len > 32000) || (symbol_len < 200)) // To avoid false frames
			{
				rx_pru[0] = 0;
				rx_pru[1] = 0;
				goto payload_error;
			} 
			
			byte_len = ((symbol_len-1-32)/16)+3;
			len_bit = ((symbol_len-81)/2); // subtract 73 = 24 (preamble) + 16 (SFD) + 32 (length) + 1 (added at TX)
			group_32bit = (len_bit+31)/32; // add 31 to round up
			rest_32bit = len_bit%(32);
			
			j=1;
			while(j<1000){//todo!
				numofblocks=j;
				thelen1=(byte_len-28)-16*(j-1);
				if (thelen1%200) numofblocks=(thelen1+6)/200 +1;
				else numofblocks=(thelen1+6)/200;
				if (numofblocks==j) break;
				j++;
			}
			
			if((thelen1>mtu)||(thelen1<0)) // To avoid false frames
			{
				rx_pru[0] = 0;
				rx_pru[1] = 0;
				goto payload_error;
			} 
			rx_data[0] = ((thelen1 >> 8) & 0xFF);
			rx_data[1] = (thelen1 & 0xFF);
			
			
			//printk("Payload %d\n", thelen1);
			
			memcpy(&rx_data[2],&rx_pru[2],group_32bit*sizeof(unsigned int)); // 
			
			//Show data before decoding
			/*for(i = 2;i<group_32bit*sizeof(unsigned int);i++)
			{
				mask = 0x00000080;
				last = rx_data[i];
				while(mask!=0)
				{
					if(mask&last)
					{
						printk("1");
					}else{
						printk("0");
					}
					mask = mask >> 1;
				}
			}*/
			//printk("\n\n");
			
			rx_pru[0] = 0;
			get_the_data_rx(rx_data);
			
		}else{
			payload_error:
			usleep_range(20,50);
		}
		
		error:
		if (kthread_should_stop())
			goto ret;
	}
	ret:
    printk("\n=======EXIT phy_decoding=======\n");
    return 0;
}



void vlc_init(struct net_device *dev)
{
	struct vlc_priv *priv;

    dev->addr_len = MAC_ADDR_LEN;
    dev->type = ARPHRD_LOOPBACK ;  // ARPHRD_IEEE802154
	vlc_setup(dev); // assign some of the fields 
	dev->netdev_ops = &vlc_netdev_ops;
	dev->header_ops = &vlc_header_ops;
	// keep the default flags, just add NOARP 
	dev->flags           |= IFF_NOARP;
	dev->features        |= NETIF_F_HW_CSUM;
	
	priv = netdev_priv(dev);
	memset(priv, 0, sizeof(struct vlc_priv));
	
	if (mac_or_app == APP) {
        vlc_rx_ints(dev, 1);		/* enable receive interrupts */
        tx_pkt = kmalloc (sizeof (struct vlc_packet), GFP_KERNEL);
        rx_pkt = kmalloc (sizeof (struct vlc_packet), GFP_KERNEL);
        rx_pkt_check_dup = kmalloc (sizeof (struct vlc_packet), GFP_KERNEL);
        if (tx_pkt==NULL || rx_pkt_check_dup==NULL || rx_pkt==NULL) {
            printk (KERN_NOTICE "Ran out of memory allocating packet pool\n");
            return ;
        }
        rx_pkt_check_dup->datalen = 0;
        vlc_setup_pool(dev);
        priv->tx_queue = NULL;
        flag_exit = 0;
    }
}

void vlc_teardown_pool(struct net_device *dev)
{
	struct vlc_priv *priv = netdev_priv(dev);
	struct vlc_packet *pkt;
    //unsigned long flags;

	while ((pkt = priv->ppool)) {
		priv->ppool = pkt->next;
		if (pkt) kfree (pkt);
		/* FIXME - in-flight packets ? */
	}
}

void vlc_cleanup(void)
{
	struct vlc_packet *pkt;
    struct vlc_priv *priv = netdev_priv(vlc_devs);
	int ret;
	flag_exit = 1;
    netif_stop_queue(vlc_devs);
	
	// Clean the threads
    if (task_mac_tx) {
        ret = kthread_stop(task_mac_tx);
		if(!ret)
			printk(KERN_INFO "Thread stopped\n");
        task_mac_tx = NULL;
    }
	if (task_phy_decoding) {
        ret = kthread_stop(task_phy_decoding);
		if(!ret)
			printk(KERN_INFO "Thread stopped\n");
       task_phy_decoding = NULL;
    }
	
	
	///////////// Unmap memory for communicating with PRU ///////////
	memunmap(tx_pru);
	memunmap(rx_pru);
	printk("Memory unmapped correctly\n");
	
	//Clean devices
	if (vlc_devs) {
        if (mac_or_app == APP) {
            printk("Cleaning the pool\n");
			
			while(priv->tx_queue) {
                pkt = vlc_dequeue_pkt(vlc_devs);
                vlc_release_buffer(pkt);
            }
			
            vlc_teardown_pool(vlc_devs);
            kfree(rx_pkt);
            kfree(rx_pkt_check_dup);
            kfree(tx_pkt);
        }
        printk("unregister the devs\n");
        unregister_netdev(vlc_devs);
          
		// Free the network device
        printk("Free the devs\n");
        free_netdev(vlc_devs);
    }
	// Free the reed solomon resources
    if (rs_decoder) {
        free_rs(rs_decoder);
    }
	printk(KERN_INFO "EBBChar: Goodbye from the LKM!\n");
	
	return 0;
}


int vlc_init_module(void)
{
	int ret = -ENOMEM;
	printk("Initializing the VLC module...\n");
	phy_state = TX;
	
	///////////// Map memory for communicating with PRU /////////////
	
	rx_pru = memremap(PRU_ADDR+PRU0, 0x10000 ,MEMREMAP_WT);
	tx_pru = memremap(PRU_ADDR+PRU1, 0x10000 ,MEMREMAP_WT);
	printk("Memory mapped correctly: %x\n",tx_pru);
	printk("Memory mapped correctly: %x\n",rx_pru);
	
	/// Create the device and register it
	vlc_devs = alloc_netdev(sizeof(struct vlc_priv), "vlc0", NET_NAME_UNKNOWN, vlc_init);
	if (vlc_devs == NULL)
		goto out;
	ret = register_netdev(vlc_devs);
    if (ret)
        printk("VLC: error registering device \"%s\"\n", vlc_devs->name);
	else printk("VLC: Device registered!\n");
	
	// Create the TX and RX threads
	task_mac_tx = kthread_run(mac_tx,"TX thread","VLC_TX");
	if (IS_ERR(task_mac_tx)){
		printk("Unable to start kernel threads. \n");
		ret= PTR_ERR(task_phy_decoding);
		task_mac_tx = NULL;
		task_phy_decoding = NULL;
		goto out;
	}
		
	task_phy_decoding = kthread_run(phy_decoding,"RX thread","VLC_RX");
    if (IS_ERR(task_phy_decoding)){
        printk("Unable to start kernel threads. \n");
        ret= PTR_ERR(task_phy_decoding);
        task_mac_tx = NULL;
        task_phy_decoding = NULL;
        goto out;
    }else printk("Started Kernel Threads! \n");
	
	// Init the RS coding
	rs_decoder = init_rs(ecc_symsize, ecc_poly, 0, 1, ECC_LEN); // 0---FCR
    if (!rs_decoder) {
        printk(KERN_ERR "Could not create a RS decoder\n");
        ret = -ENOMEM;
        goto out;
    }
	
	out:
    printk("------EXIT vlc_init_module------\n");
	if (ret)
		vlc_cleanup();

	return ret;
}

module_init(vlc_init_module);
module_exit(vlc_cleanup);