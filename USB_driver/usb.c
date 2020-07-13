#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/usb.h>

//probe function
//called on device insertion 

static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	printk(KERN_INFO"[*]: pendrive (%04X : %04X) plugged \n", id->idVendor, id->idProduct);
	return 0; //returning 0 indicates that the device is managed by this driver
}

//disconnect function

static void pen_disconnect(struct usb_interface *interface){
	printk(KERN_INFO"[*] pendrive has been removed");
}


//usb_device_id
static struct usb_device_id pen_table[]={
//0781:5406
{USB_DEVICE(0X090c, 0X1000)},//vendorid, productid
{}// terminating entry
};
MODULE_DEVICE_TABLE(usb, pen_table);



//usb driver
static struct usb_driver pen_driver =
{

	.name="MY USB",
	.id_table=pen_table, //used to match this driver with any device which is attached to usb bus
	.probe=pen_probe, //probe function
	.disconnect=pen_disconnect, // clean up memory
};


//initializing pendrive to usb core

static int __init pen_init(void){
	int ret=-1;
	printk(KERN_INFO "[*] pendrive constructor of driver");
	printk(KERN_INFO "\t Register Driver with kernel");
	ret = usb_register(&pen_driver);
	printk(KERN_INFO "\t registeration is complete");
	return ret;
}



static void __exit pen_exit(void){
	printk(KERN_INFO "[*] pendrive destructor of driver");
	usb_deregister(&pen_driver);
	printk(KERN_INFO "\t unregister complete");
}


module_init(pen_init);
module_exit(pen_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SWAROOP");
MODULE_DESCRIPTION("USB pen registration driver");

