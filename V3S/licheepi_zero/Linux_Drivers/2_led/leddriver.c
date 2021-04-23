#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include "v3s_gpio.h"
#include <linux/io.h>
#include <linux/uaccess.h>

#define LED_MAJOR   200
#define LED_MINOR   200
#define LED_DEV_NAME    "ledDevice"

static int major = -1;
static void __iomem* VA_PIO = NULL;
static PIO_Map         *PIO = NULL;
static char bufFromUser[1024];

static void GPIO_Init(PIO_PORT port, unsigned int pin, PIO_MODE mode, PIO_DRV drv, PIO_PULL pul)
{    
    unsigned int cfgIndex =0;
    unsigned int drvIndex =0;
    unsigned int pulIndex =0;

    if(VA_PIO <= 0)
        return;

    PIO = (PIO_Map*)VA_PIO;             //结构指向基地址

    /* 
        配置GPIO复用功能 :
        确定 CFG索引号
        以PIN7为例，7/8 = 0，即CFG[索引]=0 
    */
    cfgIndex = pin / 8 ;               


    /* 
        以PIN7为例，28-30位即 7 % 8 * 4 = 28，清除3位，再置位
    */
    PIO->Pn[port].CFG[cfgIndex] &= ~( ((unsigned int) 0x07) << ((pin % 8) * 4));
    PIO->Pn[port].CFG[cfgIndex] |= (((unsigned int)mode) << ((pin % 8) * 4));



    /* 
        配置GPIO的电气属性：
        设置驱动等级
        确定 DRV索引号
        以PIN15为例，15 / 16 =0；即DRV[索引]=0
    */
   drvIndex = pin / 16;

   /* 
        以PIN15为例，2*i+1 : 2*i 位即 2*15+1 : 2*15 = 31 : 30 ，清除2位，再置位
    */
   PIO->Pn[port].DRV[drvIndex] &= ~(((unsigned int)0x03) << ((pin % 16) * 2));
   PIO->Pn[port].DRV[drvIndex] |= (((unsigned int)drv) << ((pin % 16) * 2));


   /* 
        配置GPIO的电气属性：
        设置上下拉
        确定 PUL索引号
        以PIN15为例，15 / 16 =0；即PUL[索引]=0
    */
   pulIndex = pin / 16;

   /* 
        以PIN15为例，2*i+1 : 2*i 位即 2*15+1 : 2*15 = 31 : 30 ，清除2位，再置位
    */
   PIO->Pn[port].PUL[pulIndex] &= ~(((unsigned int)0x03) << ((pin % 16) * 2));
   PIO->Pn[port].PUL[pulIndex] |= (((unsigned int)pul) << ((pin % 16) * 2));
}


static void GPIO_SetPin(PIO_PORT port, unsigned int pin){
    if(PIO == NULL)
        return;

    PIO->Pn[port].DAT |= (1 << pin);
}

static void GPIO_ResetPin(PIO_PORT port, unsigned int pin){
    if(PIO == NULL)
        return;

    PIO->Pn[port].DAT &= ~(1 << pin);
}

static ssize_t led_read(struct file *filp, __user char __user *buf, size_t count, loff_t *ppos)
{
    ssize_t ret=0;
    printk("led_read .\r\n");
    return ret;
}

static ssize_t led_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
    ssize_t ret=0;
    int countFrom=0;
    printk("led_write .\r\n");

    //
    countFrom = copy_from_user(bufFromUser,buf,count);
    if(countFrom < 0 )
    {
        printk("err:led_write->copy_from_user .\r\n");
        return -EIO;
    }

    if(bufFromUser[0] == 0)
        GPIO_ResetPin(PIO_PORT_B,3);
    else
        GPIO_SetPin(PIO_PORT_B,3);

    return ret;
}

static int led_open (struct inode * pInode, struct file *pFile)
{
    printk("led_open .\r\n");    
    return 0;
}

static int led_close (struct inode *pInode, struct file *pFile)
{
    printk("led_close .\r\n");
    return 0;
}

static const struct file_operations led_ko_fops = {
    .owner  = THIS_MODULE,
    .read   = led_read,
    .write  = led_write,
    .open   = led_open,
    .release    = led_close,
};

static int __init led_ko_init(void)
{
    //注册字符设备
    major = register_chrdev(LED_MAJOR,LED_DEV_NAME,&led_ko_fops);
    if(major < 0){
        printk("err: led_ko_init->register_chrdev .\r\n");
        return major;
    }
    else
    {
        printk("注册字符设备成功。\r\n");
    }

    //物地转虚地
    VA_PIO = ioremap(PIO_BASE_ADDRESS,sizeof(PIO_Map));
    if(VA_PIO < 0){
        printk("err: led_ko_init->ioremap .\r\n");
        return major;
    }else
    {
        printk("物地转虚地:%x:%x\r\n",
            (unsigned int)PIO_BASE_ADDRESS,
            (unsigned int)VA_PIO);
    }

    //init pb3 输出，HIGH点亮LED
    GPIO_Init(PIO_PORT_B,3,PIO_MODE_OUT,PIO_DRV_LEVEL1,PIO_PULL_DISABLE);
    
    
    return 0;
}

static void __exit led_ko_exit(void)
{
    //注销字符设备
    if(major >= 0 )
    {
        unregister_chrdev(major,LED_DEV_NAME);
        printk("注销字符设备。\r\n");
    }

    if(VA_PIO > 0)
    {
        iounmap(VA_PIO);
        printk("释放虚拟地址。\r\n");
    }
}

/*
模块入口、出口
*/
module_init(led_ko_init);
module_exit(led_ko_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("RR");