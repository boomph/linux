#include <linux/module.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/kdev_t.h>

#define TEST_DEV_MAJOR  200
#define TEST_DEV_MINOR  200

static const char* mychrdevname="mychrdev";


static int mychrdev_open  (struct inode *inode, struct file *file)
{
    printk("mychrdev_open. \r\n");
    return 0;
}

static int mychrdev_release (struct inode *inode, struct file *file)
{
    printk("mychrdev_open. \r\n");
    return 0;
}

static ssize_t mychrdev_read  (struct file *file, char __user * buf, 
                        size_t size, loff_t *pos)
{
    ssize_t ret = 0;
    printk("mychrdev_read. \r\n");
    return ret;
}

static ssize_t mychrdev_write (struct file *file, const char __user * buf,
                         size_t size, loff_t *pos)
{
    ssize_t ret = 0;
    printk("mychrdev_write. \r\n");
    return ret;
}

static const struct file_operations myfops = {
    .owner      = THIS_MODULE,   // 在 linux/export.h
    .open       = &mychrdev_open,
    .release    = &mychrdev_release,
    .read       = &mychrdev_read,
    .write      = &mychrdev_write
};

static int __init chrDevBase_init(void)
{
    printk("模块入口module_init(chrDevBase_init)被调用.\r\n");

    /*
        注册字符设备 
        register_chrdev file_operations 在 include\linux\fs.h
        cat /proc/devices查可用的主设备号
    */
    register_chrdev(TEST_DEV_MAJOR,mychrdevname,&myfops);

    return 0;
}

static void __exit chrDevBase_exit(void)
{
    printk("模块出口module_exit(chrDevBase_exit)被调用.\r\n");
    /*
        注销注册字符设备 
        unregister_chrdev 在 include\linux\fs.h
    */
    unregister_chrdev(TEST_DEV_MAJOR,mychrdevname);
    return;
}


/*
    模块入口与出口
*/

module_init(chrDevBase_init);/*入口*/
module_exit(chrDevBase_exit); //出口

MODULE_LICENSE("GPL");
MODULE_AUTHOR("luo");