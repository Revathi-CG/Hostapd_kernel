#ifndef __FILE_OPS_H
#define __FILE_OPS_H

#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include "syslog.h"   // your existing syslog header

// Open a file in kernel space
static inline struct file *k_fopen(const char *path, int flags, umode_t mode)
{
    struct file *f = filp_open(path, flags, mode);
    if (IS_ERR(f)) return NULL;
    return f;
}

// Read from a kernel-space file
static inline ssize_t k_fread(struct file *f, char *buf, size_t len, loff_t *pos)
{
    if (!f || !buf) return -EINVAL;
    mm_segment_t old_fs = get_fs();
    set_fs(KERNEL_DS);
    ssize_t ret = kernel_read(f, buf, len, pos);
    set_fs(old_fs);
    return ret;
}

// Close a kernel-space file
static inline int k_fclose(struct file *f)
{
    if (!f) return -EINVAL;
    filp_close(f, NULL);
    return 0;
}

#endif

