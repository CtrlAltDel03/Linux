#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>

static int __init ofd_init(void) 
{
    printk(KERN_INFO "halo: registr");

    return 0;
}

static void __exit ofd_exit(void) 
{
    printk(KERN_INFO "tata: unregistr");
}

module_init(ofd_init);
module_exit(ofd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abhinav <abhinavgollapalli@gmail.com>");
MODULE_DESCRIPTION("Our First Driver");
/*makefile invoked the makefile of the driver   and directs the driver into the kernel space*/