
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/of.h>


#define dtsled_name             "dtsled"
#define DTSLED_MINORS           1

struct {
    dev_t           dev_t;
    struct class*   pdtsled_class;
    struct cdev     cdev;
    struct device*  pdev;
    struct device_node* pNode;
}rr_dev_obj;

static ssize_t dtsled_read(struct file *file, char __user *buf, size_t count,
		loff_t *offset)
{
    int ret = 0;
    printk("debug: dtsled_read.\r\n");
    return ret;
}

static ssize_t dtsled_write(struct file *file, const char __user *buf,
		size_t count, loff_t *offset)
{
    int ret = 0;
    printk("debug: dtsled_write.\r\n");
    return ret;
}

static int dtsled_open(struct inode *inode, struct file *file)
{
    int ret = 0;
    printk("debug: dtsled_open.\r\n");
    return ret;
}

static int dtsled_release(struct inode *inode, struct file *file)
{
    int ret = 0;
    printk("debug: dtsled_release.\r\n");
    return ret;
}

static const struct file_operations dtsled_fops = {
    .owner          = THIS_MODULE,
    .read           = dtsled_read,
    .write          = dtsled_write,
    .open           = dtsled_open,
    .release        = dtsled_release,
};

static int __init dtsled_init(void)
{
    int ret;

    printk("call dtsled_init.\r\n");


    
    /* 
        注册字符设备 ********************************************************
    */
    //申请主从设备号
    ret = alloc_chrdev_region(&rr_dev_obj.dev_t,0,DTSLED_MINORS,dtsled_name); 
    if(ret < 0 )
    {
        printk("error: alloc_chrdev_region.\r\n");
        goto fail_alloc_chrdev_region;
    }else
    {
        printk("okay: alloc_chrdev_region,major = %d,minor = %d.\r\n",
            MAJOR(rr_dev_obj.dev_t),
            MINOR(rr_dev_obj.dev_t));
    }

#if 0
    //如果指定了主从设备号，调用
    ret = register_chrdev_region(rr_dev_obj.dev_t,DTSLED_MINORS,"dtsled_dev");
    if(ret < 0)
    {
        printk("error: register_chrdev_region.\r\n");
        goto fail_register_chrdev_region;
    }else
        printk("okey: register_chrdev_region.\r\n");
#endif

    //初始化cdev结构
    cdev_init(&rr_dev_obj.cdev,&dtsled_fops);
    rr_dev_obj.cdev.owner = THIS_MODULE;
    printk("okey: cdev_init.\r\n");
    
    //注册字符设备
    ret = cdev_add(&rr_dev_obj.cdev,rr_dev_obj.dev_t,DTSLED_MINORS);
    if(ret < 0)
    {
        printk("error: cdev_add.\r\n");
        goto fail_cdev_add;
    }else
        printk("okey: cdev_add.\r\n");


    /* 
        自动创建设备节点 ********************************************************
    */
    //创建类
    rr_dev_obj.pdtsled_class = class_create(rr_dev_obj.cdev.owner,dtsled_name);
    if(IS_ERR(rr_dev_obj.pdtsled_class)){
        ret = PTR_ERR(rr_dev_obj.pdtsled_class);
        goto fail_class_create;
    }

    //创建设备节点
    rr_dev_obj.pdev = device_create(rr_dev_obj.pdtsled_class,NULL,
        rr_dev_obj.dev_t,NULL,dtsled_name);
    if(IS_ERR(rr_dev_obj.pdev)){
        ret = PTR_ERR(rr_dev_obj.pdev);
        goto fail_device_create;
    }


    /*
    2021-5-13加入从设备树节点获取信息*******************************************
    */
    rr_dev_obj.pNode = of_find_node_by_name(NULL,"myled_pin0");
    if(IS_ERR(rr_dev_obj.pNode)){
        ret = PTR_ERR(rr_dev_obj.pNode);
        goto err1;
    }
    else{
        printk("inf: device-node.name = %s \r\n ",
                rr_dev_obj.pNode->name);
        printk("inf: device-node.pins = %s \r\n ",
                (char*)of_get_property(rr_dev_obj.pNode,"pins",NULL));
        printk("inf: device-node.function = %s \r\n ",
                (char*)of_get_property(rr_dev_obj.pNode,"function",NULL));
        printk("inf: ok \r\n");
    }
    
    
    return 0;


err1:
    device_destroy(rr_dev_obj.pdtsled_class,rr_dev_obj.dev_t);
fail_device_create:
    class_destroy(rr_dev_obj.pdtsled_class);
fail_class_create:
fail_cdev_add:
    unregister_chrdev_region(rr_dev_obj.dev_t,DTSLED_MINORS);
//fail_register_chrdev_region:
fail_alloc_chrdev_region:
    return ret;
}

static void __exit dtsled_exit(void)
{
    //注销
    device_destroy(rr_dev_obj.pdtsled_class,rr_dev_obj.dev_t);
    class_destroy(rr_dev_obj.pdtsled_class);
    unregister_chrdev_region(rr_dev_obj.dev_t,DTSLED_MINORS);
}

module_init(dtsled_init);
module_exit(dtsled_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("RR");