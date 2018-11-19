# OpenVLC1.3 Rev A

## Preparing the Beaglebone

  Creating the SD Card

  We need to flash the BBB with a Debian image. To do that we need a SD Card with at least 4 GB. Follow these steps:

  1. Format the SD Card with SD card formatter with overwrite format.
  2. Download the image from the link https://debian.beagleboard.org/images/bone-debian-8.7-iot-armhf-2017-03-19-4gb.img.xz
  3. Write the image ”bone-debian-8.7-iot-armhf-2017-03-19-4gb” to the SD Card with Win32 Disk Imager.

## Flashing the BBB

  Now we have the SD Card ready with the image, we need to flash the BBB.

  1. With the power disconnected, insert the SD Card into the BBB and power it up with the USB cable. 
  2. Connect through SSH to the IP 192.168.7.2.
  3. Now we’re running the OS on the SD Card, let’s flash it into the BBB. Move to /opt/scripts/tools/eMMC and run sudo ./bbb-eMMC-       flasher-eewiki-ext4.sh.
  4. Wait until it says “eMMC has been flashed”. Once it finishes, disconnect the usb cable and with the BBB switched off, remove the SD Card.

## Setting up the OS

  Firsts steps are preparing the beaglebone. This must be done in TX as well as in RX. These are the steps:
  
  1. Disable the HDMI: The HDMI uses some PRU pins that we need to use. To disable the HDMI cape edit the uEnv.txt file:
  
    sudo nano /boot/uEnv.txt
  
  and uncomment the line:

    dtb=am335x-boneblack-emmc-overlay.dtb

  Then once you reboot the HDMI cape will be disable.
  
  2. Install the headers: Connect the beaglebone to the Internet, and then update with:

    sudo apt-get update

  Then the board is ready to install the headers

    sudo apt-get install linux-headers-$(uname -r)

  3. Copy OpenVLC1.3 folder and PRU to /home/debian.

## Connecting the cape

  Connect the cape to the BBB is quite easy, you just need to plug the cape to the correct pins as shown in the image below:
  <p align="center">
    <img src="http://nebula.wsimg.com/ee581ebfab0dbd95c78142d8f1515645?AccessKeyId=FA5733F762B610D2E10A&disposition=0&alloworigin=1">
    <img src="http://nebula.wsimg.com/8d6e0f52e7134570f2eee6e17f3be40f?AccessKeyId=FA5733F762B610D2E10A&disposition=0&alloworigin=1">
  </p>

  Once it’s plugged, connect the 5 V power supply and that’s all.
  
  ATTENTION: Be careful not to bend the components that stand out when you press or pull the cape.

## Setting up the TX/RX
  
  There are two parts in the TX/RX, the kernel driver and the PRU code. 
  
  1. To load the kernel driver, inside OpenVLC1.3 folder run:
  
    sudo ./load_test.sh
  
  In that script you can change the IP the interface takes. That’s the IP in the VLC network, so TX and RX must have different IPs (for   example TX: 192.168.0.1 and RX 192.168.0.2).
  
  2. Once the module driver is installed, go to PRU folder. Enter TX/RX and run deploy.sh code:
  
    sudo ./deploy.sh
  
  This will boot up the PRUs with the code necessary to transmit and received VLC frames.

## Working with the TX/RX

  Once you have done that in TX and RX, both interfaces are up, so you can start using VLC as a common network interface. 
  Here is an example of an iperf test at 2.5 meters of distance:

  <p align="center">
    <img src="http://nebula.wsimg.com/a1ddde94e0b321a3664a8fc487236108?AccessKeyId=FA5733F762B610D2E10A&disposition=0&alloworigin=1">
  </p>

