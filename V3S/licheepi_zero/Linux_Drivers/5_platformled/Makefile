RR_KERNELPATH 	:= /home/royal/licheepi/zero/linux/linux-licheepi-zero
RR_WORKPATH	:= $(shell pwd)

obj-m		:= platformled_device.o platformled_driver.o

build:	platformled_ko
platformled_ko:
	$(MAKE) -C $(RR_KERNELPATH) M=$(RR_WORKPATH) modules
	
clean:
	$(MAKE) -C $(RR_KERNELPATH) M=$(RR_WORKPATH) clean