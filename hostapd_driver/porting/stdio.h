#ifndef __STDIO_H_
#define __STDIO_H_

#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/stdarg.h>


typedef void FILE;

/* Kernel-compatible fprintf stub */
static inline int fprintf(void *stream, const char *fmt, ...)
{
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    printk(KERN_INFO "%s", buf); // redirect output to kernel log
    return 0; // fprintf returns number of chars normally, 0 is safe here
}

#endif
