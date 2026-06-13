## Linux Kernel Module (Keyboard Driver)

### Files

**keyboard.c**
```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init keyboard_init(void) {
    printk(KERN_INFO "Keyboard driver loaded\n");
    return 0;
}

static void __exit keyboard_exit(void) {
    printk(KERN_INFO "Keyboard driver removed\n");
}

module_init(keyboard_init);
module_exit(keyboard_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Keyboard Driver");
MODULE_AUTHOR("Simple");
```

**Makefile** (indentation MUST be real tabs not spaces)
```makefile
obj-m += keyboard.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

---

### How to Run

```bash
# install kernel headers
sudo apt install linux-headers-$(uname -r)

# build
make

# load module
sudo insmod keyboard.ko

# verify loaded
lsmod | grep keyboard

# see printk output
dmesg | tail

# unload module
sudo rmmod keyboard

# see exit message
dmesg | tail

# clean build files
make clean
```

---

### Key Concepts

```
__init          runs on insmod  (like a constructor)
__exit          runs on rmmod   (like a destructor)
module_init()   registers init function with kernel
module_exit()   registers exit function with kernel
printk          kernel version of printf (no stdout in kernel)
kmalloc         kernel version of malloc
.ko             kernel object file (compiled module)
```

### Differences from normal C

```
printf    → printk
malloc    → kmalloc
main()    → module_init
.out      → .ko
stdio.h   → linux/module.h linux/kernel.h
```

### Check tab vs spaces in neovim

```
:set list    " ^I = tab (correct), spaces = will break make
```
