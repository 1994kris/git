#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
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
static int led_probe(struct platform_device *pdev)
{
	printk(KERN_ERR "asdasdwfirst_led_probe" );
	return 0;
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

		printk(KERN_ERR "wwwwwwwwwwwwwwwwwwwwwwwwww" );
		platform_driver_register(&led_drv);
		printk(KERN_ERR "ssssssssssssssssssssssssssss" );
		return 0;
}
static void led_driver_exit(void)
{
		platform_driver_unregister(&led_drv);

}module_init(led_driver_init);
module_exit(led_driver_exit);
MODULE_LICENSE("GPL");
