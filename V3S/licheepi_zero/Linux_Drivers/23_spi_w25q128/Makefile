kernel_paths := /home/royal/licheepi/zero/linux/linux-licheepi-zero
module_paths := /home/royal/myGit/linux/V3S/licheepi_zero/Linux_Drivers/23_spi_w25q128

obj-m := w25q128.o

build := w25q128_m_ko

w25q128_m_ko:
	$(MAKE) -C $(kernel_paths) M=$(module_paths) modules

clean:
	$(MAKE) -C $(kernel_paths) M=$(module_paths) clean
