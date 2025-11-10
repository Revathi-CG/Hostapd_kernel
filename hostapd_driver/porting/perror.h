/* Kernel-space replacement for perror() */
#ifndef PORTING_PERROR_OVERRIDE
#define PORTING_PERROR_OVERRIDE

#include <linux/printk.h>

static inline void perror(const char *s)
{
    printk(KERN_ERR "hostapd error: %s\n", s);
}

#endif

