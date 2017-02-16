#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("36916cf4feae");

static int helloworld_init(void) {
    printk(KERN_DEBUG "Hello World!\n");
    return 0;
}

static void helloworld_exit(void) {
    printk(KERN_DEBUG "Hello World! exit\n");
}

module_init(helloworld_init);
module_exit(helloworld_exit);
