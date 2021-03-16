CROSS_COMPILE		?= arm-linux-gnueabihf-
TARGET				?= ledc

CC					:= ${CROSS_COMPILE}gcc
LD					:= ${CROSS_COMPILE}ld
OBJCOPY				:= ${CROSS_COMPILE}objcopy
OBJDUMP				:= ${CROSS_COMPILE}objdump


#头文件目录
INCDIRS				:= 	v3s \
						bsp \
						project

#源文件目录
SRCDIRS				:= 	v3s \
						bsp \
						project

#########################################################################################
#由于Makefile 头文件用-I 指定，所以
#通过函数：patsubst 转成
# -I v3s -I bsp -I project
INCLUDE				:= 	$(patsubst %,-I %,$(INCDIRS))


#foreath wildcard#########################################################################
#化成: v3s/start.S
SFILES				:=	$(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.S))
#化成: bsp/v3s_gpio.c project/main.c
CFILES				:=	$(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))


#notdir##################################################################################
#化成: start.S
SFILESNDIR			:=	$(notdir $(SFILES))
#化成: v3s_gpio.c main.c
CFILESNDIR			:=	$(notdir $(CFILES))



########################################################################################
#化成: obj/start.o
SOBJS				:=	$(patsubst %,obj/%,$(SFILESNDIR:.S=.o))
#化成: obj/v3s_gpio.o obj/main.o
COBJS				:=	$(patsubst %,obj/%,$(CFILESNDIR:.c=.o))
#由于$(SFILESNDIR:.S=.o)不好理解，自作主张改为
MYSOBJS				:=	$(patsubst %.S,obj/%.o,$(SFILESNDIR))
MYCOBJS				:=	$(patsubst %.c,obj/%.o,$(CFILESNDIR))



########################################################################################
OBJS				:=	$(SOBJS) $(COBJS)



#######################################################################################
#搜索路径
VPATH				:=	$(SRCDIRS)



#######################################################################################
.PHONY:clean


######################################################################################
$(TARGET).bin : $(OBJS)
	$(LD) -Tv3s.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis


######################################################################################
#使用Makefile静态模式
# %.o中的%匹配 SOBJ集合中如：bsp/start.o的bsp/start
# %.S中的%取该值，即为bsp/start.S
$(SOBJS) : obj/%.o : %.S
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

######################################################################################
clean:
	rm -rf $(TARGET).elf $(TARGET).bin $(TARGET).dis $(OBJS)

print:
	@echo INCLUDE 	=	$(INCLUDE)
	@echo SFILES 	=	$(SFILES)
	@echo CFILES	= 	$(CFILES)
	@echo SFILESNDIR=	$(SFILESNDIR)
	@echo CFILESNDIR=	$(CFILESNDIR)
	@echo SOBJS	=	$(SOBJS)
	@echo COBJS	=	$(COBJS)
	@echo MYSOBJS	= 	$(MYSOBJS)
	@echo MYCOBJS	=	$(MYCOBJS)
	@echo OBJS	= 	$(OBJS)




