#include <linux/module.h>
#include <linux/version.h>

#include <linux/init.h>

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/serial_core.h>
#include <linux/platform_device.h>


static struct platform_device led_dev= 
{
	.name = "qwe",
	.id	 =66,
};
static int led_dev_init(void)
{
printk(KERN_ERR"qsddddddddddddddddaaaaaaaaaaaaasdasdasasdsssssssssssssssssssssssssssssssdaqqqqqqqq");
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
