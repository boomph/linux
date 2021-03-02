
objs = start.o main.o v3s_gpio.o

ledc.bin : $(objs)
	arm-linux-gnueabihf-ld -Ttext 0x41000000 $^ -o ledc.elf
	arm-linux-gnueabihf-objcopy -O binary -S ledc.elf $@
	arm-linux-gnueabihf-objdump -D ledc.elf > ledc.dis


%.o : %.c
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<

%.o : %.S
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<

clean:
	rm -rf *.o ledc.bin ledc.elf ledc.dis