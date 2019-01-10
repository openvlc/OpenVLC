#!/bin/bash

cd kernel
sudo ./load_test.sh
cd ..
cd PRU/RX_back
sudo ./deploy.sh
cd ..
cd ..
echo "1" | sudo tee /proc/sys/net/ipv4/ip_forward
sudo route add -net 192.168.7.0/24 gw 192.168.6.1
sudo route add -net 192.168.2.0/24 gw 192.168.6.1
echo "RX configured"
