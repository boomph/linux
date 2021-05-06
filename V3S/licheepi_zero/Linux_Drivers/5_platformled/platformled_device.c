#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include "v3s_gpio.h"



static struct resource platformled_resource[] = {
    [0] = {
        .start  = PIO_BASE_ADDRESS,
        .end    = PIO_BASE_ADDRESS + sizeof(PIO_Map),
        .flags  = IORESOURCE_MEM,
    },
};

static void	platformled_device_release(struct device *dev)
{
    printk("inf:    platformled_device_release.\r\n");
}

static struct platform_device platformled_device = {
    .name = "platformled",
    .resource = platformled_resource,
    .num_resources = ARRAY_SIZE(platformled_resource),
    .dev = {
        .release = platformled_device_release,
    }
};

static int __init platformled_device_init(void)
{
    int ret = 0;
    ret = platform_device_register(&platformled_device);
    return ret;
}

static void __exit platformled_device_exit(void)
{
    platform_device_unregister(&platformled_device);
}

module_init(platformled_device_init);
module_exit(platformled_device_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("RR");

