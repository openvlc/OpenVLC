#!/bin/bash

sudo route add -net 192.168.6.0/24 gw 192.168.7.2 #Add USB client interface route
sudo ifconfig enp8s0 192.168.2.10 #Configure the ethernet interface IP
sudo route del -net 192.168.2.0/24 #Delete the default routing for the ethernet
sudo route add -net 192.168.2.0/24 gw 192.168.7.2 #Route client computer through VLC (BBB)
echo "1" | sudo tee /proc/sys/net/ipv4/ip_forward #Enable forwarding
sudo sysctl -w net.ipv4.conf.all.rp_filter=0 #Disable IP filter for all interfaces
sudo sysctl -w net.ipv4.conf.enx04a316b84e64.rp_filter=0 #Disable IP filter for USB interface
sudo sysctl -w net.ipv4.conf.enp8s0.rp_filter=0 #Disable IP filter for ethernet interface
sudo ufw disable #Disable Ubuntu firewall
