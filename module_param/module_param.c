#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("TOPEET");
static int module_arg1,module_arg2;
static int int_array[50];
static int int_num;
module_param(module_arg1,int,S_IRUSR);
module_param(module_arg2,int,S_IRUSR);
module_param_array(int_array,int,&int_num,S_IRUSR);
static int hello_init(void)
{
	int i;
	printk(KERN_EMERG"module_arg1 is %d\n",module_arg1);
	printk(KERN_EMERG"module_arg2 is %d\n",module_arg2);
	for(i=0;i<int_num;i++)
{
	printk(KERN_EMERG"int_array[%d] is %d!\n",i,int_array[i]);
}
	printk(KERN_EMERG"hello world enter!\n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_EMERG "HELLO WORLD exit!\n");
	
}

module_init(hello_init);
module_exit(hello_exit);
