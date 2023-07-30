#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/types.h>

#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<asm/io.h>

#define VRAM_BASE 0x000A0000/*random as I couldnt find the vram storage space in my computer*/
#define VRAM_SIZE 0x00020000

static void __iomem *vram;
static dev_t first;
static struct cdev c_dev;
static struct class *cl;

static int my_open(struct inode *i,struct file *f)
{
	return 0;
}

static int my_close(struct inode *i,struct file *f)
{
	return 0;
}

static ssize_t my_read(struct file *f,char __user *buf,size_t len, loff_t *off)
{
	int i;
	u8 byte;

	if(*off>=VRAM_SIZE)/*check if offset exceeds videoram size*/
	{
		return 0;
	}
	if(*off+len>VRAM_SIZE)/*check if videoram size left = size of given file*/
	{
		len=VRAM_SIZE-*off;
	}
	for(i=0;i<len;i++)
	{
		byte=ioread8((u8*)vram+ *off+i);/*read*/
		if(copy_to_user(buf+i,&byte,1))
		{
			return -EFAULT;/*EFAULT is error given if wrong pointer is passed*/
		}
	}
	*off+=len;/*offset set to new value after data addition detected*/
	return len;

}
static ssize_t my_write(struct file *f,const char __user *buf,size_t len,loff_t *off)
{
	int i;
	u8 byte;

	if(*off>=VRAM_SIZE)/*check if offset exceeds videoram size*/
	{
		return 0;
	}
	if(*off+len>VRAM_SIZE)/*check if videoram size left= size of input*/
	{
		len=VRAM_SIZE-*off;
	}
	for(i=0;i<len;i++)
	{
		if(copy_from_user(&byte,buf+i,1))/*input taken*/
		{
			return -EFAULT;/*EFAULT is error given if wrong pointer is passed*/
		}
		iowrite8(byte,(u8*)vram+*off+i);/*write into the ram*/
	}
	*off+=len;/*offset set to new value after data addition*/
	return len;
}

static struct file_operations vram_fops=
{
	.owner=THIS_MODULE,
	.open=my_open,
	.release=my_close,
	.read=my_read,
	.write=my_write,
}
;

static int __init vram_init(void)
{
	int ret;
	struct device *dev_ret;

	if((vram=ioremap(VRAM_BASE,VRAM_SIZE))==NULL)/*mapping of vidram to kernel virtual address is represented by vram pointer-null indicates failure*/
	{/*ioremap creates virtual kernel address for physical addresses*/
		printk(KERN_ERR "Mapping video ram failed\n");
		return -ENOMEM;
	}
	if((ret=alloc_chrdev_region(&first,0,1,"vram"))<0)/*apoints character device number to vram*/
	{
		return ret;
	}
	if(IS_ERR(cl=class_create(THIS_MODULE,"chardv")))/*class creation*//*if block of statements undergo if error detected thus unregistering the deive number*/
	{
		unregister_chrdev_region(first,1);	
		return PTR_ERR(cl);
	}
	if(IS_ERR(dev_ret=device_create(cl,NULL,first,NULL,"vram")))/*device creation; if failed then class is destroyed and device number is unregistere*/
	{
		class_destroy(cl);
		unregister_chrdev_region(first,1);
		return PTR_ERR(dev_ret);
	}

	cdev_init(&c_dev,&vram_fops);/*character device strucutre initialised*/

	if((ret=cdev_add(&c_dev,first,1))<0)/*adds c_dev to kernel*/
	{
		device_destroy(cl,first);
		class_destroy(cl);
		unregister_chrdev_region(first,1);
		return ret;
	}
	return 0;
}

static void __exit vram_exit(void)
{
	cdev_del(&c_dev);
	device_destroy(cl,first);
	class_destroy(cl);
	unregister_chrdev_region(first,1);
	iounmap(vram);
}


module_init(vram_init);
module_exit(vram_exit);

MODULE_LICENSE("GPL");