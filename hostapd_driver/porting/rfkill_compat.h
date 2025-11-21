#ifndef RFKILL_COMPAT_H
#define RFKILL_COMPAT_H

#include <linux/types.h>
#include<stdlib.h>
/* Stub: return fake fd */
static inline int rfkill_open(const char *path)
{
    return 0; /* fake fd */
}

/* Stub: pretend to read successfully */
static inline int rfkill_read(int fd, void *buf, size_t len)
{
	if (buf)
        memset(buf, 0, len); // zero-initialize buffer to remove warnings
    return len;
}

/* Stub: pretend to close successfully */
static inline int rfkill_close(int fd)
{
    return 0;
}

/* Stub: fcntl non-blocking ignored */
static inline int rfkill_set_nonblock(int fd)
{
    return 0;
}

/* Stub: realpath just returns input pointer */
static inline char *rfkill_realpath(const char *path)
{
    return (char *)path;
}

#endif /* RFKILL_COMPAT_H */

