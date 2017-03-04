#include <linux/module.h>
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
extern int gpio_get_value(int value);
int err;
int ret;
struct timer_list timer1;
#define KEY_GPIO  EXYNOS4_GPX1(1)
#define LED_GPIO  EXYNOS4_GPK1(1)
#define LCD_GPIO  EXYNOS4_GPL1(0)
static struct input_dev *key_dev;

	static irqreturn_t voldown_irq(int irq, void * dev_id)
		{
		printk(KERN_ERR"vol-");
		input_report_key(key_dev, KEY_VOLUMEDOWN,1);
		input_sync(key_dev);
		input_report_key(key_dev,KEY_VOLUMEDOWN,0);
		input_sync(key_dev);
		return IRQ_HANDLED;
		}
	static irqreturn_t volup_irq(int irq, void * dev_id)
		{
		printk(KERN_ERR"vol+");
		input_report_key(key_dev, KEY_VOLUMEUP,1);
		input_sync(key_dev);
		input_report_key(key_dev, KEY_VOLUMEUP,0);
		input_sync(key_dev);
		return IRQ_HANDLED;
		}
	static irqreturn_t back_irq(int irq, void * dev_id)
		{
		printk(KERN_ERR"back");
		input_report_key(key_dev, KEY_BACK,1);
		input_sync(key_dev);
		input_report_key(key_dev, KEY_BACK,0);
		input_sync(key_dev);
		return IRQ_HANDLED;
		}
	static irqreturn_t power_irq(int irq, void * dev_id)
		{
		printk(KERN_ERR"power");
		input_report_key(key_dev, KEY_POWER,1);
		input_sync(key_dev);
		input_report_key(key_dev, KEY_POWER,0);
		input_sync(key_dev);
		return IRQ_HANDLED;
		}
	static irqreturn_t menu_irq(int irq, void * dev_id)
		{
		printk(KERN_ERR"menu");
		input_report_key(key_dev, KEY_MENU,1);
		input_sync(key_dev);
		input_report_key(key_dev, KEY_MENU,0);
		input_sync(key_dev);
		return IRQ_HANDLED;
		}
static int led_probe(struct platform_device *pdev)
{
			

			key_dev = input_allocate_device();
			key_dev->name="power_key";
			set_bit(EV_KEY,key_dev->evbit);
			set_bit(KEY_VOLUMEDOWN,key_dev->keybit);
					
			set_bit(KEY_VOLUMEUP,key_dev->keybit);
			set_bit(KEY_MENU,key_dev->keybit);
			set_bit(KEY_POWER,key_dev->keybit);
			
			set_bit(KEY_BACK,key_dev->keybit);
			input_register_device(key_dev);

			ret = request_irq(IRQ_EINT(10), voldown_irq,
			IRQ_TYPE_EDGE_FALLING /*IRQF_TRIGGER_FALLING*/, "eint10", NULL);
			if (ret < 0) 
			{
			printk("Request IRQ %d failed, %d\n", IRQ_EINT(10), ret);
			goto exit;
			}

					
			ret = request_irq(IRQ_EINT(27), volup_irq,
			IRQ_TYPE_EDGE_FALLING /*IRQF_TRIGGER_FALLING*/, "eint27", NULL);
			if (ret < 0) 
			{
			printk("Request IRQ %d failed, %d\n", IRQ_EINT(27), ret);
			goto exit;
			}
			
			ret = request_irq(IRQ_EINT(9), back_irq,
			IRQ_TYPE_EDGE_FALLING /*IRQF_TRIGGER_FALLING*/, "eint9", NULL);
			if (ret < 0) 
			{
			printk("Request IRQ %d failed, %d\n", IRQ_EINT(9), ret);
			goto exit;
			}

			ret = request_irq(IRQ_EINT(17), power_irq,
			IRQ_TYPE_EDGE_FALLING /*IRQF_TRIGGER_FALLING*/, "eint17", NULL);
			if (ret < 0) 
			{
			printk("Request IRQ %d failed, %d\n", IRQ_EINT(17), ret);
			goto exit;
			}

			ret = request_irq(IRQ_EINT(16), menu_irq,
			IRQ_TYPE_EDGE_FALLING /*IRQF_TRIGGER_FALLING*/, "eint16", NULL);
			if (ret < 0) 
			{
			printk("Request IRQ %d failed, %d\n", IRQ_EINT(16), ret);
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
