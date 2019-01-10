sudo route add -net 192.168.6.0/24 gw 192.168.7.2
sudo route del -net 192.168.2.0/24
sudo route add -net 192.168.2.0/24 gw 192.168.7.2
echo "1" | sudo tee /proc/sys/net/ipv4/ip_forward
sudo sysctl -w net.ipv4.conf.all.rp_filter=0
sudo sysctl -w net.ipv4.conf.enx04a316b84e64.rp_filter=0
sudo sysctl -w net.ipv4.conf.enp8s0.rp_filter=0
