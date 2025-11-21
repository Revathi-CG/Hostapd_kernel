#ifndef __STDLIB_H_
#define __STDLIB_H_


#include <linux/slab.h>   // kmalloc, kfree, krealloc

// Replace user-space realloc with kernel-space equivalent
#define realloc(ptr, size) krealloc((ptr), (size), GFP_KERNEL)

// Replace malloc and free too
#define malloc(size) kmalloc((size), GFP_KERNEL)
// calloc() mapping → kernel equivalent
#define calloc(n, size) k_calloc(n, size)

#define free(ptr) __kernel_free(ptr)

static inline void __kernel_free(void *ptr)
{
    kfree(ptr);
}

/* Kernel-compatible stub for exit() */
static inline void exit(int code)
{
    /* In kernel space, we cannot exit a process.
       So, we do nothing or optionally print a warning. */
    printk(KERN_WARNING "hostapd called exit(%d) in kernel space - ignored\n", code);
}

static inline void *k_calloc(size_t n, size_t size)
{
    return kzalloc(n * size, GFP_KERNEL);   // kernel zeroed allocation
}


#endif
