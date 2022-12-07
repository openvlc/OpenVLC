#! /bin/bash

##############################################################################
#
# Copyright (C) 2016 Zubeen Tolani <ZeekHuge - zeekhuge@gmail.com>
# IMDEA NETWORKS Institute: This file has been modified and it is part of the OpenVLC's source codes
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#	* Redistributions of source code must retain the above copyright
#	  notice, this list of conditions and the following disclaimer.
#
#	* Redistributions in binary form must reproduce the above copyright
#	  notice, this list of conditions and the following disclaimer in the
#	  documentation and/or other materials provided with the
#	  distribution
#
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#############################################################################


# The script builds the pru_blinky project and configures the pinmuxing for $HEADER$PIN_NUM

#If changing these variables, make sure the given pin can be muxed to the given pru.  
HEADER=P8_
PIN_NUMBER=45
#PRU_CORE should be either 0 or 1
PRU_CORE=1

export PRU_CGT=/usr/share/ti/cgt-pru
find -exec touch \{\} \;

echo "-Building project"
	make clean
	make

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
	config-pin -a P8_46 pruout
	config-pin -q P8_46

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
	
	

echo "Done. Blikny must be up on pin $HEADER$PIN_NUMBER"
