// porting/readlink_compat.h
#ifndef READLINK_COMPAT_H
#define READLINK_COMPAT_H

#include <linux/types.h>

static inline int kernel_readlink(const char *path, char *buf, size_t bufsize)
{
    return 0; // pretend zero bytes read
}

#ifndef readlink
#define readlink(path, buf, bufsize) kernel_readlink(path, buf, bufsize)
#endif

#endif /* READLINK_COMPAT_H */

