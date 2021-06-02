rr_core_path 	:= /home/royal/licheepi/zero/linux/linux-licheepi-zero
rr_work_path	:= $(shell pwd)

obj-m		:= rr_24c02_driver.o

build:	rr_24c02_driver_ko
rr_24c02_driver_ko:
	$(MAKE) -C $(rr_core_path) M=$(rr_work_path) modules

clean:
	$(MAKE) -C $(rr_core_path) M=$(rr_work_path) clean

