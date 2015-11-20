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
#include <linux/interrupt.h> /* mark_bh */
#include <linux/in.h>
#include <linux/netdevice.h>   /* struct device, and other headers */
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
#include <asm/system.h>
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
#include <rtdm/rtdm_driver.h>
#include <asm/io.h>		// ioremap

#include <linux/proc_fs.h>

#include <linux/skbuff.h>
#include <linux/ip.h>          /* struct iphdr */
#include <linux/tcp.h>         /* struct tcphdr */
#include <linux/if_arp.h>
#include <linux/rslib.h>

#include "openvlc.h"
#define DEVICE_NAME "vlc"

MODULE_AUTHOR("Qing WANG");
MODULE_LICENSE("Dual BSD/GPL");

volatile void* gpio1;
volatile void* gpio2;

#define MAC 0
#define APP 1
static int mac_or_app = 0;
module_param(mac_or_app, int, 0);

static int block_size = 200;
module_param(block_size, int, 0);

uint16_t par[ECC_LEN];
int ecc_symsize = 8;
int ecc_poly = 0x11d;

/* the Reed Solomon control structure */
static struct rs_control *rs_decoder;

// Timer: used to trigger sending/receiving symbols
static rtdm_timer_t phy_timer;
static _Bool f_adjust_slot = 0;

#define MAX_RETRANSMISSION  0 // At most tx 4 times
static int cnt_retransmission = 0;
static _Bool f_re_tx = 0;

static int frq = 50; // Unit: K
static int tx = 0;
static int rx = 0;
static int dst_id = 8;
static int self_id = 7;

static int tx_len = 20;
static int rx_len = 1;
static int mode = 0;
static int threshold = 5;
static int show_msg = 0;
static int flag_exit = 0;
static int flag_lock = 0;
module_param(flag_lock, int, 0);

static int mtu = 1200;

static int cnt_detection_bit = 0;
#define MAX_DETECTION_BIT 10

module_param(self_id, int, 0);
module_param(dst_id, int, 0);
module_param(tx, int, 0);
module_param(rx, int, 0);
module_param(frq, int, 0);
module_param(rx_len, int, 0);
module_param(tx_len, int, 0);
module_param(mode, int, 0);
module_param(threshold, int, 0);
module_param(show_msg, int, 0);
module_param(mtu, int, 0);


// Qing - May 2, 2015
//static int pd_as_rx = 0;
//module_param(pd_as_rx, int, 0);
static int hpl = 0;
module_param(hpl, int, 0);
static int bit_led_anode = BIT_LED_ANODE;

// May 28, 2015
struct proc_dir_entry *vlc_dir, *tx_device, *rx_device;
static int rx_device_value = 0;
static int tx_device_value = 0;

const char *name = "any";

static struct task_struct *task_mac_tx = NULL;
static struct task_struct *task_phy_decoding = NULL;

#define ACK_LEN 1

static _Bool f_ready_to_tx = 0;
static _Bool f_rx_whole_preamble = 0;
static _Bool f_rx_one_preamble = 0;

#define RX_BUFFER_SIZE 10000
static int rx_buffer[RX_BUFFER_SIZE] = {0};
static int rx_in_index = 0;
static int rx_out_index = 0;
//static char *rx_data = NULL;
#define RX_DATA_LEN 2000
static char rx_data[RX_DATA_LEN]; // Length > MAC_HDR_LEN+maxpayload+rs_code;

//static int *rx_data_symbol = NULL;
static int tmp_symbol_index = 0;
static int rx_in_val = 0;

// For DATA frame
//static unsigned char* data_buffer_byte = NULL;
//static _Bool* data_buffer_symbol = NULL;
#define DB_BYTE_LEN 2000
#define DB_SYMBOL_LEN 2000*16
static unsigned char data_buffer_byte[DB_BYTE_LEN];
static _Bool data_buffer_symbol[DB_SYMBOL_LEN];

static int data_buffer_byte_len = 0;
static int data_buffer_symbol_len = 0;
static int tx_data_curr_index = 0;
// For ACK frame
//static char* ack_buffer_byte = NULL;
//static _Bool* ack_buffer_symbol = NULL;
#define ACK_BYTE_LEN 50
#define ACK_SYMBOL_LEN 50*16
static char ack_buffer_byte[ACK_BYTE_LEN];
static _Bool ack_buffer_symbol[ACK_SYMBOL_LEN];

static int ack_buffer_byte_len = 0;
static int ack_buffer_symbol_len = 0;
static int tx_ack_curr_index = 0;

// Feb. 25, 2014
static int decoding_sleep_slot = 1;

uint32_t slot_ns;

// May 27, 2015
static int adc_ch = 0;
module_param(adc_ch, int, 0);
#define RX_FROM_LED 0x00 // channel 0
#define RX_FROM_PD 0x01 // channel 1
static int prev_hpl = 0;

static int bit_clc = 1<<BIT_CLC;

// April 04

enum {SENSING, RX, TX} phy_state; // Short sensing is implemented in tx state

#define LONG_SENSING_SYMBOLS 8
static int sensing_buffer[LONG_SENSING_SYMBOLS] = {0};
static int index_long_sensing = 0;
static int avg_val_from_sensing = 0;
static int min_threshold = 10; // Pre-defined minimal threshold between ON and OFF

static int CW = 0; // Contention window
static int CW_min = 4; // Minimal contention window
static int CW_max = 16; // Maximal contention window

static int ACK_TIMEOUT =2*100*8*2; // Ack length is 10 bytes: times*bytes*bits_per_byte*manchester
static _Bool f_ready_to_tx_ack = 0;
static _Bool f_wait_for_ack = 0;
static int index_ack_timeout = 0;
static _Bool f_received_len = false;
static _Bool f_received_ack = 0;

static _Bool f_dropped_frame = 0;

// The device
struct net_device *vlc_devs;

// This structure is private to each device. It is used to pass
// packets in and out, so there is place for a packet
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

void __aeabi_d2uiz(void){}
void __aeabi_ddiv(void){}
void __aeabi_i2d(void){}

static struct vlchdr *vlc_hdr(const struct sk_buff *skb)
{
    return (struct vlchdr *) skb_mac_header(skb);
}

/*
 * A structure representing an in-flight packet.
 */
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




//static void vlc_tx_timeout(struct net_device *dev);
static void (*vlc_interrupt)(int, void *, struct pt_regs *);

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


/*
 * Set up a device's packet pool.
 */
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

void vlc_teardown_pool(struct net_device *dev)
{
	struct vlc_priv *priv = netdev_priv(dev);
	struct vlc_packet *pkt;
    //unsigned long flags;

    //spin_lock_bh(&priv->lock);
	while ((pkt = priv->ppool)) {
		priv->ppool = pkt->next;
		if (pkt) kfree (pkt);
		/* FIXME - in-flight packets ? */
	}
    //spin_unlock_bh(&priv->lock);
}

/*
 * Buffer/pool management.
 */
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
		//printk (KERN_INFO "The MAC layer queue is full!\n");
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

// Add a packet from upper layer to the beginning of the MAC queue
void vlc_enqueue_pkt(struct net_device *dev, struct vlc_packet *pkt)
{
    //unsigned long flags;
	struct vlc_priv *priv = netdev_priv(dev);
    struct vlc_packet *last_pkt; 
    
    //spin_lock_bh(&priv->lock, flags);
	//pkt->next = priv->tx_queue;  /* FIXME - misorders packets */
	//priv->tx_queue = pkt;
    //spin_unlock_bh(&priv->lock, flags);
    
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
    ///
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
    return pkt;
}

/*
 * Enable and disable receive interrupts.
 */
static void vlc_rx_ints(struct net_device *dev, int enable)
{
	struct vlc_priv *priv = netdev_priv(dev);
	priv->rx_int_enabled = enable;
}

// Switch the LED to TX mode
static void switch_led_to_tx(void)
{
    gpio_set_value(GPIO_LED_CATHODE, GPIOF_INIT_LOW);
    gpio_set_value(GPIO_BUFFER_CONTROL, GPIOF_INIT_LOW);
}

// Switch the LED to RX mode
static void switch_led_to_rx(void)
{
    gpio_set_value(GPIO_LED_ANODE, GPIOF_INIT_LOW);
    gpio_set_value(GPIO_BUFFER_CONTROL, GPIOF_INIT_HIGH);
}

// Switch the TX
static void switch_tx(void)
{
    //if (prev_hpl != hpl) {
        //writel(1<<bit_led_anode, gpio2+CLEAR_OFFSET);
        //prev_hpl = hpl;
    //}
    if (hpl == 1) {
        bit_led_anode = BIT_H_POWER_LED; // High-power LED as TX
        gpio_direction_output(GPIO_LED_OR_PD, GPIOF_INIT_LOW); // PD as RX
        gpio_direction_output(GPIO_LED_ANODE, GPIOF_INIT_LOW); // PD as RX
        //writel(1<<BIT_LED_ANODE, gpio2+CLEAR_OFFSET); // Clear the low-power LED
    } else { // LED
        bit_led_anode = BIT_LED_ANODE; // LED as TX
        gpio_direction_output(GPIO_LED_OR_PD, GPIOF_INIT_HIGH); // LED as RX  
        gpio_direction_output(GPIO_H_POWER_LED, GPIOF_INIT_LOW); // PD as RX
        //writel(1<<BIT_H_POWER_LED, gpio2+CLEAR_OFFSET); // Clear the HIGH-power LED
    }
}

#define SPI_DELAY_CNT 10
// Delay in terms of count
static void inline delay_n_NOP(void)
{
    int i;
    for(i=SPI_DELAY_CNT; i>0; i--) 
        ;
}

// Write SFD and channel ID to the ADC
static void SPI_write_sfd_and_ch(void)
{
    //unsigned char write_byte = 0x18; // 0001 1000  channel 0 of the ADC
    unsigned char write_byte = 0x18 + adc_ch; // 0001 1000  channel 0 of the AD
    unsigned char shift = 0x10; // 0001 1000
    while (shift > 0) {
        writel(bit_clc, gpio2+CLEAR_OFFSET);
        delay_n_NOP();
        if ((_Bool) (write_byte & shift)) {
            writel(1<<BIT_MOSI, gpio2+SET_OFFSET);
            delay_n_NOP();
        } else {
            writel(1<<BIT_MOSI, gpio2+CLEAR_OFFSET);
            delay_n_NOP();
        }
        shift >>= 1;
        writel(bit_clc, gpio2+SET_OFFSET);
    }
}

// Read one symbol from the ADC
static int SPI_read_from_adc(void)
{
    unsigned int value = 0, index;

    writel(1<<BIT_CS, gpio1+CLEAR_OFFSET);
    delay_n_NOP();
    SPI_write_sfd_and_ch();
    // Skip the first interval
    writel(bit_clc, gpio2+CLEAR_OFFSET);
    delay_n_NOP();
    writel(bit_clc, gpio2+SET_OFFSET);
    delay_n_NOP();
    // Read the value
    for (index=0; index<11; index++)
    {
        writel(bit_clc, gpio2+CLEAR_OFFSET);
        delay_n_NOP();
        value <<= 1;
        value |= (0x1 & (readl(gpio1+READ_OFFSET)>>BIT_MISO));
        writel(bit_clc, gpio2+SET_OFFSET);
        delay_n_NOP();
    }
    writel(bit_clc, gpio2+CLEAR_OFFSET);
    delay_n_NOP();
    writel(1<<BIT_CS, gpio1+SET_OFFSET);
    delay_n_NOP();

    return value;
}

//#define POLY 0x8408
/*
 *                                      16   12   5
 * this is the CCITT CRC 16 polynomial X  + X  + X  + 1.
 * This works out to be 0x1021, but the way the algorithm works
 * lets us use 0x8408 (the reverse of the bit pattern).  The high
 * bit is always assumed to be set, thus we only use 16 bits to
 * represent the 17 bit value.
 * 1 0001 0000 0010 0001
 * 1000010000000001
 */
unsigned short crc16(char *data_p, unsigned short length)
{
    unsigned char i;
    unsigned int data;
    unsigned int crc = 0xffff;
    unsigned int poly = 0x8408;

    if (length == 0)
        return (~crc);
    do {
        for (i=0, data=(unsigned int)0xff & *data_p++; i<8; i++, data>>=1) {
            if ((crc & 0x0001) ^ (data & 0x0001))
                crc = (crc >> 1) ^ poly;
            else  crc >>= 1;
        }
    } while (--length);

    crc = ~crc;
    data = crc;
    crc = (crc << 8) | (data >> 8 & 0xff);

    return (crc);
}


//// Print a (new generated) frame
//static void print_uncoded_frame(void)
//{
    //int i = 0;
    //printk("Generated:");
    //for (i=PREAMBLE_LEN; i<data_buffer_byte_len; i++)
        //printk(" %02x",data_buffer_byte[i]&0xff);
    //printk("\n");
//}

//// Print a (new generated) frame
//static void print_uncoded_ack(void)
//{
    //int i = 0;
    //printk("Generated:");
    //for (i=PREAMBLE_LEN; i<ack_buffer_byte_len; i++)
        //printk(" %02x",ack_buffer_byte[i]&0xff);
    //printk("\n");
//}


//// Print a (new generated) frame
//static void print_coded_frame(void)
//{
    //int i = 0;
    //printk("coded frame:");
    //for (i=0; i<data_buffer_symbol_len; i++)
        //printk(" %1x",data_buffer_symbol[i]&0xff);
    //printk("\n");
//}

// On-Off Keying (OOK) WITH Manchester Run-Length-Limited (RLL) code
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


//// On-Off Keying (OOK) w/o Manchester Run-Length-Limited (RLL) code
//static void OOK_without_Manchester_RLL(char *buffer_before_coding,
    //_Bool *buffer_after_coding, int len_before_coding)
//{
    //int byte_index, symbol_index = 0;
    //unsigned char curr_byte, mask;

    //// Convert the frame -- OOK w/o Manchester RLL code
    //for (byte_index=0; byte_index<len_before_coding; byte_index++) {
        //mask = 0x80;
        //curr_byte = buffer_before_coding[byte_index] & 0xff;
        //while (mask) {
            //buffer_after_coding[symbol_index++] = (_Bool) (curr_byte & mask);
            //mask >>= 1;
        //}
    //}
//}

static void construct_ack(char* buffer, int buffer_len)
{
    int i;
    for (i=0; i<PREAMBLE_LEN; i++)
        buffer[i] = 0xaa; // Preamble
    // SFD
    buffer[PREAMBLE_LEN] = 0x3a;
}

static void construct_frame_header(char* buffer, int buffer_len, int payload_len)
{
    int i;
    //unsigned short crc;

    for (i=0; i<PREAMBLE_LEN; i++)
        buffer[i] = 0xaa; // Preamble
    // SFD
    buffer[PREAMBLE_LEN] = 0xa3;
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

static void generate_DATA_frame(struct vlc_packet *pkt)
{
    int i, payload_len, index_block, encoded_len, num_of_blocks = 0;
    payload_len = pkt->datalen-(MAC_HDR_LEN-OCTET_LEN);
    encoded_len = payload_len+2*MAC_ADDR_LEN+PROTOCOL_LEN;
    // Calculate the number of blocks
    if (encoded_len % block_size)
        num_of_blocks = encoded_len / block_size + 1;
    else
        num_of_blocks = encoded_len / block_size;
        
    data_buffer_byte_len = FRAME_LEN_WO_PAYLOAD + payload_len + ECC_LEN*(num_of_blocks-1);
    //data_buffer_byte = kmalloc(data_buffer_byte_len, GFP_KERNEL);
    memset (data_buffer_byte, 0, sizeof (unsigned char) * data_buffer_byte_len);
    data_buffer_symbol_len = (data_buffer_byte_len-PREAMBLE_LEN)*8*2
        + PREAMBLE_LEN*8 + 1; // Send a BIT more, why? -- Avoid phy error
    //data_buffer_symbol =
        //kmalloc((data_buffer_symbol_len)*sizeof(_Bool), GFP_KERNEL);
    if (data_buffer_byte==NULL || data_buffer_symbol==NULL) {
        printk ("Ran out of memory generating new frames.\n");
        return;
    }
    // Construct a new data frame
    memcpy(data_buffer_byte+PREAMBLE_LEN+SFD_LEN+OCTET_LEN, pkt->data, 
        pkt->datalen); // Copy the payload
    vlc_release_buffer(pkt); // Return the buffer to the pool
    construct_frame_header(data_buffer_byte, data_buffer_byte_len, payload_len);
    
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
    
    /////******************************
    //for (i = 0; i < ECC_LEN; i++)
        //par[i] = 0;
    //encode_rs8(rs_decoder, data_buffer_byte+PREAMBLE_LEN+SFD_LEN+OCTET_LEN, // buffer
                //payload_len+2*MAC_ADDR_LEN+PROTOCOL_LEN, // Length of data to be encoded
                //par, 0);
                ////data_buffer_byte+FRAME_LEN_WO_PAYLOAD+tx_len-ECC_LEN, 0);
    //for (i = 0; i < ECC_LEN; i++) {
        //data_buffer_byte[FRAME_LEN_WO_PAYLOAD+payload_len-ECC_LEN+i] = par[i];
        ////printk(" %02x",par[i]&0xff);
    //}
    //printk("\n");
    // Encoding the frame
    OOK_with_Manchester_RLL(data_buffer_byte, data_buffer_symbol,
                            data_buffer_byte_len);
    tx_data_curr_index = data_buffer_symbol_len;
    //print_uncoded_frame();
    //if (data_buffer_byte) kfree(data_buffer_byte);
//    print_coded_frame();
}

static void construct_dummy_frame(char* buffer, int buffer_len, int payload_len)
{
    int i;
    //unsigned short crc;

    for (i=0; i<PREAMBLE_LEN; i++)
        buffer[i] = 0xaa; // Preamble
    // SFD
    buffer[PREAMBLE_LEN] = 0xa3;
    // Length of payload
    buffer[PREAMBLE_LEN+1] = (unsigned char) ((payload_len>>8) & 0xff);
    buffer[PREAMBLE_LEN+2] = (unsigned char) (payload_len & 0xff);
    // Destination address
    buffer[PREAMBLE_LEN+3] = (unsigned char) ((dst_id>>8) & 0xff);
    buffer[PREAMBLE_LEN+4] = (unsigned char) (dst_id & 0xff);
    // Source address
    buffer[PREAMBLE_LEN+5] = (unsigned char) ((self_id>>8) & 0xff);
    buffer[PREAMBLE_LEN+6] = (unsigned char) (self_id & 0xff);
    // Protocol
    buffer[PREAMBLE_LEN+7] = 0x08;
    buffer[PREAMBLE_LEN+8] = 0x06;
    // Payload
    for (i=0; i<payload_len; i++) { // Data
        buffer[PREAMBLE_LEN+SFD_LEN+MAC_HDR_LEN+i] = (char) (0x99&0xff); 
    }
    // CRC
    //crc = crc16(buffer+PREAMBLE_LEN+SFD_LEN, MAC_HDR_LEN+payload_len);
    //buffer[buffer_len-2] = (char) ((0xff00&crc)>>8); // CRC byte 1
	//buffer[buffer_len-1] = (char) ((0x00ff&crc)); // CRC byte 2
}


static void generate_dummy_DATA_frame(void)
{
    int i, index_block, encoded_len, num_of_blocks = 0;
    encoded_len = tx_len+2*MAC_ADDR_LEN+PROTOCOL_LEN;
    // Calculate the number of blocks
    if (encoded_len % block_size)
        num_of_blocks = encoded_len / block_size + 1;
    else
        num_of_blocks = encoded_len / block_size;
    //printk("num_of_blocks: %d\n", num_of_blocks);
    data_buffer_byte_len = FRAME_LEN_WO_PAYLOAD + tx_len + ECC_LEN*(num_of_blocks-1);
    //data_buffer_byte = kmalloc(data_buffer_byte_len, GFP_KERNEL);
    memset (data_buffer_byte, 0, sizeof (unsigned char) * data_buffer_byte_len);
    data_buffer_symbol_len = (data_buffer_byte_len-PREAMBLE_LEN)*8*2
        + PREAMBLE_LEN*8 + 1; // Send a BIT more, why? -- Avoid phy error
    //data_buffer_symbol =
        //kmalloc(data_buffer_symbol_len*sizeof(_Bool), GFP_KERNEL);
    if (data_buffer_byte==NULL || data_buffer_symbol==NULL) {
        printk ("Ran out of memory generating new frames.\n");
        return;
    }
    // Construct a new data frame
    construct_dummy_frame(data_buffer_byte, data_buffer_byte_len, tx_len);
    
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
            data_buffer_byte[FRAME_LEN_WO_PAYLOAD+tx_len+(index_block-1)*ECC_LEN+i] = par[i];
    }
        
    //print_uncoded_frame();
    // Encoding the frame
    OOK_with_Manchester_RLL(data_buffer_byte, data_buffer_symbol,
                            data_buffer_byte_len);
    tx_data_curr_index = data_buffer_symbol_len;
    //print_uncoded_frame();
    //if (data_buffer_byte) kfree(data_buffer_byte);
//    print_coded_frame();
}


static void generate_ACK_frame(void)
{
    //ack_buffer_byte_len = FRAME_LEN_WO_PAYLOAD;
    ack_buffer_byte_len = PREAMBLE_LEN+SFD_LEN+10;
    //ack_buffer_byte = kmalloc(ack_buffer_byte_len, GFP_KERNEL);
    ack_buffer_symbol_len = (ack_buffer_byte_len-PREAMBLE_LEN)*8*2
        + PREAMBLE_LEN*8 + 1; // Send a BIT more, why? -- Avoid phy error
    //ack_buffer_symbol =
        //kmalloc(ack_buffer_symbol_len*sizeof(_Bool), GFP_KERNEL);
    if (ack_buffer_byte==NULL || ack_buffer_symbol==NULL) {
        printk ("Ran out of memory generating new frames.\n");
        return;
    }
    // Construct a new frame
    //construct_frame(ack_buffer_byte, ack_buffer_byte_len, 0);
    construct_ack(ack_buffer_byte, ack_buffer_byte_len);
    // Encoding the frame
    OOK_with_Manchester_RLL(ack_buffer_byte, ack_buffer_symbol,
                                ack_buffer_byte_len);
    //print_uncoded_ack();
    //if (ack_buffer_byte) kfree(ack_buffer_byte);
//    print_coded_frame();
}

static int basic_sensing(_Bool f_display)
{
    int cnt_symbol = 0;
    int i = 0;
    int timeout = 1;
    index_long_sensing = 0;
    phy_state = SENSING;
    while (index_long_sensing<LONG_SENSING_SYMBOLS && timeout<100) {
        msleep(1);
        ++timeout;
    }
    if (timeout >= 100) {
        printk("Sensing timeout.\n");
        return 0;
    }
    if (f_display) printk("sensing: %d ", sensing_buffer[0]);
    avg_val_from_sensing = sensing_buffer[0];
    for (i = 1; i < LONG_SENSING_SYMBOLS; i++) {
        if (f_display)  printk("%d ", sensing_buffer[i]);
        avg_val_from_sensing += sensing_buffer[i];
        if (abs(sensing_buffer[i]-sensing_buffer[i-1]) > min_threshold)
            ++cnt_symbol;
    }
    avg_val_from_sensing /= LONG_SENSING_SYMBOLS;
    if (f_display)  printk("\n");
    return cnt_symbol;
}

static int mac_tx(void *data)
{
    int backoff_timer = 0;
    struct vlc_priv *priv = netdev_priv(vlc_devs);
    //unsigned long flags;
    
start: 
    for (; ;) {
        if (mac_or_app == APP) {
            if (!priv->tx_queue) {
                msleep(decoding_sleep_slot);
                if (kthread_should_stop()) {
                    printk("\n=======EXIT mac_tx=======\n");
                    return 0;
                }
                goto start;
            }
            tx_pkt = vlc_dequeue_pkt(vlc_devs);
            //printk("Dequeue a packet!\n");
            /// Transmit the packet
            generate_DATA_frame(tx_pkt); // Generate MAC frame
        } else if (mac_or_app == MAC) {
            //if (data_buffer_symbol)
                //kfree(data_buffer_symbol);
            generate_dummy_DATA_frame();
        }
        for (; ;) {
            if (f_received_ack || f_dropped_frame) {
                f_received_ack = false;
                f_dropped_frame = false;
                msleep(decoding_sleep_slot);
                //printk("f_received_ack %d || f_dropped_frame%d\n", f_received_ack, f_dropped_frame);
                break;
            }
            if (phy_state == TX) { // This node is transmitting the ACK
                msleep(decoding_sleep_slot);
                //printk("phy_state == TX %d\n", phy_state);
                continue;
            }
            if (!f_wait_for_ack && tx_data_curr_index>=data_buffer_symbol_len) {
                if (!f_re_tx) {
                    f_ready_to_tx = 0;
                    get_random_bytes(&backoff_timer,sizeof(backoff_timer));
                    CW = CW_min;
                    backoff_timer = abs(backoff_timer) % CW + 1;
                } else { /// Retransmit a frame
                    CW = CW << 1;
                    CW = (CW < CW_max) ? CW : CW_max;
                    backoff_timer = abs(backoff_timer) % CW + 1;
                    f_re_tx = false;
                }
    wait:       // waiting for ACK || receiving || transmitting || busy channel
                while ((phy_state==TX) || basic_sensing(false)) {
                    //printk("basic sensing.\n");
                    msleep(decoding_sleep_slot);
                    if (kthread_should_stop()) {
                        printk("\n=======EXIT mac_tx=======\n");
                        return 0;
                    }
                }
                backoff_timer -= 1;
                while (backoff_timer)
                    goto wait;
                tx_data_curr_index = 0;
                f_ready_to_tx = 1;
                cnt_detection_bit = 0;
                if (!hpl) switch_led_to_tx();
                phy_state = TX; // Switch to TX mode to transmit the data frame
            }
            //printk("f_wait_for_ack %d; tx_data_curr_index %d; data_buffer_symbol_len%d\n",
                //f_wait_for_ack, tx_data_curr_index, data_buffer_symbol_len);
            msleep(decoding_sleep_slot);
        }
        if (kthread_should_stop()) {
            printk("\n=======EXIT mac_tx=======\n");
            return 0;
        }
    }
    
//ret:
    //printk("\n=======EXIT mac_tx=======\n");
    //return 0;
}


/*
 * Receive a packet: retrieve, encapsulate and pass over to upper levels
 */
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
	skb_reserve(skb, 2); /* align IP on 16B boundary */
	memcpy(skb_put(skb, pkt->datalen), pkt->data, pkt->datalen);

	/* Write metadata, and then pass to the receive level */
	skb->dev = dev;
	skb->protocol = vlc_type_trans(skb, dev);
	skb->ip_summed = CHECKSUM_UNNECESSARY; /* don't check it */
	priv->stats.tx_packets++;
	priv->stats.tx_bytes += pkt->datalen;
	netif_rx(skb);
	//kfree(pkt);
  out:
	return;
}

static inline int decode_a_symbol_w_Manchester_RLL(void)
{
    int val_1, val_2;
    val_1 = rx_buffer[rx_out_index++];
    if (rx_out_index >= RX_BUFFER_SIZE)
        rx_out_index = 0;
    val_2 = rx_buffer[rx_out_index++];
    if (rx_out_index >= RX_BUFFER_SIZE)
        rx_out_index = 0;

    //val_1 = (val_1 >= threshold) ? 1 : 0;
    //val_2 = (val_2 >= threshold) ? 1 : 0;
    //if (!val_1 && val_2)
        //return 1;
    //else if (val_1 && !val_2)
        //return 0;
        
    //else return 0;
    return (val_1 < val_2);
}

static _Bool rx_buffer_has_two_plus_symbols(void)
{
    if ( (((rx_out_index+1)%RX_BUFFER_SIZE)!=rx_in_index)
                && (rx_out_index%RX_BUFFER_SIZE !=rx_in_index) )
        return true;
    return false;
}

static void print_rx_symbols(void)
{
    int i = rx_out_index;
    printk("Read values: ");
    while (i!=rx_in_index && i<rx_out_index+8) { // Print 16 symbols
   // while (i!=rx_in_index) { // Print 16 symbols
        printk("%d ", (int)rx_buffer[i++]);
        if (i >= RX_BUFFER_SIZE)
            i = 0;
    }
    if (adc_ch == 0)
        printk("- RX: low-power LED.\n");
    else
        printk("- RX: photodiode.\n");
    //rx_out_index=rx_in_index;
    //printk(" === \n");
}

/// Can not use the standard "strncmp" or "strcmp"
static int cmp_packets(char *pkt_1, char *pkt_2, int len)
{
    int i = 0;
    for (i=0; i<len; i++) {
        if (pkt_1[i] != pkt_2[i])
            return 1; // Packets are not equal
    }
    return 0; // Packets are equal
}

static int phy_decoding(void *data)
{
    int i, j, num_err = 0;
    char sfd_data = 0xa3;
    char sfd_ack = 0x3a;
    //unsigned char mask;
    int cnt_preamble = 0;
    int cnt_byte = 0;
    int cnt_symbol = 1;
    int curr_symbol = 0;
    _Bool curr_read = 0;
    //_Bool curr_cmp;
    char recv_sfd = 0;
    unsigned int payload_len = 0;
    unsigned int buffer_len = 0;
    int rx_ch;
    int prev_symbol = 0;
    int guarder = 2; //
    int sum_preamble=0;
    int min_preamble = 10;
    int max_preamble = 0;
    //unsigned short recv_crc = 0;
    //unsigned short cal_crc = 0;
    struct vlc_priv *priv = netdev_priv(vlc_devs);
    int index_block, encoded_len, num_of_blocks, total_num_err = 0;
    // May 31, 2015
    int max_un_reception = 10000;
    int num_un_reception = 0;
    ///******************Nov 14, 2014
    //int erasures[16];
    //int n_erasures = 0;
    ///******************************
    threshold = 0;

start_of_process: /// Start the process of a frame
    cnt_symbol = 1;
    prev_symbol = 0;
    cnt_preamble = 0;
    sum_preamble = 0;
    tmp_symbol_index = 0;
    num_un_reception = 0;
    for (; ;) {
        if (phy_state == TX) {
            rx_out_index = rx_in_index;
            msleep(decoding_sleep_slot);
            //printk("sleep...\n");
            continue;
        }
        if(show_msg) print_rx_symbols();
        while (rx_out_index != rx_in_index) {
            curr_symbol = rx_buffer[rx_out_index++];
            if (rx_out_index >= RX_BUFFER_SIZE) { rx_out_index = 0; }
//p_preamble: /// Proceed the preamble
            // printk("check preamble...\n");
            if ( ( (!(cnt_symbol%2)) && (curr_symbol-prev_symbol>=guarder) )
                || ((cnt_symbol%2)&&(prev_symbol-curr_symbol>=guarder)) ) {
                ++cnt_symbol;
                sum_preamble += curr_symbol;
                max_preamble = (curr_symbol>max_preamble) ? curr_symbol:max_preamble;
                min_preamble = (curr_symbol<min_preamble) ? curr_symbol:min_preamble;
            } else {
                cnt_symbol = 1;
                sum_preamble = curr_symbol;
                min_preamble=100;
                max_preamble=0;
                cnt_preamble = 0;
            }
            prev_symbol = curr_symbol;
            if (cnt_symbol >= 8) {
                cnt_symbol = 0;
                ++cnt_preamble;
                f_rx_one_preamble = true;
                if (cnt_preamble >= PREAMBLE_LEN) {
                    //threshold = sum_preamble/(PREAMBLE_LEN*8);
                    threshold = (min_preamble+max_preamble)/2;
                    if (show_msg)
                        printk("Found a preamble! ");
                    //printk("Threshold: %d \t", threshold);
                    f_rx_whole_preamble = true;
                    num_un_reception = 0; // May 31, 2015
                    goto p_sfd;
                }
            }
        // May 31, 2015  Dynamic switch of the RX
            //++num_un_reception;
            //if (num_un_reception >= max_un_reception) {
                //num_un_reception = 0;
                //adc_ch = (adc_ch == 0) ? 1 : 0;
                //rx_device->data = &adc_ch;
                ////printk("switch to different channel: %d\n", adc_ch);
            //}
        }
        msleep(decoding_sleep_slot);
        if (kthread_should_stop()) { 
            printk("\n=======EXIT======from p_premable=======\n");
            goto ret;
        }
    }

p_sfd:  /// Proceed the SFD
    cnt_symbol = 7;
    recv_sfd = 0;
    for (; ;) {
        while (rx_buffer_has_two_plus_symbols()) {
            curr_read = decode_a_symbol_w_Manchester_RLL();
            recv_sfd += (curr_read << cnt_symbol);
            if (--cnt_symbol < 0) {
                if (recv_sfd == sfd_data) {
                    goto p_length;
                } else if (recv_sfd == sfd_ack) {
                    f_wait_for_ack = false;
                    f_received_ack = true;
                    printk("Received ACK.\n");
                    if (!kthread_should_stop())
                        goto start_of_process;
                } else {
                    //printk("SFD error: %02x\n", recv_sfd&0xff);
                    goto start_of_process;
                }
                //if (recv_sfd != sfd) {
                    //printk("SFD error: %02x %02x \n", recv_sfd&0xff, sfd&0xff);
                    //goto p_preamble;
                //} else {
                    ////if (show_msg)
                        ////printk("Found the SFD: %02x %02x \n", recv_sfd&0xff, sfd&0xff); 
                        //// Finish matching the SFD
                    
                //}
                //goto p_length;
            }
        }
        msleep(decoding_sleep_slot);
        if (kthread_should_stop())  {
            printk("\n=======EXIT======from p_sfd=======\n");
            goto ret;
        }
    }

p_length: ///  Get payload length
    cnt_symbol = 15;
    payload_len = 0;
    for (; ;) {
        while (rx_buffer_has_two_plus_symbols()) {
            curr_read = decode_a_symbol_w_Manchester_RLL();
            payload_len += (curr_read << cnt_symbol);
            if (--cnt_symbol < 0) {
                if (payload_len > 0 && payload_len <= mtu) 
                    printk("Payload: %d ", payload_len);
                else 
                    goto end;
                f_received_len = true;
                encoded_len = payload_len+2*MAC_ADDR_LEN+PROTOCOL_LEN;
                // Calculate the number of blocks
                if (encoded_len % block_size)
                    num_of_blocks = encoded_len / block_size + 1;
                else
                    num_of_blocks = encoded_len / block_size;
                //printk("num_of_blocks: %d\n", num_of_blocks);
                buffer_len = MAC_HDR_LEN+payload_len+num_of_blocks*ECC_LEN;
                //rx_data = kmalloc(buffer_len, GFP_KERNEL);
                memset(rx_data, 0, sizeof (char) * RX_DATA_LEN);
                rx_data[0] = (char)((payload_len>>8) & 0xff);
                rx_data[1] = (char)(payload_len & 0xff);
                tmp_symbol_index = 0;
                goto p_body;
            }
        }
        msleep(decoding_sleep_slot);
        if (kthread_should_stop()) {
            printk("\n=======EXIT======from p_length=======\n");
            //if (rx_data) kfree(rx_data);
            goto ret;
        }
    }

p_body: /// Proceed the frame payload
    cnt_byte = 2; // The two bytes are the data length, which has been saved
    cnt_symbol = 7;
    rx_ch = 0;
    for (; ;) {
        while (rx_buffer_has_two_plus_symbols()) {
            curr_read = decode_a_symbol_w_Manchester_RLL();
            rx_ch += (curr_read << cnt_symbol);
            if (--cnt_symbol < 0) {
                rx_data[cnt_byte++] = (char) rx_ch;
                if (cnt_byte >= buffer_len) {
                    if (0 == payload_len) {
                        f_rx_one_preamble = false;
                    }
                    //f_wait_for_ack = false;
                    goto p_final;
                }
                cnt_symbol = 7;
                rx_ch = 0;
            }
        }
        msleep(decoding_sleep_slot);
        if (kthread_should_stop()) {
            printk("\n=======EXIT======from p_body=======\n");
            //if (rx_data) kfree(rx_data);
            goto ret;
        }
    }

p_final: /// Check the Reed-solomon, print the DATA frame, and send the ACK
    ///******************Nov 14, 2014
    //printk("check final...\n");
    //rx_data[10]=0x09;
    //for (cnt_byte=0 ; cnt_byte<payload_len+2*MAC_ADDR_LEN+PROTOCOL_LEN+ECC_LEN; cnt_byte++)
            //printk(" %02x", rx_data[OCTET_LEN+cnt_byte]);
    //printk("\n");
    
    // 
    j = OCTET_LEN+2*MAC_ADDR_LEN+PROTOCOL_LEN+payload_len;
    total_num_err = 0;
    for (index_block=0; index_block < num_of_blocks; index_block++) {
        for (i = 0; i < ECC_LEN; i++) {
            par[i] = rx_data[j+index_block*ECC_LEN+i];
            //printk(" %02x", par[i]);
        }
        //printk("\n");
        if (index_block < num_of_blocks-1) {
            num_err = decode_rs8(rs_decoder, rx_data+OCTET_LEN+index_block*block_size, 
                par, block_size, NULL, 0, NULL, 0, NULL);
        } else { // The last block
            num_err = decode_rs8(rs_decoder, rx_data+OCTET_LEN+index_block*block_size, 
                par, encoded_len % block_size, NULL, 0, NULL, 0, NULL);
        }
        if (num_err < 0) {
            printk("*** CRC error. ***\n");
            f_adjust_slot = 1;
            goto end;
        }
        total_num_err += num_err;
    }
    if (total_num_err > 0) {
        printk("*** Has corrected %d error(s) *** ", total_num_err);
    }
    
    if (payload_len>0) { // Data frame
        if (mac_or_app == APP) { // To upper layer
            //rx_pkt = kmalloc (sizeof (struct vlc_packet), GFP_KERNEL);
            rx_pkt->datalen = MAC_HDR_LEN-OCTET_LEN+payload_len;
            // Copy the received data (omit the datalen octet)
            memcpy(rx_pkt->data, rx_data+OCTET_LEN, rx_pkt->datalen);
            if (cmp_packets(rx_pkt->data,rx_pkt_check_dup->data,rx_pkt->datalen)) {
                // Frist copy the packet; the rx_pkt will be released in max_rx
                memcpy(rx_pkt_check_dup->data, rx_pkt->data, rx_pkt->datalen);
                rx_pkt_check_dup->datalen = rx_pkt->datalen;
                mac_rx(vlc_devs, rx_pkt);
                //printk("Sent to the Internet layer.\n");
                priv->stats.rx_packets++;
                priv->stats.rx_bytes += rx_pkt->datalen;
            }
            //if (rx_pkt) kfree(rx_pkt); // End of to upper layer
        }
        printk("Received DATA. %d \n", adc_ch);
        // Send the ACK
        generate_ACK_frame();
        msleep(10*decoding_sleep_slot);
        tx_ack_curr_index = 0;
        f_ready_to_tx_ack = 1;
        if (!hpl) switch_led_to_tx();
        phy_state = TX; // Switch to TX mode to transmit the ACK frame 
    }
end:
    //if (rx_data) kfree(rx_data);
    if (!kthread_should_stop())
        goto start_of_process;
    
    ret:
    printk("\n=======EXIT phy_decoding=======\n");
    return 0;
}

//static enum hrtimer_restart phy_timer_handler(struct hrtimer *timer)
void phy_timer_handler(rtdm_timer_t *timer)
{
    //int val1, val2 = 0;
    //int tmp_th = 10;
    int prev_value = 0;
    if (f_adjust_slot) {
        rtdm_timer_stop(&phy_timer);
        rtdm_timer_start(&phy_timer, slot_ns/2, slot_ns,
            RTDM_TIMERMODE_RELATIVE);
        f_adjust_slot = false;
    }

    hpl = (*(int *)tx_device->data); // Read the configuration of the TX
    switch_tx(); // May change the TX
    adc_ch = (*(int *)rx_device->data); // May change the RX
    
	if (phy_state == TX) { // The node is in TX state
        if (f_ready_to_tx && (tx_data_curr_index<data_buffer_symbol_len)) {
            if (data_buffer_symbol[tx_data_curr_index]) {// Transmit symbol HIGH
                if (!hpl) writel(1<<BIT_BUFFER_CONTROL, gpio2+CLEAR_OFFSET);
                delay_n_NOP();
                writel(1<<bit_led_anode, gpio2+SET_OFFSET);
            } else { // Transmit symbol LOW
                writel(1<<bit_led_anode, gpio2+CLEAR_OFFSET);
                //gpio_set_value(GPIO_LED_ANODE, GPIOF_INIT_LOW);
                if (!hpl) writel(1<<BIT_BUFFER_CONTROL, gpio2+SET_OFFSET);
                if ( (tx_data_curr_index%2)
                        && (tx_data_curr_index>2*PREAMBLE_LEN_IN_BITS) )  
                {
                    //switch_led_to_rx();
                    //prev_value = SPI_read_from_adc();
                    //delay_n_NOP();
                    //rx_in_val = SPI_read_from_adc();
                    //switch_led_to_tx();
                    //if (prev_value+10 < rx_in_val)
                    //{
                        //if (++cnt_detection_bit >= MAX_DETECTION_BIT) {
                            //printk("Collision detected. Stop transmitting: Curr-%d Avg-%d CNT-%d \n", rx_in_val, 
                                //avg_val_from_sensing, cnt_detection_bit);
                            //cnt_detection_bit = 0;
                            //tx_data_curr_index = data_buffer_symbol_len;
                            //f_ready_to_tx = false;
                            //switch_led_to_rx();
                            //phy_state = RX; // Switch to RX mode to receive ACK
                            //rx_out_index = rx_in_index;
                        //}
                    //}
                }
            }
            if (++tx_data_curr_index>=data_buffer_symbol_len && f_ready_to_tx) {
                f_wait_for_ack = true;
                index_ack_timeout = 0;
                f_received_len = false;
                writel(1<<bit_led_anode, gpio2+CLEAR_OFFSET);
                //if (show_msg) 
                //{
                    //if (hpl == 1) {
                        //printk("Sent a frame. TX: high-power LED.\n");
                    //} else {
                        //printk("Sent a frame. TX: low-power LED.\n");
                    //}
                //}
                //printk("Sent frame. Wait for ACK.\n");
                gpio_set_value(GPIO_LED_ANODE, GPIOF_INIT_LOW);
                gpio_set_value(GPIO_BUFFER_CONTROL, GPIOF_INIT_HIGH);
                switch_led_to_rx();
                phy_state = RX; // Switch to RX mode to receive the ACK
                rx_out_index = rx_in_index;
            }
        } // End: the node is transmtting a data frame
        else if (f_ready_to_tx_ack && // Transmit an ACK frame
                    (tx_ack_curr_index<ack_buffer_symbol_len)) {
            if (ack_buffer_symbol[tx_ack_curr_index]) {
                if (!hpl) writel(1<<BIT_BUFFER_CONTROL, gpio2+CLEAR_OFFSET);
                delay_n_NOP();
                writel(1<<bit_led_anode, gpio2+SET_OFFSET);
            } else {
                writel(1<<bit_led_anode, gpio2+CLEAR_OFFSET);
                if (!hpl) writel(1<<BIT_BUFFER_CONTROL, gpio2+SET_OFFSET);
            }
            if (++tx_ack_curr_index >= ack_buffer_symbol_len) {
                f_ready_to_tx_ack = false;
                //printk("Sent ACK.\n");
                if (!hpl) switch_led_to_rx();
                phy_state = RX; // Switch to RX mode
            }
        } // End: the node is transmitting an ACK frame
    } // End TX mode
    else if (phy_state == RX) {
        rx_buffer[rx_in_index++] = SPI_read_from_adc();
        if (rx_in_index >= RX_BUFFER_SIZE) { rx_in_index = 0; }
        if (f_wait_for_ack && (index_ack_timeout++)>ACK_TIMEOUT) {
            f_wait_for_ack = false;
            if (cnt_retransmission<MAX_RETRANSMISSION) {
                ++cnt_retransmission;
                f_re_tx = true; // Retransmit
                f_rx_one_preamble = 0;
              //printk("ACK timeout. Retransmit %d.\n\n", cnt_retransmission);
            } else { // Drop the current data frame or assume it is received
                printk("*** Drop the frame: transmitted %d times ***\n", cnt_retransmission);
                f_dropped_frame = true;
                cnt_retransmission = 0;
                f_re_tx = false;
                f_rx_one_preamble = false;
            }
        }
    } // End RX mode
    else if (phy_state == SENSING) { /// The node is in SENSING state
        //val1 = SPI_read_from_adc();
        //val2 = SPI_read_from_adc();
        //if (val2-val1>=tmp_th)
            //rx_in_val = 100;
        //else if (val1-val2>tmp_th)
            //rx_in_val = 3;
        //else if (val2>2*tmp_th)
            //rx_in_val = 100;
        //else 
            //rx_in_val = 3;
        rx_in_val = SPI_read_from_adc();
        sensing_buffer[index_long_sensing++] = rx_in_val;
        rx_buffer[rx_in_index++] = rx_in_val; // Also save to the rx_buffer
        if (rx_in_index >= RX_BUFFER_SIZE) {rx_in_index = 0; }
        if (index_long_sensing >= LONG_SENSING_SYMBOLS) {
            phy_state = RX;
        }
	} // End Sensing mode (part of RX mode)
}

int vlc_release(struct net_device *dev)
{
	//netif_stop_queue(dev); /* can't transmit any more */
	return 0;
}

// Configuration changes (passed on by ifconfig)
int vlc_config(struct net_device *dev, struct ifmap *map)
{
	if (dev->flags & IFF_UP) /* can't act on a running interface */
		return -EBUSY;

	/* Don't allow changing the I/O address */
	if (map->base_addr != dev->base_addr) {
		printk(KERN_WARNING "snull: Can't change I/O address\n");
		return -EOPNOTSUPP;
	}

	/* Allow changing the IRQ */
	if (map->irq != dev->irq) {
		dev->irq = map->irq; /* request_irq() is delayed to open-time */
	}

	/* ignore other fields */
	return 0;
}

// Transmit a packet (called by the kernel)
int vlc_tx(struct sk_buff *skb, struct net_device *dev)
{
    struct vlc_packet *tmp_pkt;
    
    dev->trans_start = jiffies;
    tmp_pkt = vlc_get_tx_buffer(dev);
    tmp_pkt->next = NULL; ///*******
    tmp_pkt->datalen = skb->len;
    memcpy(tmp_pkt->data, skb->data, skb->len);
    vlc_enqueue_pkt(dev, tmp_pkt);
    printk("Enqueue a packet!\n");
    
    dev_kfree_skb(skb);
	return 0; /* Our simple device can not fail */
}

// Ioctl commands
int vlc_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	//printk("ioctl\n");
	return 0;
}

// Return statistics to the caller
struct net_device_stats *vlc_stats(struct net_device *dev)
{
	struct vlc_priv *priv = netdev_priv(dev);
	return &priv->stats;
}

// This function is called to fill up a VLC header 
int vlc_rebuild_header(struct sk_buff *skb)
{
	struct vlchdr *vlc = (struct vlchdr *) skb->data;
	struct net_device *dev = skb->dev;

	memcpy(vlc->h_source, dev->dev_addr, dev->addr_len);
	memcpy(vlc->h_dest, dev->dev_addr, dev->addr_len);
	vlc->h_dest[MAC_ADDR_LEN-1] ^= 0x01;   /* dest is us xor 1 */
	return 0;
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
    .create  = vlc_header,
	.rebuild = vlc_rebuild_header
};

int vlc_open(struct net_device *dev)
{
	memcpy(dev->dev_addr, "\0\2", MAC_ADDR_LEN);
    netif_start_queue(dev);
	return 0;
}

// Setup VLC network device
void vlc_setup(struct net_device *dev)
{
    dev->hard_header_len = VLC_HLEN;
    dev->mtu = mtu;
    dev->tx_queue_len = 100;
    dev->priv_flags |= IFF_TX_SKB_SHARING;
}

static const struct net_device_ops vlc_netdev_ops = {
	.ndo_open            = vlc_open,
	.ndo_stop            = vlc_release,
	.ndo_start_xmit      = vlc_tx,
	.ndo_do_ioctl        = vlc_ioctl,
	.ndo_set_config      = vlc_config,
	.ndo_get_stats       = vlc_stats,
};


int proc_read(char *page, char **start, off_t off, int count, int *eof,  
                void *data)
{
    count = sprintf(page, "%d", *(int *)data);
    return count;
}

int proc_write(struct file *file, const char *buffer, 
    unsigned long count, void *data) 
{
    unsigned int c = 0, len = 0, val, sum = 0;
    int * temp = (int *)data;

    while (count) {
        if (get_user(c, buffer))
            return -EFAULT;

        len++;
        buffer++;
        count--;

        if (c == 10 || c == 0)
            break;
        val = c - '0';
        if (val > 9)
            return -EINVAL;
        sum *= 10;
        sum += val;
    }
    *temp = sum;
    return len;
}


void vlc_init(struct net_device *dev)
{
	struct vlc_priv *priv;

    dev->addr_len = MAC_ADDR_LEN;
    dev->type = ARPHRD_LOOPBACK ;  // ARPHRD_IEEE802154
	vlc_setup(dev); /* assign some of the fields */
	dev->netdev_ops = &vlc_netdev_ops;
	dev->header_ops = &vlc_header_ops;
	/* keep the default flags, just add NOARP */
	dev->flags           |= IFF_NOARP;
	dev->features        |= NETIF_F_HW_CSUM;

	priv = netdev_priv(dev);
	memset(priv, 0, sizeof(struct vlc_priv));
    //printk(".....4.....\n");
	//spin_lock_init(&priv->lock);
    //printk(".....5.....\n");
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
        //printk(".....8.....\n");
        //netif_start_queue(dev);
        //printk(".....9.....\n");
    }
}

void vlc_cleanup(void)
{
    struct vlc_packet *pkt;
    struct vlc_priv *priv = netdev_priv(vlc_devs);
    ////unsigned long flags;
    //if (flag_lock)
        //spin_lock_bh(&priv->lock);
    flag_exit = 1;
    netif_stop_queue(vlc_devs);
    //if (flag_lock)
        //spin_unlock_bh(&priv->lock);
    
    
    // Clean the threads
    printk("stop phy decoding\n");
    if (task_phy_decoding) {
        kthread_stop(task_phy_decoding);
        task_phy_decoding = NULL;
    }
    
    printk("stop mac tx\n");
    if (task_mac_tx) {
        kthread_stop(task_mac_tx);
        task_mac_tx = NULL;
    }
    
    rtdm_timer_destroy(&phy_timer);

    iounmap(gpio1);
    iounmap(gpio2);
    
    // Clean the GPIOs
    gpio_free(GPIO_LED_ANODE);
    gpio_free(GPIO_LED_CATHODE);
    gpio_free(GPIO_BUFFER_CONTROL);
    gpio_free(GPIO_H_POWER_LED);
    gpio_free(GPIO_LED_OR_PD);

    gpio_free(SPI_CLC);
    gpio_free(SPI_MISO);
    gpio_free(SPI_MOSI);
    gpio_free(SPI_CS);
    // 
    
    // Clean the devices
    if (vlc_devs) {
        if (mac_or_app == APP) {
            printk("clean the pool\n");
            //if (flag_lock)
                //spin_lock_bh(&priv->lock);
            while(priv->tx_queue) {
                pkt = vlc_dequeue_pkt(vlc_devs);
                vlc_release_buffer(pkt);
            }
            //if (flag_lock)
                //spin_unlock_bh(&priv->lock);
            vlc_teardown_pool(vlc_devs);
            kfree(rx_pkt);
            kfree(rx_pkt_check_dup);
            kfree(tx_pkt);
        }
        printk("unregister the devs\n");
        unregister_netdev(vlc_devs);
        
        //if (mac_or_app == APP) {
            //vlc_teardown_pool(vlc_devs);
        //}
        
        printk("free the devs\n");
        free_netdev(vlc_devs);
    }
    
    remove_proc_entry("rx", vlc_dir);
    remove_proc_entry("tx", vlc_dir);
    remove_proc_entry("vlc", NULL);

    // Free the reed solomon resources
    if (rs_decoder) {
        free_rs(rs_decoder);
    }
    
    //printk("free packets\n");
    //if (tx_pkt)
        //kfree(tx_pkt);
    //if (rx_pkt)
        //kfree(rx_pkt);
    //if (rx_pkt_check_dup)
        //kfree(rx_pkt_check_dup);
    //if (data_buffer_symbol)
        //kfree(data_buffer_symbol);
                
	printk(KERN_NOTICE "The VLC module has been removed.\n");
	return;
}

static void vlc_regular_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
}

int vlc_init_module(void)
{
	int ret = -ENOMEM;
	printk("Initializing the VLC module...\n");
    
    vlc_interrupt = vlc_regular_interrupt;
    
    
    frq *= 1000; // Convert the frequency from KHz to Hz
	// May optimize this part
    /// Wait to be optimized
    decoding_sleep_slot = (1000*1/frq);
    decoding_sleep_slot = (decoding_sleep_slot>=1) ? decoding_sleep_slot : 1;
    printk("Sleep slot (while decoding) is %d ms\n", decoding_sleep_slot);

	/// Create the device and register it
	vlc_devs = alloc_netdev(sizeof(struct vlc_priv), "vlc%d", vlc_init);
	if (vlc_devs == NULL)
		goto out;
	ret = register_netdev(vlc_devs);
    if (ret)
        printk("VLC: error registering device \"%s\"\n", vlc_devs->name);

    /// GPIOs for the LED
    if ( gpio_request(GPIO_LED_ANODE, "LED_ANODE")
            || gpio_request(GPIO_LED_CATHODE, "LED_CATHODE")
            || gpio_request(GPIO_BUFFER_CONTROL, "BUFFER_CONTROL") 
            || gpio_request(GPIO_H_POWER_LED, "H_POWER_LED") 
            || gpio_request(GPIO_LED_OR_PD, "LED_OR_PD") 
            ) {
        printk("Request GPIO failed!\n");
        ret = -ENOMEM;
        goto out;
    }
    gpio_direction_output(GPIO_LED_ANODE, GPIOF_INIT_LOW);
    gpio_direction_output(GPIO_LED_CATHODE, GPIOF_INIT_LOW);
    gpio_direction_output(GPIO_BUFFER_CONTROL, GPIOF_INIT_HIGH);
    gpio_direction_output(GPIO_H_POWER_LED, GPIOF_INIT_LOW);
    gpio_direction_output(GPIO_LED_OR_PD, GPIOF_INIT_LOW);
    
    /// GPIOs for SPI
    if ( gpio_request(SPI_CLC, "SPI_CLC")
            || gpio_request(SPI_MISO, "SPI_MISO")
            || gpio_request(SPI_MOSI, "SPI_MOSI")
            || gpio_request(SPI_CS, "SPI_CS") ) {
        printk("Request GPIO failed!\n");
        ret = -ENOMEM;
        goto out;
    }
    gpio_direction_output(SPI_CLC, GPIOF_INIT_LOW);
    gpio_direction_input(SPI_MISO);
    gpio_direction_output(SPI_MOSI, GPIOF_INIT_LOW);
    gpio_direction_output(SPI_CS, GPIOF_INIT_LOW);

    // Qing - May 2, 2015
    //if (pd_as_rx == 1) { // PD
        //gpio_direction_output(GPIO_LED_OR_PD, GPIOF_INIT_HIGH);
    //} else { // LED
        //gpio_direction_output(GPIO_LED_OR_PD, GPIOF_INIT_LOW);
    //}
    //if (hpl == 1) {
        //bit_led_anode = BIT_H_POWER_LED; // High-power LED as TX
        //gpio_direction_output(GPIO_LED_OR_PD, GPIOF_INIT_LOW); // PD as RX
    //} else { // LED
        //bit_led_anode = BIT_LED_ANODE; // LED as TX
        //gpio_direction_output(GPIO_LED_OR_PD, GPIOF_INIT_HIGH); // LED as RX
    //}
    switch_tx();
    
    gpio1 = ioremap(ADDR_BASE_0, 4);
    gpio2 = ioremap(ADDR_BASE_1, 4);
    
    phy_state = RX;
    switch_led_to_rx();
    
    printk("my_gpio: Access address to device is:0x%x  0x%x\n", 
        (unsigned int) gpio1, (unsigned int) gpio2);
 
    if (!(gpio1 && gpio2))
        goto out;

    vlc_dir = proc_mkdir("vlc", NULL);
    rx_device = create_proc_entry("rx", 0666, vlc_dir);
    tx_device = create_proc_entry("tx", 0666, vlc_dir);
    if (rx_device && tx_device) {
        rx_device->data = &rx_device_value;
        rx_device->read_proc = proc_read;
        rx_device->write_proc = proc_write;
        
        tx_device->data = &tx_device_value;
        tx_device->read_proc = proc_read;
        tx_device->write_proc = proc_write;
    }
    
    /// Timer
    slot_ns = 1000000000 / frq;
    printk("Slot in nanosecond: %d\n", slot_ns);
    ret = rtdm_timer_init(&phy_timer, phy_timer_handler, "phy timer");
    
    if(ret) {
      rtdm_printk("PWM: error initializing up-timer: %i\n", ret);
      return ret;
    }
    
    /* We could create the decoder on demand, if memory is a concern.
     * This way we have it handy, if an error happens
     *
     * Symbolsize is 10 (bits)
     * Primitve polynomial is x^10+x^3+1
     * first consecutive root is 0
     * primitve element to generate roots = 1
     * generator polinomial degree = 6
     */
    rs_decoder = init_rs(ecc_symsize, ecc_poly, 0, 1, ECC_LEN); // 0---FCR
    if (!rs_decoder) {
        printk(KERN_ERR "Could not create a RS decoder\n");
        ret = -ENOMEM;
        goto out;
    }

    
    ret = rtdm_timer_start(&phy_timer, slot_ns, slot_ns,
            RTDM_TIMERMODE_RELATIVE);
    if(ret) {
        rtdm_printk("PWM: error starting up-timer: %i\n", ret);
        return ret;
    }
    rtdm_printk("PWM: timers created\n");
    
    ///// Threads
    if (!rx) { 
        task_mac_tx = kthread_run(mac_tx,"TX thread","VLC_TX");
        if (IS_ERR(task_mac_tx)){
            printk("Unable to start kernel threads. \n");
            ret= PTR_ERR(task_phy_decoding);
            task_mac_tx = NULL;
            task_phy_decoding = NULL;
            goto out;
        }
    }
    task_phy_decoding = kthread_run(phy_decoding,"RX thread","VLC_DECODING");
    if (IS_ERR(task_phy_decoding)){
        printk("Unable to start kernel threads. \n");
        ret= PTR_ERR(task_phy_decoding);
        task_mac_tx = NULL;
        task_phy_decoding = NULL;
        goto out;
    }
    
    printk("The VLC module has been initialized.\n\n");

    out:
    printk("------EXIT vlc_init_module------\n");
	if (ret)
		vlc_cleanup();

	return ret;
}

module_init(vlc_init_module);
module_exit(vlc_cleanup);
