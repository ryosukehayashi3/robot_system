//SPDX-License-Identifer: GPL-2.0
/*
 * Copyright (C) 2021 Ryosuke Hayashi. All rights reserved.
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

#define num 3

MODULE_AUTHOR("Ryuichi Ueda and Ryosuke Hayashi");
MODULE_DESCRIPTION("driver for LED and Buzzer control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;

static int list[num] = {25,26,12};

static ssize_t led_write(struct file* flip, const char*buf, size_t count, loff_t*pos)
{
	char c;
	int i,n;
	if(copy_from_user(&c,buf,sizeof(char)))
		return -EFAULT;

	if(c && c != "\n"){

	if(c == "a"){
		for(i = 0; i <= 10; i++){
			n = 1000 - 100*i + 1;
			gpio_base[7] = 1 << list[0];
			gpio_base[7] = 1 << list[2];
			msleep(10);
			gpio_base[10] = 1 << list[2];
			msleep(n);

			gpio_base[10] = 1 << list[0];
			gpio_base[7] = 1 << list[1];
			gpio_base[7] = 1 << list[2];
			msleep(10);
			gpio_base[10] = 1 << list[2];
			msleep(n);
			gpio_base[10] = 1 << list[1];

			if(n == 1){
				for(i = 0; i <= 5; i++){
					gpio_base[7] = 1 << list[0];
					gpio_base[7] = 1 << list[2];
					msleep(10);
					gpio_base[10] = 1 << list[2];
					msleep(n);

					gpio_base[10] = 1 << list[0];
					gpio_base[7] = 1 << list[1];
					gpio_base[7] = 1 << list[2];
					msleep(10);
					gpio_base[10] = 1 << list[2];
					msleep(n);
					gpio_base[10] = 1 << list[1];
				}
				break;
			}
		}
			gpio_base[7] = 1 << list[2];
			msleep(500);
			gpio_base[10] = 1 << list[2];
	}else{
		for(i = 0; i <= 2; i++){
			gpio_base[7] = 1 << list[0];
			gpio_base[7] = 1 << list[1];
			gpio_base[7] = 1 << list[2];
			msleep(100);
			gpio_base[10] = 1 << list[0];
			gpio_base[10] = 1 << list[1];
			gpio_base[10] = 1 << list[2];
			msleep(100);
		}
	}
}
	
	printk(KERN_INFO "receive: %c\n",c);
	for(i = 0; i < num; i++){
		gpio_base[10] = 1 << list[i];
	}

	return 1;

}

static ssize_t sushi_read(struct file* flip, char* buf, size_t count, loff_t*pos)
{
	int size = 0;
	char sushi[] = {0xF0,0x9F,0x8D,0xA3,0x0A};
	if(copy_to_user(buf+size,(const char *)sushi, sizeof(sushi))){
		printk( KERN_INFO "sushi : copy_to_user failed\n" );
		return -EFAULT;
	}
	size += sizeof(sushi);
	return size;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write,
	.read = sushi_read
};

static int __init init_mod(void)
{
	int retval,i;
	retval = alloc_chrdev_region(&dev, 0, 1, "myled");
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed\n");
		return retval;
	}
	printk (KERN_INFO "%s is loaded. major:%d\n",__FILE__, MAJOR(dev));

	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
		if(retval < 0){
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
		return retval;
	}

	cls = class_create(THIS_MODULE, "myled");
	if(IS_ERR(cls)){
			printk(KERN_ERR "class_create failed.");
			return PTR_ERR(cls);
			}

	device_create(cls, NULL, dev, NULL, "myled%d", MINOR(dev));

	gpio_base = ioremap_nocache(0x3f200000, 0xA0);

	for(i = 0; i < num; i++){
		const u32 led = list[i];
		const u32 index = led/10;	
		const u32 shift = (led%10)*3;
		const u32 mask = ~(0x7 << shift);
		gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);
	}

       	return 0;
}

static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is uncloaded, major:%d\n",__FILE__, MAJOR(dev));
}

module_init(init_mod);
module_exit(cleanup_mod);

