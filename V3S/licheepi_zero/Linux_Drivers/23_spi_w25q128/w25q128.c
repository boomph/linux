#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/of.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>


#define W25Q128_NAME "w25q128"
#define W25Q128_CNT     1





static const struct file_operations w25q128_ops = {
    .owner      = THIS_MODULE,    

};

static struct w25q128_dat_type{
    dev_t   dev_t;
    struct cdev    cdev;
    struct class* pclass;
    struct device*  pdev;
    struct spi_device* pSPI;
    struct device_node* pSPI_CTRL_node;//SPI控制器节点
    int cs_gpio;
}w25q128_dat;

//SPI寄存器读
static int w25q128_read_regs(struct w25q128_dat_type* obj, void* reg, void* buf, unsigned len)
{
    int ret = 0;
    struct spi_transfer    trans;
    struct spi_message     mess;
    u8* txbuf = NULL;

    //动态内存分配
    txbuf= kzalloc(len,GFP_KERNEL);
    if(IS_ERR(txbuf)){
        ret = PTR_ERR(txbuf);
        printk("err1: w25q128_read_regs.\r\n");
        goto fail_kzalloc_txbuf;
    }

    //片选：拉低//////////////////////////
    gpio_set_value(obj->cs_gpio,0);

    //第一步，发送要读取的寄存器地址    
    trans.tx_buf    = reg;
    trans.len       = 1;

    spi_message_init(&mess);
    spi_message_add_tail(&trans,&mess);
    ret = spi_sync(obj->pSPI,&mess);
    if(ret < 0){
        printk("err2: w25q128_read_regs.\r\n");
        goto fail_spi_sync1;
    }

    //第二步，读取数据，SPI是全双工，读取时要写入任意数据
    txbuf[0] = 0xff;        //无效数据
    trans.tx_buf    = txbuf;
    trans.rx_buf    = buf;
    trans.len       = len;

    spi_message_init(&mess);
    spi_message_add_tail(&trans,&mess);
    ret = spi_sync(obj->pSPI,&mess);
    if(ret < 0){
        printk("err3: w25q128_read_regs.\r\n");
        goto fail_spi_sync2;
    }

    //取消片选：拉高//////////////////////
    gpio_set_value(obj->cs_gpio,1);


    kfree(txbuf);
    return ret;

fail_spi_sync2:
fail_spi_sync1:
    kfree(txbuf);

fail_kzalloc_txbuf:
    return ret;
}

//SPI寄存器写
static int w25q128_write_regs(struct w25q128_dat_type* obj, void* reg, void* buf, unsigned len)
{
    int ret = 0;
    struct spi_transfer    trans;
    struct spi_message     mess;

   

    //片选：拉低//////////////////////////
    gpio_set_value(obj->cs_gpio,0);

    //第一步，发送要读取的寄存器地址    
    trans.tx_buf    = reg;
    trans.len       = 1;

    spi_message_init(&mess);
    spi_message_add_tail(&trans,&mess);
    ret = spi_sync(obj->pSPI,&mess);
    if(ret < 0){
        printk("err1: w25q128_write_regs.\r\n");
        goto fail_spi_sync1;
    }

    //第二步，读取数据，SPI是全双工，读取时要写入任意数据
    //txbuf[0] = 0xff;        //无效数据
    //trans.tx_buf    = txbuf;
    trans.tx_buf    = buf;
    trans.len       = len;

    spi_message_init(&mess);
    spi_message_add_tail(&trans,&mess);
    ret = spi_sync(obj->pSPI,&mess);
    if(ret < 0){
        printk("err2: w25q128_write_regs.\r\n");
        goto fail_spi_sync2;
    }

    //取消片选：拉高//////////////////////
    gpio_set_value(obj->cs_gpio,1);


    
    return ret;

fail_spi_sync2:
fail_spi_sync1:
//fail_kzalloc_txbuf:
    return ret;
}

//SPI设备：w25q128 初始化
static void spi_w25q128_init(struct w25q128_dat_type* obj){
    //读取JEDEC ID      9F 
    u8  reg = 0x9F;
    u8  buf[256] = {'\0'};

    w25q128_read_regs(obj, &reg, buf, 3);

    printk("manufactureID=%X\r\n ID=%X\r\n ID2=%X\r\n",buf[0],buf[1],buf[2]);
}

static int w25q128_spi_probe(struct spi_device *spi)
{
    int ret = 0;
    printk("debug:  w25q128_spi_probe.\r\n");

    //搭建字符设备驱动框架
    /* 
        注册字符设备 ********************************************************
    */
    //申请主从设备号
    ret = alloc_chrdev_region(&w25q128_dat.dev_t,0,W25Q128_CNT,W25Q128_NAME); 
    if(ret < 0 )
    {
        printk("error: alloc_chrdev_region.\r\n");
        goto fail_alloc_chrdev_region;
    }else
    {
        printk("okay: alloc_chrdev_region,major = %d,minor = %d.\r\n",
            MAJOR(w25q128_dat.dev_t),
            MINOR(w25q128_dat.dev_t));
    }



    //初始化cdev结构
    cdev_init(&w25q128_dat.cdev,&w25q128_ops);
    w25q128_dat.cdev.owner = THIS_MODULE;
    printk("okey: cdev_init.\r\n");
    
    //注册字符设备
    ret = cdev_add(&w25q128_dat.cdev,w25q128_dat.dev_t,W25Q128_CNT);
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
    w25q128_dat.pclass = class_create(w25q128_dat.cdev.owner,W25Q128_NAME);
    if(IS_ERR(w25q128_dat.pclass)){
        ret = PTR_ERR(w25q128_dat.pclass);
        printk("err: fail_class_create.\r\n");
        goto fail_class_create;
    }

    //创建设备节点
    w25q128_dat.pdev = device_create(w25q128_dat.pclass,NULL,
        w25q128_dat.dev_t,NULL,W25Q128_NAME);
    if(IS_ERR(w25q128_dat.pdev)){
        ret = PTR_ERR(w25q128_dat.pdev);
        printk("err: fail_device_create.\r\n");
        goto fail_device_create;
    }

    //初始化spi，设备mode
    // spi->mode = SPI_MODE_3;
    // spi_setup(spi);

    //保存 struct spi_device *spi
    w25q128_dat.pSPI = spi;


    /* 获取片选引脚 pc2 **********************************************************/
    //取得SPI控制器（适配器）节点
    w25q128_dat.pSPI_CTRL_node = of_get_parent(spi->dev.of_node);
    if(IS_ERR(w25q128_dat.pSPI_CTRL_node)){
        ret = PTR_ERR(w25q128_dat.pSPI_CTRL_node);
        printk("err: fail_get_pSPI_CTRL_node.\r\n");
        goto fail_get_pSPI_CTRL_node;
    }

    //在SPI控制器中获取cs-gpio属性，用到了设备树，pinctrl,gpio子系统
    w25q128_dat.cs_gpio = of_get_named_gpio(w25q128_dat.pSPI_CTRL_node,"cs-gpio",0);
    if(!gpio_is_valid(w25q128_dat.cs_gpio)){
        ret = -ENODEV;
        printk("err: fail_get_cs_gpio.\r\n");
        goto fail_get_cs_gpio;
    }else
    {
        printk("debug:of_get_named_gpio = %d .\r\n", w25q128_dat.cs_gpio);
    }

    /* gpio子系统操作示例 *********************************************************/
    //申请gpio
    ret = gpio_request(w25q128_dat.cs_gpio,"cs");
    if(ret < 0)
    {
        printk("err: fail_gpio_request.\r\n");
        goto fail_gpio_request;
    }

    //gpio设置为输出，默认高电平
    ret = gpio_direction_output(w25q128_dat.cs_gpio,1);
    if(ret < 0)
    {
        printk("err: fail_gpio_direction_output.\r\n");
        goto fail_gpio_direction_output;
    }
    gpio_set_value(w25q128_dat.cs_gpio,1);
    mdelay(200);
    

    /* SPI设备 w25q128 初始化 ****************************************************/
    spi_w25q128_init(&w25q128_dat);

    return ret;



fail_gpio_direction_output:
    gpio_free(w25q128_dat.cs_gpio);
fail_gpio_request:
fail_get_cs_gpio:    
fail_get_pSPI_CTRL_node:
    device_destroy(w25q128_dat.pclass,w25q128_dat.dev_t);
fail_device_create:
    class_destroy(w25q128_dat.pclass);
fail_class_create:
fail_cdev_add:
    unregister_chrdev_region(w25q128_dat.dev_t,W25Q128_CNT);
fail_alloc_chrdev_region:

    return ret;


}

static int w25q128_spi_remove(struct spi_device *spi)
{
    int ret = 0;
    printk("debug:  w25q128_spi_remove.\r\n");

    gpio_free(w25q128_dat.cs_gpio);
    device_destroy(w25q128_dat.pclass,w25q128_dat.dev_t);
    class_destroy(w25q128_dat.pclass);
    unregister_chrdev_region(w25q128_dat.dev_t,W25Q128_CNT);

    return ret;
}

//传统匹配
static const struct spi_device_id w25q128_id_table[] = {
    {"rr,w25q128", 0},
    { }
};

//设备树匹配
static const struct of_device_id w25q128_of_match[] = {
	{ .compatible = "rr,w25q128", },
	{ }
};

//spi_driver
static struct spi_driver w25q128_spi_driver = {
	.driver = {
        .owner = THIS_MODULE,
		.name	= "w25q128",
		.of_match_table = w25q128_of_match,
	},
	.probe		= w25q128_spi_probe,
	.remove		= w25q128_spi_remove,
    .id_table   = w25q128_id_table,
};

static int __init w25q128_init(void)
{
    int ret = spi_register_driver(&w25q128_spi_driver);
    if(ret)
    {
        printk("err:w25q128_init.spi_register_driver.\r\n");
    }
    return ret;
}

static void __exit w25q128_exit(void)
{
    spi_unregister_driver(&w25q128_spi_driver);
}

module_init(w25q128_init);
module_exit(w25q128_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("RR");