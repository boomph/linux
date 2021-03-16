CROSS_COMPILE		?= arm-linux-gnueabihf-
TARGET				?= ledc

CC					:= ${CROSS_COMPILE}gcc
LD					:= ${CROSS_COMPILE}ld
OBJCOPY				:= ${CROSS_COMPILE}objcopy
OBJCUMP				:= ${CROSS_COMPILE}objdump

INCDIRS				:= 	v3s \
						bsp \
						project

SRCDIRS				:= 	v3s \
						bsp \
						project

#由于Makefile 头文件用-I 指定，所以
#通过函数：patsubst 转成
# -I v3s -I bsp -I project
INCLUDE				:= 	$(patsubst %,-I %,$(INCDIRS))



SFILES				:=	${foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.S))
CFILES				:=	$(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))

print:
	@echo INCLUDE 	=	$(INCLUDE)
	@echo SFILES 	=	$(SFILES)
	@echo CFILES	= 	$(CFILES)





