#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/unistd.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/timer.h>
#include <linux/serial_core.h>
#include <linux/platform_device.h>  
#include <plat/gpio-cfg.h>
#include <mach/gpio-exynos4.h>
#include <linux/errno.h>
extern int gpio_direction_input(unsigned gpio);
extern int gpio_direction_output(unsigned gpio,int value);
extern int gpio_request(unsigned gpio,const char *label);
extern void gpio_set_value(unsigned gpio,int value);
extern int gpio_get_value(unsigned gpio);
int err;
int ret;
#define KEY_GPIO  EXYNOS4_GPX1(1)
#define LED_GPIO  EXYNOS4_GPK1(1)

static struct workqueue_struct *mywq;
struct work_struct my_work;
static struct input_dev *key_dev;
static struct proc_dir_entry *pt_root;
void work_func(struct work_struct *work);
void work_func(struct work_struct *work)
{
		printk(KERN_ERR"jiadayin");
		input_report_key(key_dev, KEY_POWER,1);
		input_sync(key_dev);
		msleep(2000);
		input_report_key(key_dev, KEY_POWER,0);
		input_sync(key_dev);
}
static struct proc_dir_entry *tp_root;  
static struct proc_dir_entry *debug_entry;  
static struct proc_dir_entry *pt_entry1;
#define USER_ROOT_DIR "tp_debug"  
#define USER_ENTRY1   "debug_switch"

static int my_switch_writeproc(struct file *file,const char *buffer,unsigned long count,void *data)
{	
/*	int tp_dbg;
	sscanf(buffer,"%d",&tp_dbg);
	printk("tpd:proc-->tp_dbg=%d\n",tp_dbg);
*/	return count;
}
static int my_switch_readproc(char *page,char **start,off_t off,int count,int *eof,void *data)
{
/*
int len;
int tp_dbg;
unsigned char tmp = tp_dbg&0x0F;
len = sprintf(page,"%c\n",tmp);
*/
return 2;
}
/*static void remove_debug_port(void)
{
	remove_proc_entry(USER_ENTRY1,pt_root);
	remove_proc_entry(USER_ROOT_DIR,NULL);
}
*/
static int init_debug_port(void)
{
	
/*	pt_root = proc_mkdir(USER_ROOT_DIR,NULL);
	if(NULL==pt_root);
		{
     printk(KERN_ALERT"Create dir /proc/%s error!\n", USER_ROOT_DIR); 
            return -1; 
		}
	printk(KERN_INFO"Create dir /proc/%s\n", USER_ROOT_DIR); */
	pt_entry1 =create_proc_entry(USER_ENTRY1, 0666, NULL); 
        if (NULL ==pt_entry1) 
        { 
                printk(KERN_ALERT"MY Create entry %s under /proc/%s error!\n", 
                                            USER_ENTRY1,USER_ROOT_DIR); 
                goto err_out; 
         }
	pt_entry1->write_proc=my_switch_writeproc;
	pt_entry1->read_proc=my_switch_readproc;
	printk(KERN_INFO"MY1 Create /proc/%s/%s/%s\n",USER_ROOT_DIR,USER_ENTRY1);
	return 0;
	err_out: 
         pt_entry1->read_proc =NULL; 
         pt_entry1->write_proc= NULL;
         remove_proc_entry(USER_ROOT_DIR,pt_root); 
         return -1;
}
	static irqreturn_t power_irq(int irq, void * dev_id)
		{
		printk(KERN_ERR"power");
		queue_work(mywq,&my_work);
		return IRQ_HANDLED;
		}
	static void gpiokey()
	{	
		if(gpio_request(EXYNOS4_GPX1(1),"key1"))
		{
			printk(KERN_ERR"fail");
			return -1;
		}
		s3c_gpio_cfgpin(KEY_GPIO,S3C_GPIO_SFN(0xf));
		s3c_gpio_setpull(KEY_GPIO,S3C_GPIO_OUTPUT);
	}
	static void input_dev_init()
	{
		
			key_dev = input_allocate_device();
			key_dev->name="power_key";
			set_bit(EV_KEY,key_dev->evbit);
			set_bit(KEY_POWER,key_dev->keybit);
			input_register_device(key_dev);
	}
static int debug_probe(struct platform_device *pdev)
{
			init_debug_port();

		
			mywq= create_workqueue("mywq");
			INIT_WORK(&my_work,work_func);
			gpiokey();
			input_dev_init();
			ret = request_irq(gpio_to_irq(KEY_GPIO), power_irq,
			IRQ_TYPE_EDGE_FALLING /*IRQF_TRIGGER_FALLING*/, "eint17", NULL);
			if (ret < 0) 
			{
			printk("Request IRQ %d failed, %d\n", IRQ_EINT(17), ret);
			goto exit;
			}

		

			exit:
			return ret;
}
	
static int debug_remove(struct platform_device *pdev)
{	
	return 0;
}


struct platform_driver led_drv= 
{
	.driver = {
	.name = "qwe",
},
	.probe = debug_probe,
	.remove = debug_remove,
};
static int led_driver_init(void)
{
		

		platform_driver_register(&led_drv);
		return 0;
}
static void led_driver_exit(void)
{		
		platform_driver_unregister(&led_drv);
}
EXPORT_SYMBOL_GPL(gpio_direction_input);
//module_init(led_driver_init);
late_initcall(led_driver_init);
module_exit(led_driver_exit);
MODULE_LICENSE("GPL");
