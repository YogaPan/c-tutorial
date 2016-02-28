#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YogaPan <godhand1234567@gmail.com>");
MODULE_DESCRIPTION("Hello!");

static int __init hello_module_init(void)
{
	printk(KERN_DEBUG "Hello World!\n");
	return 0;
}

static void __exit hello_module_exit(void)
{
	printk(KERN_DEBUG "Good Bye.\n");
}


module_init(hello_module_init);
module_exit(hello_module_exit);
