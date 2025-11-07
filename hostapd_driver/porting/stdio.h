#ifndef __STDIO_H_
#define __STDIO_H_

#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/stdarg.h>
#include <linux/slab.h>  // kmalloc/kfree
/* Dummy stderr pointer */
#define stderr ((void*)0)

/* Redirect printf -> printk */
#define printf(fmt, ...) printk(KERN_INFO fmt, ##__VA_ARGS__)

/* Kernel-compatible fprintf stub */
static inline int fprintf(void *stream, const char *fmt, ...)
{
        char *buf = kmalloc(1024, GFP_KERNEL);
    if (!buf) return -ENOMEM;
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, 1024, fmt, args);
    va_end(args);

    printk("%s", buf); // redirect output to kernel log
    kfree(buf);
    return 0; // fprintf returns number of chars normally, 0 is safe here
}

#endif
