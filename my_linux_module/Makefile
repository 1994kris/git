#!/bin/bash
obj-m += gpio.o
KDIR := /home/d/Android4.0/iTop4412_Kernel_3.0
PWD ?= $(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.o
