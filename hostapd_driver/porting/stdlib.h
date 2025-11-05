#ifndef __STDLIB_H_
#define __STDLIB_H_

#include <linux/slab.h>   // kmalloc, kfree, krealloc

// Replace user-space realloc with kernel-space equivalent
#define realloc(ptr, size) krealloc((ptr), (size), GFP_KERNEL)

// Replace malloc and free too
#define malloc(size) kmalloc((size), GFP_KERNEL)
#define free(ptr) kfree(ptr)


#endif
