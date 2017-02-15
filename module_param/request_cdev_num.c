#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#define DEVICE_NAME "sscdev"
#define DEVICE_MINOR_NUM 2
#define DEV_MAJOR 0
#define DEV_MINOR 0
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("TOPEET");
int numdev_major = DEV_MAJOR;
int numdev_minor = DEV_MINOR;
static int module_arg1,module_arg2;
static int int_array[50];
static int int_num;
module_param(numdev_major,int,S_IRUSR);
module_param(numdev_minor,int,S_IRUSR);
module_param_array(int_array,int,&int_num,S_IRUSR);
static int scdev_init(void)
{
	int i;
	int ret = 0;
	dev_t num_dev;
	printk(KERN_EMERG"module_arg1 is %d\n",module_arg1);
	printk(KERN_EMERG"module_arg2 is %d\n",module_arg2);
	if(numdev_major)
{
num_dev = MKDEV(numdev_major,numdev_minor);
ret = register_chrdev_region(num_dev,DEVICE_MINOR_NUM,DEVICE_NAME);
}
else{
printk(KERN_EMERG"numdev_major %d is failed!\n",numdev_major);
}
if(ret<0)
{
printk(KERN_EMERG"register_chrdev_region req %d is failed!\n",numdev_major);
}
	printk(KERN_EMERG"scdev_init!\n");
	return 0;
}

static void scdev_exit(void)
{
	printk(KERN_EMERG "HELLO WORLD exit!\n");
	unregister_chrdev_region(MKDEV(numdev_major,numdev_minor),DEVICE_MINOR_NUM);
}

module_init(scdev_init);
module_exit(scdev_exit);
