ifeq (5.15.0-76-generic,)
	KERNEL_SOURCE:= /lib/modules/$(uname -r)
	PWD:=$(shell pwd)

default:
	make -C /lib/modules/$(uname -r)/build M=$PWD modules

clean:
	make -C /lib/modules/$(uname -r)/build M=$PWD clean

else
	obj-m:=char_driver.o
endif
