CROSS_COMPILE 				?= arm-linux-gnueabihf-
TARGET						?= int

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
SFILES						:= $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.S))

# project/main.c bsp/v3s_gpio.c
CFILES						:= $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))


# start.S
SFILESNDIR					:= $(notdir $(SFILES))

# main.c v3s_gpio.c
CFILESNDIR					:= $(notdir $(CFILES))


# SOBJS obj/start.o
SOBJS						:= $(patsubst %.S,obj/%.o,$(SFILESNDIR))

# COBJS obj/main.o v3s_gpio.o
COBJS						:= $(patsubst %.c,obj/%.o,$(CFILESNDIR))

# OBJS obj/start.o obj/main.o obj/v3s_gpio.o
OBJS						:= $(SOBJS) $(COBJS)



# key.bin : obj/start.o obj/v3s_gpio.o
$(TARGET).bin : $(OBJS)
	$(LD) -Tv3s.lds $^ -o $(TARGET).elf 
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

# obj/start.o : start.S
$(SOBJS) : obj/%.o : %.S
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDS) -o $@ $<

# obj/main.o obj/v3s_gpio.o : main.c v3s_gpio.c
$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDS) -o $@ $<




.PHONEY:clean


print:
	@echo INCLUDS = $(INCLUDS)
	@echo VPATH = $(VPATH)
	@echo SFILES = $(SFILES)
	@echo CFILES = $(CFILES)
	@echo SFILESNDIR = $(SFILESNDIR)
	@echo CFILESNDIR = $(CFILESNDIR)
	@echo SOBJS	= $(SOBJS)
	@echo COBJS	= $(COBJS)
	@echo OBJS	= $(OBJS)


clean:
	rm -rf $(TARGET).bin $(TARGET).elf $(TARGET).dis $(OBJS)

