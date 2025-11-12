#ifndef __STAT_H_
#define __STAT_H_

#include <linux/kernel.h>

/*
 * Kernel-space stub for mkdir()
 * Logs a warning and returns -EOPNOTSUPP
 */
static inline int kernel_mkdir(const char *path, umode_t mode)
{
    printk(KERN_WARNING "hostapd(kernel): mkdir() called on path '%s', ignoring\n", path);
    return -EOPNOTSUPP;  // operation not supported
}

/* Redirect all hostapd mkdir() calls to kernel stub */
#define mkdir(path, mode) kernel_mkdir(path, mode)

#endif /* __STAT_H_ */
