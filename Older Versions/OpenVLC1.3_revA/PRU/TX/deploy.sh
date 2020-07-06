#! /bin/bash

echo "-Placing the firmware"
	if [[ "$(echo $(uname -r))" == "4.14"* ]]
	then
		cp gen/main_pru1_fw.out /lib/firmware
	else
		cp gen/main_pru1_fw.out /lib/firmware/am335x-pru1-fw
	fi
	

echo "-Configuring pinmux"
	config-pin -a P8_45 pruout
	config-pin -q P8_45

echo "Loading PRU"
	
	if [[ "$(echo $(uname -r))" == "4.14"* ]]
	then
			echo 'stop' | sudo tee /sys/class/remoteproc/remoteproc2/state
			echo 'main_pru1_fw.out' | sudo tee /sys/class/remoteproc/remoteproc2/firmware
			echo 'start' | sudo tee /sys/class/remoteproc/remoteproc2/state
	else
			echo "4a338000.pru1"  > /sys/bus/platform/drivers/pru-rproc/unbind 2> /dev/null
			echo "4a338000.pru1" > /sys/bus/platform/drivers/pru-rproc/bind
	fi
	

echo "Done. TX loaded into the PRU"
