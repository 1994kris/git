#include <linux/module.h>
#include <linux/version.h>

#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/serial_core.h>
#include <linux/platform_device.h>
static struct resource dev_irq_gpio_resource[] =
{
/*	[0]={
	.start = IRQ_EINT(9),
	.end   = IRQ_EINT(9),
	.flags  = IORESOURCE_IRQ,
	},
*/	[0]={
	.start  = EXYNOS4_GPX1(1),
	.end   =  EXYNOS4_GPX1(1),
	.flags = IORESOURCE_IO,
	},
	[2]={
	.start  = EXYNOS4_GPL2(0),
	.end    = EXYNOS4_GPL2(0),
	.flags  = IORESOURCE_IO,
	},
	[1]={
	.start  = EXYNOS4_GPK1(1),
	.end    = EXYNOS4_GPK1(1),
	.flags  = IORESOURCE_IO,
	}
};
static void dev_irq_release(struct device * dev)
{
	printk(" -----");
}

static struct platform_device led_dev= 
{
	.name = "qwe",
	.id	 =66,
	.resource = dev_irq_gpio_resource,
	.num_resources  = ARRAY_SIZE(dev_irq_gpio_resource),
	.dev =	{
			.release= dev_irq_release,
			},
};
static int led_dev_init(void)
{
printk(KERN_ERR"qwertyuiopasdfghjklzxcvbnm");
platform_device_register(&led_dev);
	return 0;
}
static void led_dev_exit(void)
{
platform_device_unregister(&led_dev);

}

module_init(led_dev_init);
module_exit(led_dev_exit);
MODULE_LICENSE("GPL");
