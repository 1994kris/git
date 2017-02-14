#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#define DRIVER_NAME "hello_ctl"
#define DEVICE_NAME "hello_ctl123"
static long hello_ioctl(struct file *files,unsigned int cmd,unsigned long arg)
{
printk("cmd is %d,arg is %d\n",cmd,arg);
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
printk(KERN_EMERG "\tinitialized\n");
misc_register(&hello_dev);
return 0;
}
static int hello_remove(struct platform_device *pdv)
{
printk(KERN_EMERG"\tremove\n");
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

platform_driver_unregister(&hello_driver);
}






module(my_hello_init);
module(my_hello_exit);
MODULE_LICENSE("GPL");
