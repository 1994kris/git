#include <linux/module.h>
#include <linux/init.h>
#include <linux/module.h>
  static int __init key_init(void)
  {
          printk(KERN_ALERT"key...........adsdsssdasdsaddaadadadadassdasdassssssssssssssddddddddsadsass...............pppppppppppppp......");
 	 return 0; 
  }
  
  
  static void __exit key_exit(void)
  {
          printk(KERN_ALERT"key2.............d123123122222111232333111232332223....");
  }
  module_init(key_init);
  module_exit(key_exit);
                               
