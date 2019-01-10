#!/bin/bash

cd kernel
sudo ./load_test.sh #Load OpenVLC driver
cd ..
cd PRU/TX
sudo ./deploy.sh #Load OpenVLC firmware
cd ..
cd ..
echo "1" | sudo tee /proc/sys/net/ipv4/ip_forward #Enable forwarding
sudo route add -net 192.168.6.0/24 gw 192.168.0.2 #Add USB client interface route
sudo route add -net 192.168.2.0/24 gw 192.168.0.2 #Add ethernet client interface route
echo "TX config"
