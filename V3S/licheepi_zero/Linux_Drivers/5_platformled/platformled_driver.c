#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include "v3s_gpio.h"


#define PLATFORMLED_DRIVER_NAME "platformled"


struct {
    dev_t dev_t;
    struct cdev cdev;
    struct class* pClass;
    struct device* pDevice;
}rr_led_device;


static int platformled_open(struct inode *inode, struct file *filp)
{
    int ret = 0;
    return ret;
}

static int platformled_release(struct inode *inode, struct file *filp)
{
    int ret = 0;
    return ret;
}

static ssize_t platformled_read(struct file *file, 
            char __user *buf, 
            size_t count,
			loff_t *ppos)
{
    int ret =0;
    return ret;
}

static ssize_t platformled_write(struct file *file, const char __user *buf,
						size_t count, loff_t *ppos)
{
    int ret = 0;
    return ret;
}

static const struct file_operations platformled_fops={
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


    return ret;

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