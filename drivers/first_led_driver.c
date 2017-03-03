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
	/*	static void on_led()
	{	
		gpio_set_value(LED_GPIO,0);
		
	} 
	*/
	
/*	static irqreturn_t SLK_irq(int irq, void *dev_id)
	{	
		gpio_set_value(LED_GPIO,1);
		mod_timer(&timer1,jiffies+HZ);
		printk(KERN_ERR"jiffies:::%ld\n",jiffies+HZ);
		return IRQ_HANDLED;		
	}
*/
	static irqreturn_t LCD_irq(int irq, void * dev_id)
		{
		printk("aaa");
		input_report_key(key_dev, KEY_VOLUMEDOWN,1);
		input_sync(key_dev);
		input_report_key(key_dev,KEY_VOLUMEDOWN,0);
		input_sync(key_dev);
		return IRQ_HANDLED;
		}
/*	static void my_timer()
	
	{
		
		timer1.function =on_led;//
		init_timer(&timer1);
		timer1.expires = jiffies+(HZ);
	}		
*/
/*static void key_gpio_init()
{
	
		err = gpio_request(EXYNOS4_GPX1(1),  "key_gpio");
		if (err)
		 {
		printk(KERN_ERR "failed to request key_gpio)\n");
		return -1;
		}
			
		gpio_direction_input(EXYNOS4_GPX1(1));		
		s3c_gpio_cfgpin(EXYNOS4_GPX1(1), S3C_GPIO_INPUT);
		s3c_gpio_setpull(EXYNOS4_GPX1(1), S3C_GPIO_PULL_UP);
				
}*/
/*static void led_gpio_init()
{

		if(gpio_request(EXYNOS4_GPK1(1), "led_gpio"))
		{
		printk(KERN_ERR "failed to request led_gpio for "
		"USI control\n");
		return err;
		}
		gpio_direction_output(EXYNOS4_GPK1(1), 0);
		s3c_gpio_cfgpin(EXYNOS4_GPK1(1), S3C_GPIO_OUTPUT);
	//	gpio_free(EXYNOS4_GPK1(1));
}

*/
/*static void lcd_pwdn_init()
{
	err = gpio_request(EXYNOS4_GPL1(0), "GPL1_0");
	if (err) {
	printk(KERN_ERR "failed to request GPL1 for "
			"lcd power control\n");
		return err;
	}
	gpio_direction_output(EXYNOS4_GPL1(0), 0);

	s3c_gpio_cfgpin(EXYNOS4_GPL1(0), S3C_GPIO_OUTPUT);

	printk("(%s, %d): LCD_PWDN ON\n", __FUNCTION__, __LINE__);
}*/

static int led_probe(struct platform_device *pdev)
{
			
	  	//	my_timer();
		//	led_gpio_init();
		//	key_gpio_init();
			key_dev = input_allocate_device();
			key_dev->name="power_key";
			set_bit(EV_KEY,key_dev->evbit);
			set_bit(KEY_VOLUMEDOWN,key_dev->keybit);
					
			input_register_device(key_dev);

			ret = request_irq(IRQ_EINT(10), LCD_irq,
			IRQ_TYPE_EDGE_FALLING /*IRQF_TRIGGER_FALLING*/, "eint10", NULL);
			if (ret < 0) 
			{
			printk("Request IRQ %d failed, %d\n", IRQ_EINT(10), ret);
			goto exit;
			}

	//		ret = request_irq(IRQ_EINT(9), LCD_irq,
	//		IRQ_TYPE_EDGE_FALLING /*IRQF_TRIGGER_FALLING*/, "eint9", NULL);
	//		if (ret < 0) 
	//		{
	//		printk("Request IRQ %d failed, %d\n", IRQ_EINT(9), ret);
	//		goto exit;
	//	}

			exit:
			return ret;
}
	
static int led_remove(struct platform_device *pdev)
{	
	
	del_timer(&timer1);
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
