#ifndef __STRING_H_
#define __STRING_H_

#include <linux/slab.h>   // kmalloc, kfree
#include <linux/string.h> // strcpy, strlen

/* Kernel-space replacement for strdup */
static inline char *hostapd_strdup(const char *s)
{
    if (!s)
        return NULL;

    char *dup = kmalloc(strlen(s) + 1, GFP_KERNEL);
    if (!dup)
        return NULL;

    strcpy(dup, s);
    return dup;
}

/* Macro to replace os_strdup in kernel build */
#define os_strdup(s) hostapd_strdup(s)

#endif

