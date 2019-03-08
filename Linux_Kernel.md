[Goback to Readme](./readme.md)

## Linux


### Booting


### Kernel
Kernel can be regarded as a program to manage the hardware resources, like CPU and peripheral devices. The user application can interact with hardware through the kernel.
- case1: It has to make sure that there is enough memory available for an application to run, as well as to place an application in the right location in memory.
- case2: It tries to optimize the usage of the processor so that it can complete tasks as quickly as possible. It also aims to avoid deadlocks, which are problems that completely halt the system when one application needs a resource that another application is using.
- case3: It’s a fairly complicated circus act to coordinate all of those things, but it needs to be done and that’s what the kernel is for.


#### Loadable kernel module

Loadable module is a object file to extend the kernel. You can easily add files to control hardware, and don't need to recompile the kernel. 

### Linux Device Driver
A device driver is a computer program allowing higher-level computer programs to interact with a hardware device.

The device driver actaully provide a standard interface to devices. In Linux the interface is a file. It can be opened, read, write or close. So when we manipulate the devices through manipulating files.
- major number: to distinguish different kinds of driver
- minor number: to distinguish differenct individual physical devices with the same drier

Different Types:
- Character Device File
- Block Device File
- Pseudo Device File

```bash
mknod /dev/memory c 60 0 # using the make node to create a new device driver
sudo insmod nothing.ko #inser the kernel object file
lsmod # list all the module 

```

The ioctl() system call manipulates the underlying device parameters of special files. Here is how to define how the device driver will response to the ioctl operation
```c++
// This file contains snippets of code that can be added to partC.c //

long memory_ioctl (struct file *filp, unsigned int cmd, \
		  unsigned long arg);

struct file_operations memory_fops = 
{
  .read = memory_read,
  .write = memory_write,
  .open = memory_open,
  .release = memory_release,
  .unlocked_ioctl = memory_ioctl
};

long 
memory_ioctl (struct file *filp, unsigned int cmd,
 	      unsigned long arg)
{
  printk("<1>in ioctl\n");
  if(cmd==0) 
	*memory_buffer^=0x20;	
  else
        *memory_buffer|=0x20;
  return(0); // success!
}
```

A typical kernel module file
```c++
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
MODULE_LICENSE("Dual BSD/GPL");
static int hello_init(void) {
    printk("<1> Pork chop sandwiches!\n");
    return 0;
}
static void hello_exit(void) {
    printk("<1> What are you doing? Get out of here!\n");
}
module_init(hello_init);
module_exit(hello_exit);
```

The device driver for the h-bridge. We must define the init entry, exit entry, and file operations. So, in the module init function, we need to register the device file with the major number and defined file operations. 
```c++
/**
 * @file    h-bridge device driver
 * @author  Kevin Yang
 * @date    3/20/2017
 * @brief   Solution code for a kernel module that controls a h-bridge. 
 *          Pin mounts and commands are defined below.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/* printk() */
#include <linux/gpio.h>

#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/types.h>	/* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h>	/* O_ACCMODE */
#include <linux/ioport.h>
//#include <asm/system.h>		/* cli(), *_flags */
#include <asm/uaccess.h>	/* copy_from/to_user */
#include <asm/io.h>

MODULE_LICENSE ("Dual BSD/GPL");


/*
 * Input commands and pin mounts
 */

#define FORWARD 'F'
#define LEFT    'L'
#define BACK    'B'
#define RIGHT   'R'
#define STOP    'S'

//Adjust to add intermediate speeds
#define IDLE    0
#define SPEED   1

//Adjust to reverse motor polarity
int LEFT_MOTOR  = true;
int RIGHT_MOTOR = false;

//These pins are for the RPI3 B, adjust if using a different board
#define EN1 20  //pwm pin, left motor
#define EN2 21  //pwm pin, right motor
#define A_1 6   //Y1, left motor positive
#define A_2 13  //Y2, left motor negative
#define A_3 19  //Y3, right motor positive
#define A_4 26  //Y4, right motor negative


int memory_open (struct inode *inode, struct file *filp);
int memory_release (struct inode *inode, struct file *filp);
ssize_t memory_read (struct file *filp, char *buf, size_t count,
		     loff_t * f_pos);
ssize_t memory_write (struct file *filp, const char *buf, size_t count,
		      loff_t * f_pos);
void memory_exit (void);
int memory_init (void);
//int memory_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);

void setPin(int PIN);
void removePin(int PIN);
void moveRobot(char command);
void motorControl(bool ifLeftMotor, char command);


struct file_operations memory_fops = 
{
  .read = memory_read,
  .write = memory_write,
  .open = memory_open,
  .release = memory_release,
//  .unlocked_ioctl = memory_ioctl
};

module_init (memory_init);
module_exit (memory_exit);

int memory_major = 60;
char *memory_buffer;

int memory_init (void) {
	int result;
	result = register_chrdev (memory_major, "memory", &memory_fops);
	if (result < 0) {
		printk ("Memory: cannot obtain major number %d\n", memory_major);
		return result;
	}

	/* Allocating memory for the buffer */
	memory_buffer = kmalloc (1, GFP_KERNEL);
	if (!memory_buffer) {
		result = -ENOMEM;
		goto fail;
	}

	memset (memory_buffer, 0, 1);
	printk ("Inserting memory module\n");
   
    setPin(EN1);
    setPin(EN2);
    setPin(A_1);
    setPin(A_2);
    setPin(A_3);
    setPin(A_4); 
    
    return 0;

fail:
	memory_exit ();
	return result;
}

void memory_exit (void) {
    unregister_chrdev (memory_major, "memory");
	if (memory_buffer)	{
	    kfree (memory_buffer);
	}
	printk ("Removing memory module\n");
     
    removePin(EN1);
    removePin(EN2);
    removePin(A_1);
    removePin(A_2);
    removePin(A_3);
    removePin(A_4);
    
    printk("GPIO freed, goodbye\n");
}

int memory_open (struct inode *inode, struct file *filp) {
 	return 0;
}

int memory_release (struct inode *inode, struct file *filp) {
 	return 0;
}

ssize_t memory_read (struct file * filp, char *buf, size_t count, loff_t * f_pos) {
  /* Transfering data to user space */
  /* Changing reading position as best suits */
	if (*f_pos == 0) {
		if(copy_to_user (buf, memory_buffer, 1)) return count; //error
		*f_pos += 1;
		return 1;
	} else {
		return 0;
	}
}

ssize_t memory_write (struct file * filp, const char *buf, size_t count, loff_t * f_pos) { 
	int tmp=copy_from_user(memory_buffer, buf, 1);
	if(tmp!=0)
	{
		printk("mem_write error");
		return(count);//just do nothing but say you did all the chars
	}
	f_pos += 1;	

	if (memory_buffer[0] == 'F') {
	    moveRobot(FORWARD);
    }
	if (memory_buffer[0] == 'L') {
	    moveRobot(LEFT);
    }
	if (memory_buffer[0] == 'B') {
	    moveRobot(BACK);
    }
	if (memory_buffer[0] == 'R') {
	    moveRobot(RIGHT);
    }    
	if (memory_buffer[0] == 'S') {
	    moveRobot(STOP);
    }

	return 1;
}

void setPin(int PIN) {
    
    if (!gpio_is_valid(PIN)) {
        printk("Invalid GPIO pin\n");
        return;
    }
    // Your stuff here.
    
    printk("GPIO pin %d exported... Pin state is currently: %d\n", PIN, gpio_get_value(PIN));

}

void removePin(int PIN) {     
	// Your stuff here.
}

 
void moveRobot(char command) {
    switch(command) {
        case FORWARD:
            motorControl(LEFT_MOTOR, FORWARD);
            motorControl(RIGHT_MOTOR, FORWARD);
            break;
        case LEFT:
            motorControl(LEFT_MOTOR, STOP);
            motorControl(RIGHT_MOTOR, FORWARD);
            break; 
        case BACK:
            motorControl(LEFT_MOTOR, BACK);
            motorControl(RIGHT_MOTOR, BACK);
            break; 
        case RIGHT:
            motorControl(LEFT_MOTOR, FORWARD);
            motorControl(RIGHT_MOTOR, STOP);
            break;
        case STOP:
            motorControl(LEFT_MOTOR, STOP);
            motorControl(RIGHT_MOTOR, STOP);
            break;
        default:
            printk("Illegal command input\n");
            break;
    }   
}

void motorControl(bool ifLeftMotor, char command) {
    int enable      = ifLeftMotor ? EN1 : EN2;
    int motorPos    = ifLeftMotor ? A_1 : A_3;
    int motorNeg    = ifLeftMotor ? A_2 : A_4;

    switch (command) {
        case FORWARD:
            gpio_set_value(enable, SPEED);
            gpio_set_value(motorPos, 1);
            gpio_set_value(motorNeg, 0);
            break;
        case BACK:
            gpio_set_value(enable, SPEED);
            gpio_set_value(motorPos, 0);
            gpio_set_value(motorNeg, 1);
            break;    
        case STOP:
            gpio_set_value(motorPos, 0);
            gpio_set_value(motorNeg, 0);
            break;
        default:
            break;           
    }
}
```

