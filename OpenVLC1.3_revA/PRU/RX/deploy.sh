#! /bin/bash

echo "-Placing the firmware"
	cp gen/main_pru0_fw.out /lib/firmware/am335x-pru0-fw
	cp gen/main_pru1_fw.out /lib/firmware/am335x-pru1-fw

echo "-Configuring pinmux"
	config-pin -a P9_30 pruin # MISO PD
	config-pin -a P9_31 pruout # CS PD
	config-pin -a P9_28 pruout # MOSI PD
	config-pin -q P9_30
	config-pin -q P9_31
	config-pin -q P9_28

echo "-Rebooting"
	
	echo "Rebooting pru-core 0"
	echo "4a334000.pru0" > /sys/bus/platform/drivers/pru-rproc/unbind 2>/dev/null
	echo "4a334000.pru0" > /sys/bus/platform/drivers/pru-rproc/bind
	
	echo "Rebooting pru-core 1"
	echo "4a338000.pru1"  > /sys/bus/platform/drivers/pru-rproc/unbind 2> /dev/null
	echo "4a338000.pru1" > /sys/bus/platform/drivers/pru-rproc/bind
	

echo "Done. RX loaded into the PRU"
