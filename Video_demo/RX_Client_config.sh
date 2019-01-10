sudo route add -net 192.168.7.0/24 gw 192.168.2.10
echo "1" | sudo tee /proc/sys/net/ipv4/ip_forward
sudo sysctl net.ipv4.conf.all.rp_filter=0
sudo sysctl net.ipv4.conf.enp0s31f6.rp_filter=0
sudo sysctl net.ipv4.conf.enx506583e15eca.rp_filter=0
sudo ufw disable
