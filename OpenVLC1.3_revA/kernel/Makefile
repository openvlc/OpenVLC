
###### CONFIGURATION ######


### List of modules to be build
MODULES = openvlc


###### KERNEL MODULE BUILD (no change required normally) ######

### Default to sources of currently running kernel
KSRC ?= /lib/modules/$(shell uname -r)/build

OBJS     := ${patsubst %, %.o, $(MODULES)}
CLEANMOD := ${patsubst %, .%*, $(MODULES)}
PWD      := $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)

### Kernel 2.6 or 3.0
PATCHLEVEL:=$(shell sed 's/PATCHLEVEL = \(.*\)/\1/;t;d' $(KSRC)/Makefile)
VERSION:=$(shell sed 's/VERSION = \(.*\)/\1/;t;d' $(KSRC)/Makefile)



obj-m        := vlc.o
vlc-objs :=  reed_solomon.o openvlc.o
EXTRA_CFLAGS := -g -DCONFIG_REED_SOLOMON_ENC8 -DCONFIG_REED_SOLOMON_DEC8 -DCONFIG_REED_SOLOMON_ENC16 -DCONFIG_REED_SOLOMON_DEC16 $(ADD_CFLAGS)

all::
	$(MAKE) -C $(KSRC) SUBDIRS=$(PWD) modules


## Target for capturing 2.4 module CFLAGS
modules:
	@echo "$(CFLAGS)"

clean::
	$(RM) $(CLEANMOD) *.o *.ko *.mod.c Module*.symvers Module.markers modules.order
	$(RM) -R .tmp*
	
	
	

