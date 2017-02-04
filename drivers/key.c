#include <linux/module.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include <linux/irq.h>
#include <linux/gpio.h>

#include <mach/gpio.h>
#include <plat/gpio-cfg.h>


static int major;


static struct class *cls;
static volatile unsigned long *gpio_con;
static volatile unsigned long *gpio_dat;
static int pin;

static ssize_t key_write(struct file *file,const char __user*buf,size_t count,loff_t ppos)
{
return 0;
}

static int key_open(struct inode *inode, struct file *file)
{
	return 0;	
}

	


static struct file_operations key_fops = {
    	.open   =   key_open,     
	.write	=	key_write,	   
};

static int key_probe(struct platform_device *pdev)
{
int ret = 0;
	printk("led_key,found led\n");


	ret = gpio_request(EXYNOS4_GPX2(1), "KEY");
	if (ret)
	{
		printk(KERN_ERR "gpio request failed\n");
	}
	else
	{
		printk(KERN_ERR "gpio request success\n");
	}
	gpio_direction_input(EXYNOS4_GPX2(1));

	s3c_gpio_cfgpin(EXYNOS4_GPX2(1), S3C_GPIO_INPUT);


	return 0;
}

static int key_remove(struct platform_device *pdev)
{
	
	return 0;
}


struct platform_driver key_drv = {
	.probe		= key_probe,
	.remove		= key_remove,
	.driver		= {
		.name	= "key",
	}
};
static int __init my_key_init(void)
{
	printk("ssssssssssssssssssssss");   
	platform_driver_register(&key_drv);
	
	return 0;
}


static void __exit my_key_exit(void)
{
	platform_driver_unregister(&key_drv);
}

module_init(my_key_init);
module_exit(my_key_exit);

MODULE_LICENSE("GPL");
