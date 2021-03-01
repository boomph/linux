leds.bin : leds.s
	arm-linux-gnueabihf-gcc -g -c leds.s -o leds.o
	arm-linux-gnueabihf-ld -Ttext 0x41000000 leds.o -o leds.elf
	arm-linux-gnueabihf-objcopy -O binary -S -g leds.elf leds.bin
	arm-linux-gnueabihf-objdump -D leds.elf > leds.dis

clean:
	rm -rf *.o leds.elf leds.bin leds.dis
	