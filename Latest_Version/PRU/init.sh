# IMDEA NETWORKS Institute: This file has been modified and it is part of the OpenVLC's source codes
export PRU_CGT=/usr/share/ti/cgt-pru
export PRU_SUPPORT=/opt/source/pru-software-support-package
cd $PRU_CGT
mkdir -p bin
cd bin
ln -s `which clpru`  .
ln -s `which lnkpru` .