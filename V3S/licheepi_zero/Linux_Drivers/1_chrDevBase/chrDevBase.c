#include <linux/module.h>
#include <linux/printk.h>

static int __init chrDevBase_init(void)
{
    printk("chrDevBase inited!\r\n");
    return 0;
}

static void __exit charDevBase_exit(void)
{
    printk("chrDevBase exited\r\n");
    return;
}


/*
    模块入口与出口
*/

module_init(chrDevBase_init);/*入口*/
module_exit(charDevBase_exit); //出口

MODULE_LICENSE("GPL");
MODULE_AUTHOR("luo");