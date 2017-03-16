#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/platform_device.h>

static struct i2c_client *this_client;

static int bh1750_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	printk(KERN_ERR"bh1750_probe");
	struct  bh1750_i2c_platform_data *pdata;
	int err = -EINVAL;

}
static int __devexit bh1750_remove(struct i2c_client *client) {

}


static const struct i2c_device_id bh1750_id[] = {
	{ "bh1750", 0 },
	{ }
};
static struct i2c_driver bh1750_driver = {
	.probe		= bh1750_probe,
	.remove		= __devexit_p(bh1750_remove),
	.id_table	= bh1750_id,
	.driver	= {
		.name	=" bh1750",
		.owner	= THIS_MODULE,
	},
};
static int __init bh1750_init(void)
{
	return i2c_add_driver(&bh1750_driver);
}


static void __exit bh1750_exit(void)
{
	i2c_del_driver(&bh1750_driver);

	//regulator_put(dc33v_tp);
}

MODULE_LICENSE("GPL");
module_exit(bh1750_exit);
module_init(bh1750_init);



