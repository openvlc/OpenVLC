#!/bin/bash

rmmod vlc
#watch -n 0.1 "dmesg | tail -n $((LINES-6))"

find -exec touch \{\} \;

make clean

make

# Insert the driver
insmod vlc.ko 

# Configure the IP address of the new interface
ifconfig vlc0 192.168.0.2
