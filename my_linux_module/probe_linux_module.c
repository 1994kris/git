#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#define DRIVER_NAME "hello_ctl"
static int my_hello_init(void)
{
printk(KERN_EMERG" hello init");
DriverState = platform_driver_register(&hello_driver);
printk(KERN_EMERG "\tDriverState is %d\n",DriverState);
return 0;
}
static void my_hello_exit(void)
{
printk(KERN_EMERG" hello exit");
platform driver unregister(&hello_driver);
}

struct platform_driver_hello_driver = {
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
static int hello_probe(struct platform_device *pdv)
{
printk(KERN_EMERG "\tinitialized\n");
return 0;
}
static int hello_remove(struct platform_device *pdv)
{
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
module(my_hello_init);
module(my_hello_exit);
MODULE_LICENSE("GPL");
