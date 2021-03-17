CROSS_COMPILE 				?= arm-linux-gnueabihf-
TARGET						?= key

CC							:= $(CROSS_COMPILE)gcc
LD							:= $(CROSS_COMPILE)ld
OBJCOPY						:= $(CROSS_COMPILE)objcopy
OBJDUMP						:= $(CROSS_COMPILE)objdump




INCDIRS						:= 	bsp \
								project \
								v3s

SRCDIRS						:= 	bsp \
								project \
								v3s


# -I bsp -I project -I v3s
INCLUDS						:= $(patsubst %,-I %,$(INCDIRS))								



VPATH						:= $(SRCDIRS)


# project/start.S
SFILES						:= $(foreach dir,$(SRCDIRS),$(wildcard dir/*.S))

# project/main.c bsp/v3s_gpio.c
CFILES						:= $(foreach dir,$(SRCDIRS),$(wildcard dir/*.c))


# start.S
SFILESNDIR					:= $(notdir $(SFILES))

# main.c v3s_gpio.c
CFILESNDIR					:= $(notdir $(CFILES))


# key.bin : obj/start.o obj/v3s_gpio.o
# $(TARGET).bin : 


.PHONEY:clean


print:
	@echo INCLUDS = $(INCLUDS)
	@echo VPATH = $(VPATH)
	@echo SFILES = $(SFILES)
	@echo CFILES = $(CFILES)
	@echo SFILESNDIR = $(SFILESNDIR)
	@echo CFILESNDIR = $(CFILESNDIR)



clean:
	rm -rf $(TARTGET).bin $(TARTGET).elf $(TARTGET).dis