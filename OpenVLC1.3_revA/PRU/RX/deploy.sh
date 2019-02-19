#! /bin/bash

echo "-Placing the firmware"
	if [[ "$(echo $(uname -r))" == "4.14"* ]]
	then
		cp gen/main_pru0_fw.out /lib/firmware
		cp gen/main_pru1_fw.out /lib/firmware
	else
		cp gen/main_pru0_fw.out /lib/firmware/am335x-pru0-fw
		cp gen/main_pru1_fw.out /lib/firmware/am335x-pru1-fw
	fi
		
echo "-Configuring pinmux"
	config-pin -a P8_29 pruout # debug
	config-pin -a P8_27 pruout # debug
	config-pin -a P9_30 pruin # MISO PD
	config-pin -a P9_31 pruout # CS PD
	config-pin -a P9_28 pruout # MOSI PD
	config-pin -a P8_15 pruin # MISO LL
	config-pin -a P8_12 pruout # CS LL
	config-pin -a P8_11 pruout # MOSI LL
	config-pin -q P8_29
	config-pin -q P8_27
	config-pin -q P9_30
	config-pin -q P9_31
	config-pin -q P9_28
	config-pin -q P8_15
	config-pin -q P8_12
	config-pin -q P8_11

echo "-Rebooting"
	
	
	
	if [[ "$(echo $(uname -r))" == "4.14"* ]]
	then
			echo 'stop' | sudo tee /sys/class/remoteproc/remoteproc1/state
			echo 'stop' | sudo tee /sys/class/remoteproc/remoteproc2/state
			
			echo 'main_pru0_fw.out' | sudo tee /sys/class/remoteproc/remoteproc1/firmware
			echo 'main_pru1_fw.out' | sudo tee /sys/class/remoteproc/remoteproc2/firmware
			
			echo 'start' | sudo tee /sys/class/remoteproc/remoteproc1/state
			echo 'start' | sudo tee /sys/class/remoteproc/remoteproc2/state
	else
			echo "Rebooting pru-core 0"
			echo "4a334000.pru0" > /sys/bus/platform/drivers/pru-rproc/unbind 2>/dev/null
			echo "4a334000.pru0" > /sys/bus/platform/drivers/pru-rproc/bind
			
			echo "Rebooting pru-core 1"
			echo "4a338000.pru1"  > /sys/bus/platform/drivers/pru-rproc/unbind 2> /dev/null
			echo "4a338000.pru1" > /sys/bus/platform/drivers/pru-rproc/bind
	fi
	

echo "Done. RX loaded into the PRU"
