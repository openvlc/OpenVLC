#!/bin/bash
sudo ifconfig enp8s0 192.168.2.10 #Configure the ethernet interface IP
sudo route add -net 192.168.7.0/24 gw 192.168.2.10 #Route server USB interfaces through ethernet
echo "1" | sudo tee /proc/sys/net/ipv4/ip_forward #Enable forwarding
sudo sysctl net.ipv4.conf.all.rp_filter=0  #Disable IP filter for all interfaces
sudo sysctl net.ipv4.conf.enp0s31f6.rp_filter=0  #Disable IP filter for USB interface
sudo sysctl net.ipv4.conf.enx506583e15eca.rp_filter=0  #Disable IP filter for ethernet interface
sudo ufw disable #Disable Ubuntu firewall

