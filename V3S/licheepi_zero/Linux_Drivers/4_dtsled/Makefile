RR_KERNELPATH := /home/royal/licheepi/zero/linux/linux-licheepi-zero
RR_MODULEPATH := $(shell pwd)

obj-m := dtsled.o

build:	rr_dtsled_ko
rr_dtsled_ko:
	$(MAKE) -C $(RR_KERNELPATH) M=$(RR_MODULEPATH) modules

clean:
	$(MAKE) -C $(RR_KERNELPATH) M=$(RR_MODULEPATH) clean