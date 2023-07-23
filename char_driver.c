#include<linux/fs.h>/*register range of major minor*/
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>
#include <linux/device.h>
#include <linux/cdev.h>

static dev_t first;/*variable for device number containing major minor*/
static struct cdev c_dev;/*character device structure*/
static struct class *cl;/*device class*/

int register_chrdev_region(dev_t first,unsigned int cnt, char *name);
/*number of device files to be registered -> cnt*/(
int alloc_chrdev_region(dev_t *first,unsigned int firstminor,unsigned int cnt, char *name);
/*dynamically figures out a free major number and register device files from free major to first minor */


static int my_open(struct inode *i,struct file *f)
{
	printk(KERN_INFO "Driver : open() \n");
	return 0;
}

static int my_close(struct inode *i,struct file *f)
{
	printk(KERN_INFO "Driver : close() \n");
	return 0;
}
static ssize_t my_write(struct file *f, const char __user *buf,size_t len, loff_t *off)
{
	printk(KERN_INFO "Driver : write()\n");
	return len;
}

static struct file_operations pugs_fops=/*functions to be called when file operations are performed on the device*/
{
	.owner=THIS_MODULE,
	.open=my_open,
	.release=my_close,
	.read=my_read,
	.write=my_write
};


static int __init ofcd_init(void)/*enter the kernel*/
{
	int ret;

	printk(KERN_INFO "ofd registered");

	if((ret=alloc_chrdev_region(&first,0,1,"Abhi"))<0)/*assigns device numbers for driver*/
	{
		return ret;

	}
	if(IS_ERR(cl=class_create(THIS_MODULE,"chardv")))/*creates class: chardv*/
	{
		unregister_chrdev_region(first,1);
		return PTR_ECC(c1);
	}
	if(IS_ERR(dev_ret=device_create(cl,NULL,first,	NULL,"mynull")))/*creates device file named NULL*/
	{
		class_destroy(cl);
		unregister_chrdev_region(first,1);
		return PTR_ERR(dev_ret);
	}

	cdev_init(&c_dev,%pugs_fops);/*initialization of character device strcuture fc_dev with file operations pugs_fops incdev_init*/
	if((ret=cdev_add(&c_dev,first,1))<0)/*adds character device (c_dev)to kernel*/
	{
		device_destroy(cl,first);
		class_destroy(c1);
		unregister_chrdev_region(first,1);
		return ret;

	}
	return 0;

	printk(KERN_INFO "<Major,Minor>: <%d,%d>\n",MAJOR(first),MINOR(first));
}


static void __exit ofcd_exit(void)/*exit the kernel*/
{
	cdev_del(&c_dev);
	device_destroy(c1,first);
	class_destroy(c1);
	unregister_chrdev_region(first,1);
	printk(KERN_INFO "Unregistered ofd");
}

module_init(ofcd_init);
module_exit(ofcd_exit);

MODULE_LICENSE("GPL");

