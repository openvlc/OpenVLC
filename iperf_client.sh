#!/bin/bash
iperf -c 192.168.0.1 -u -b 16k -l .8k -p 10001  -t 600
