#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include "v3s_gpio.h"


#define PLATFORMLED_DRIVER_NAME "platformled"


static struct {
    dev_t dev_t;
    struct cdev cdev;
    struct class* pClass;
    struct device* pDevice;
    struct platform_device* pPlatform_Device;
    struct resource* pRes_mem;
    void __iomem *va_pio;
}rr_led_device;


static void GPIO_Init(PIO_PORT port, unsigned int pin, PIO_MODE mode, PIO_DRV drv, PIO_PULL pul)
{    
    unsigned int cfgIndex =0;
    unsigned int drvIndex =0;
    unsigned int pulIndex =0;
    PIO_Map* PIO;

    if(rr_led_device.va_pio <= 0)
        return;

    PIO = (PIO_Map*)rr_led_device.va_pio;             //结构指向基地址

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
    PIO_Map* PIO;

    if(rr_led_device.va_pio <= 0)
        return;

    PIO = (PIO_Map*)rr_led_device.va_pio;

    PIO->Pn[port].DAT |= (1 << pin);
}

static void GPIO_ResetPin(PIO_PORT port, unsigned int pin){
    PIO_Map* PIO;

    if(rr_led_device.va_pio <= 0)
        return;

    PIO = (PIO_Map*)rr_led_device.va_pio;

    PIO->Pn[port].DAT &= ~(1 << pin);
}

static int platformled_open(struct inode *inode, struct file *filp)
{
    int ret = 0;
    
    /* 保存私有数据 */
    filp->private_data = &rr_led_device;
    
    printk("platformled_open.\r\n");
    return ret;
}

static int platformled_release(struct inode *inode, struct file *filp)
{
    int ret = 0;

    printk("platformled_release.\r\n");
    return ret;
}

static ssize_t platformled_read(struct file *file, 
            char __user *buf, 
            size_t count,
			loff_t *ppos)
{
    int ret =0;

    printk("platformled_read.\r\n");
    return ret;
}

static ssize_t platformled_write(struct file *file, const char __user *buf,
						size_t count, loff_t *ppos)
{
    ssize_t ret = 0;
    int countFrom=0;
    char bufFromUser[32];
    printk("platformled_write.\r\n");
    

    //
    countFrom = copy_from_user(bufFromUser,buf,count);
    if(countFrom < 0 )
    {
        printk("err:    platformled_write->copy_from_user .\r\n");
        return -EIO;
    }

    if(bufFromUser[0] == 0)
        GPIO_ResetPin(PIO_PORT_B,3);
    else
        GPIO_SetPin(PIO_PORT_B,3);

    return ret;
}

static const struct file_operations platformled_fops={
    .owner      = THIS_MODULE,
    .open       = platformled_open,
    .release    = platformled_release,
    .read       = platformled_read,
    .write      = platformled_write,
};

static int platformled_driver_probe(struct platform_device* pdev){
    int ret = 0;
    
    printk("inf:    platformled_driver_probe.\r\n");

    /* 申请主从设备号 */
    ret = alloc_chrdev_region(&rr_led_device.dev_t,
        0,1,PLATFORMLED_DRIVER_NAME);
    if(ret < 0)
        goto err1;
    else
        printk("platformled_driver_probe:    alloc_chrdev_region.\r\n");


    /* 注册字符设备 */
    cdev_init(&rr_led_device.cdev,&platformled_fops);
    ret = cdev_add(&rr_led_device.cdev,rr_led_device.dev_t,1);
    if(ret < 0)
        goto err2;
    else
        printk("platformled_driver_probe:    cdev_init  cdev_add.\r\n");


    /* 自动创建设备节点 */
    rr_led_device.pClass = class_create(THIS_MODULE,PLATFORMLED_DRIVER_NAME);
    if(IS_ERR(rr_led_device.pClass))
    {
        ret = PTR_ERR(rr_led_device.pClass);
        goto err3;
    }
    else
        printk("platformled_driver_probe:    class_create.\r\n");

    rr_led_device.pDevice = device_create(rr_led_device.pClass,NULL,
        rr_led_device.dev_t,NULL,PLATFORMLED_DRIVER_NAME);
    if(IS_ERR(rr_led_device.pDevice))
    {
        ret = PTR_ERR(rr_led_device.pDevice);
        goto err4;
    }
    else
        printk("platformled_driver_probe:    device_create.\r\n");


    /*保存platform_device指针*/
    rr_led_device.pPlatform_Device = pdev;

    /* 获取设备资源 */
    rr_led_device.pRes_mem = platform_get_resource(pdev,IORESOURCE_MEM,0);
    if(!rr_led_device.pRes_mem){
        ret = -ENODEV;
        goto err5;
    }
    else        
        printk("platformled_driver_probe:    platform_get_resource.\r\n");
    
    /* 内存映射 */
    rr_led_device.va_pio = ioremap(rr_led_device.pRes_mem->start,resource_size(rr_led_device.pRes_mem));
    if(rr_led_device.va_pio <= 0)
    {
        ret = -ENOMEM;
        goto err6;
    }
    else
        printk("物地转虚地:%x:%x\r\n",
            (unsigned int)rr_led_device.pRes_mem->start,
            (unsigned int)rr_led_device.va_pio);


    //init pb3 输出，HIGH点亮LED
    GPIO_Init(PIO_PORT_B,3,PIO_MODE_OUT,PIO_DRV_LEVEL1,PIO_PULL_DISABLE);
    printk("platformled_driver_probe:    GPIO_Init.\r\n");
    
    return ret;

err6:
err5:
err4:
    class_destroy(rr_led_device.pClass);
err3:
    cdev_del(&rr_led_device.cdev);
err2:
    unregister_chrdev_region(rr_led_device.dev_t,1);
err1:    
    return ret;
}

static int platformled_driver_remove(struct platform_device* pdev){
    int ret = 0;
    
    iounmap(rr_led_device.va_pio);
    printk("platformled_driver_remove:    iounmap.\r\n");

    device_destroy(rr_led_device.pClass,rr_led_device.dev_t);
    printk("platformled_driver_remove:    device_destroy.\r\n");

    class_destroy(rr_led_device.pClass);
    printk("platformled_driver_remove:    class_destroy.\r\n");

    cdev_del(&rr_led_device.cdev);
    printk("platformled_driver_remove:    cdev_del.\r\n");

    unregister_chrdev_region(rr_led_device.dev_t,1);
    printk("platformled_driver_remove:    unregister_chrdev_region.\r\n");


    printk("info:    platformled_driver_remove.\r\n");
    return ret;
}

static struct platform_driver platformled_driver = {
    .driver.name    =   PLATFORMLED_DRIVER_NAME,
    .probe          =   platformled_driver_probe,
    .remove         =   platformled_driver_remove,
};


static int __init platformled_driver_init(void){
    
    return platform_driver_register(&platformled_driver);
    
}

static void __exit platformled_driver_exit(void){
    platform_driver_unregister(&platformled_driver);
}

module_init(platformled_driver_init);
module_exit(platformled_driver_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("RR");