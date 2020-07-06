#!/bin/bash

# Insert the driver
insmod vlc.ko frq=50 pool_size=5 mtu=1300 mac_or_app=1 self_id=9 dst_id=8

# Configure the IP address of the new interface
ifconfig vlc0 192.168.0.2

# Specify the TX: 0 is low-power LED; 1 is high-power LED
echo 1 > /proc/vlc/tx

# Specify the RX: 0 is low-power LED; 1 is PD
echo 1 > /proc/vlc/rx
