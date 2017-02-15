#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>
#include <mach/gpio-exynos4.h>
#define DRIVER_NAME "hello_ctl"
#define DEVICE_NAME "hello_gpio"


static int led_gpios[]={
EXYNOS4_GPL2(0),EXYNOS4_GPK1(1),
EXYNOS4_GPD0(0),
EXYNOS4_GPX1(0),EXYNOS4_GPX1(3),EXYNOS4_GPX1(5),EXYNOS4_GPX1(6),
EXYNOS4_GPX3(0),EXYNOS4_GPX2(6),EXYNOS4_GPX2(7),EXYNOS4_GPX3(5),

};
#define LED_NUM    ARRAY_SIZE(led_gpios)

static long hello_ioctl(struct file *files,unsigned int cmd,unsigned long arg)
{
printk("cmd is %d,arg is %d\n",cmd,arg);
switch(cmd)
{
case 0 :
case 1 :
	if(arg > LED_NUM)
{
return -EINVAL;
}
gpio_set_value(led_gpios[arg],cmd);
break;
default:
return -EINVAL;
}
gpio_set_value(led_gpios[2],0);
return 0;
}
static int hello_release(struct inode *inode,struct file *file)
{
printk(KERN_EMERG"hello release\n");
return 0;
}
static int hello_open(struct inode *inode,struct file *file){
printk(KERN_EMERG"hello open\n");
return 0;
}
static struct file_operations hello_ops = {
.owner = THIS_MODULE,
.open = hello_open,
.release = hello_release,
.unlocked_ioctl = hello_ioctl,
};
static struct miscdevice hello_dev = {
.minor = MISC_DYNAMIC_MINOR,
.name = DEVICE_NAME,
.fops = &hello_ops,
};
static int hello_probe(struct platform_device *pdv)
{
int ret,i;
printk(KERN_EMERG "\tinitialized\n");
for(i=0;i<LED_NUM;i++)
{
ret = gpio_request(led_gpios[i],"LED");
if(ret)
{
printk("%s:request GPIO %d for LED fialed,ret = %d\n",DRIVER_NAME,i,ret);}
else{
s3c_gpio_cfgpin(led_gpios[i],S3C_GPIO_OUTPUT);
gpio_set_value(led_gpios[i],1);
}
}
gpio_set_value(led_gpios[2],0);
misc_register(&hello_dev);
if(ret<0)
{
printk("leds:register device failed\n");
goto exit;
}
return 0;

exit:
misc_register(&hello_dev);
return ret;
return 0;
}
static int hello_remove(struct platform_device *pdv)
{
int i;
printk(KERN_EMERG"\tremove\n");
for(i=0;i<LED_NUM;i++)
{
gpio_free(led_gpios[i]);
}
misc_deregister(&hello_dev);
return 0;
}


static void hello_shutdown(struct platform_device *pdv)
{
;
}
static int hello_suspend(struct platform_device *pdv)
{
return 0;
}

static int hello_resume(struct platform_device *pdv)
{
return 0;
}

struct platform_driver hello_driver = {
.probe = hello_probe,
.remove = hello_remove,
.shutdown = hello_shutdown,
.suspend = hello_suspend,
.resume = hello_resume,
.driver = {
.name = DRIVER_NAME,
.owner = THIS_MODULE,
}
};
static int my_hello_init(void)
{
int Driverstate;
printk(KERN_EMERG" hello init");
Driverstate = platform_driver_register(&hello_driver);
printk(KERN_EMERG "\tDriverState is %d\n",Driverstate);
return 0;
}
static void my_hello_exit(void)
{
printk(KERN_EMERG" hello exit");
void free_irq(unsigned int irq,void *dev_id);
platform_driver_unregister(&hello_driver);
}
module_init(my_hello_init);
module_exit(my_hello_exit);
MODULE_LICENSE("GPL");
