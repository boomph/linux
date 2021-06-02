#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/of.h>
#include <linux/device.h>

static int at24c02_i2c_probe(struct i2c_client* client,
                            const struct i2c_device_id* id)
{
    int ret = 0;
    return ret;
}

static int at24c02_i2c_remove(struct i2c_client *client)
{
    int ret = 0;
    return ret;
}


//有设备树
static const struct of_device_id of_match_table[] = {
    { .compatible = "rr,at24c02-i2c",},
    {},
};

//无设备树时，传统方式
static const struct i2c_device_id at24c02_i2c_id[] = {
    {"rr,at24c02-i2c",0},
    {},
};


static struct i2c_driver at24c02_i2c_driver = {
    .driver = {
        .owner = THIS_MODULE,
        .name = "at24c02_i2c_driver.driver.name",
        .of_match_table = of_match_ptr(of_match_table),
    },
    .probe = at24c02_i2c_probe,
    .remove = at24c02_i2c_remove,
    .id_table = at24c02_i2c_id,
};




static int __init at24c02_i2c_init(void)
{
	return i2c_add_driver(&at24c02_i2c_driver);
}

static void __exit at24c02_i2c_exit(void)
{
    i2c_del_driver(&at24c02_i2c_driver);
}

module_init(at24c02_i2c_init);
module_exit(at24c02_i2c_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("RR");