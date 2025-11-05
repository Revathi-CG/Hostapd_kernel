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
/*
 * Kernel-space stub for strtok_r to avoid hostapd build errors.
 * Since strtok_r is user-space only, we provide a dummy function.
 */

static inline char *strtok_r(char *str, const char *delim, char **saveptr)
{
    /* Do nothing, just return NULL in kernel build */
    (void)str;
    (void)delim;
    (void)saveptr;
    return NULL;
}

/* Macro to replace os_strdup in kernel build */
#define os_strdup(s) hostapd_strdup(s)

#endif

