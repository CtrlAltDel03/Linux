#include<linux/init.h>
#include<linux/module.h>

int ex01_simple_module_init(void)/*called when program is loaded into kernel space*/
{
	printk(KERN_ALERT "Inside the %s function",__FUNCTION__);
	return 0;
}
void ex01_simple_module_exit(void)/*called when program is removed from kernel space*/
{
	printk(KERN_ALERT "Inside the %s function",__FUNCTION__);
}

module_init(ex01_simple_module_init);/*to specify the function to be called when inserted*/
module_exit(ex01_simple_module_exit);/*to specify fn to be called when removed*/
MODULE_LICENSE("GPL");/*licence*/

