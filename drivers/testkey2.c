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

static unsigned long key1_gpio;
static unsigned long led1_gpio;
static unsigned long led2_gpio;


static struct workqueue_struct *mywq;
struct work_struct my_work;
static struct input_dev *key_dev;
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
	static irqreturn_t power_irq(int irq, void * dev_id)
		{
	printk(KERN_ERR"power");
	queue_work(mywq,&my_work);
		return IRQ_HANDLED;
		}
	static void gpiokey()
	{	
		if(gpio_request(key1_gpio,"key_gpio"))
		{
			printk(KERN_ERR"fail");
			return -1;
		}
		s3c_gpio_cfgpin(key1_gpio,S3C_GPIO_SFN(0xf));
		s3c_gpio_setpull(key1_gpio,S3C_GPIO_OUTPUT);
	}
	static void led_gpio_init()
	{
		int err;
		if(gpio_request(led1_gpio,"led_gpio"))
		{
		printk(KERN_ERR"failed to request led_gpio for");
		return err;
		}
		printk(KERN_ERR"led1jiadayin");
		gpio_direction_output(led1_gpio,0);
		s3c_gpio_cfgpin(led1_gpio,S3C_GPIO_OUTPUT);
	}
	static void led2_gpio_init()
	{
		int err;
		if(gpio_request(led2_gpio,"led2_gpio"))
		{
		printk(KERN_ERR"failed to request led2_gpio for");
		return err;
		}
		printk(KERN_ERR"led2jiadayin");
		gpio_direction_output(led2_gpio,0);
		s3c_gpio_cfgpin(led2_gpio,S3C_GPIO_OUTPUT);
	}
	static void input_dev_init()
	{
		
			key_dev = input_allocate_device();
			key_dev->name="power_key";
			set_bit(EV_KEY,key_dev->evbit);
			set_bit(KEY_POWER,key_dev->keybit);
			input_register_device(key_dev);
	}
	static struct proc_dir_entry *tp_root;  
	static struct proc_dir_entry *debug_entry;  
	static struct proc_dir_entry *pt_entry1;
	static struct proc_dir_entry *pt_root;
	#define USER_ROOT_DIR "tp_debug"  
	#define USER_ENTRY1   "debug_switch"
	static int my_switch_writeproc(struct file *file,const char *buffer,unsigned long count,void *data)
{
	printk(KERN_ERR"led=%d\n",led1_gpio);
	int tp_dbg;
	sscanf(buffer,"%d",&tp_dbg);
	printk("tpd:proc-->tp_dbg=%d\n",tp_dbg);
	if(tp_dbg==1)
	{
		
		gpio_direction_output(led1_gpio,0);
	printk(KERN_ERR"led1_gpio=%d\n",led1_gpio);	
		gpio_direction_output(led2_gpio,0);
	printk(KERN_ERR"led2_gpio=%d\n",led2_gpio);
	}
	if(tp_dbg==2)
	{
		
		gpio_direction_output(led1_gpio,1);
	printk(KERN_ERR"led1_gpi1o=%d\n",led1_gpio);
		gpio_direction_output(led2_gpio,1);
	printk(KERN_ERR"led2_gpi2o=%d\n",led2_gpio);
	}	
return count;
}
	static int my_switch_readproc(char *page,char **start,off_t off,int count,int *eof,void *data)
{

int len;
int tp_dbg;
unsigned char tmp = tp_dbg&0x0F;
len = sprintf(page,"%c\n",tmp);

return 2;
}
	static int init_debug_port(void)
{
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
static int led_probe(struct platform_device *pdev)
{			
			init_debug_port();
			
			mywq= create_workqueue("mywq");
			struct resource *res;
			INIT_WORK(&my_work,work_func);
			gpiokey();
			input_dev_init();
			res=platform_get_resource(pdev,IORESOURCE_IO,1);
			led1_gpio=res->start;
			led_gpio_init();
			res=platform_get_resource(pdev,IORESOURCE_IO,2);
			led2_gpio=res->start;
			led2_gpio_init();
			res=platform_get_resource(pdev,IORESOURCE_IO,0);
			key1_gpio=res->start;
printk(KERN_ERR"key1_gpio%d\n",key1_gpio);
printk(KERN_ERR"GPX1(1)%d\n",EXYNOS4_GPX1(1));
printk(KERN_ERR"led1_gpio%d\n",led1_gpio);
printk(KERN_ERR"EXYNOSGPX1(0)=%d\n",EXYNOS4_GPX1(0));
printk(KERN_ERR"led2_gpio=%d\n",led2_gpio);
printk(KERN_ERR"EXYNOSGPK1(1) %d\n",EXYNOS4_GPK1(1));




			ret = request_irq(gpio_to_irq(key1_gpio), power_irq,
			IRQ_TYPE_EDGE_FALLING /*IRQF_TRIGGER_FALLING*/, "key_gpio", NULL);
			if (ret < 0) 
			{
			printk("Request IRQ %d failed, %d\n", key1_gpio, ret);
			goto exit;
			}

		

			exit:
			return ret;
}
	
static int led_remove(struct platform_device *pdev)
{	
	printk(KERN_ERR"first_led_remove");
	return 0;
}


struct platform_driver led_drv= 
{
	.driver = {
	.name = "qwe",
},
	.probe = led_probe,
	.remove = led_remove,
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
module_init(led_driver_init);
module_exit(led_driver_exit);
MODULE_LICENSE("GPL");
