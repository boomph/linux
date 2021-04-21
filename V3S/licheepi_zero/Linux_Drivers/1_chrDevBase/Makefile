KERNELDIRR := /home/royal/licheepi/zero/linux/linux-licheepi-zero

CURRENT_PATHH := $(shell pwd)

obj-m := chrDevBase.o

build: kernel_moduless

kernel_moduless:
	$(MAKE) -C $(KERNELDIRR) M=$(CURRENT_PATHH) modules

clean:
	$(MAKE) -C $(KERNELDIRR) M=$(CURRENT_PATHH) clean

mytest:
	@echo MAKE = $(MAKE)