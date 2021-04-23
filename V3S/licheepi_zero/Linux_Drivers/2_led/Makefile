LINUX_DIR := /home/royal/licheepi/zero/linux/linux-licheepi-zero
CUR_PATH := $(shell pwd)
obj-m := leddriver.o

build:	led_ko
led_ko:
	$(MAKE) -C $(LINUX_DIR) M=$(CUR_PATH) modules
clean:
	$(MAKE) -C $(LINUX_DIR) M=$(CUR_PATH) clean
