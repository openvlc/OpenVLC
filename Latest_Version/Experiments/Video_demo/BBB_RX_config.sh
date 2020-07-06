#!/bin/bash

cd kernel
sudo ./load_test.sh #Load OpenVLC driver
cd ..
cd PRU/RX_back
sudo ./deploy.sh #Load OpenVLC firmware
cd ..
cd ..
echo "1" | sudo tee /proc/sys/net/ipv4/ip_forward #Enable forwarding
sudo route add -net 192.168.7.0/24 gw 192.168.6.1 #Add USB server interface route
sudo route add -net 192.168.2.0/24 gw 192.168.6.1 #Add ethernet server interface route
echo "RX configured"
