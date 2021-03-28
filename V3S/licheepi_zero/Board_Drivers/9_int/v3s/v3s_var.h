#ifndef __V3S_VAR_H
#define __V3S_VAR_H

/*
 * 自定义一些数据类型供库文件使用
 */
#define     __I     volatile 
#define     __O     volatile 
#define     __IO    volatile

#define ON 		1
#define OFF		0

#define NULL 0

#define __ASM            __asm                         	/* GNU C语言内嵌汇编关键字 */ 
#define __INLINE         inline                      	/* GNU内联关键字 */             
#define __STATIC_INLINE  static inline					


#define     __IM     volatile const      /* 只读 */
#define     __OM     volatile            /* 只写 */
#define     __IOM    volatile            /* 读写 */
#define __STRINGIFY(x) #x


typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned long     long uint64_t;
typedef	  signed char  	 	   s8;		
typedef	  signed short 	  int  s16;
typedef	  signed int 		   s32;
typedef	  signed long long int s64;
typedef	unsigned char 		   u8;
typedef	unsigned short int     u16;
typedef	unsigned int 		   u32;
typedef	unsigned long long int u64;


#endif //__V3S_VAR_H
