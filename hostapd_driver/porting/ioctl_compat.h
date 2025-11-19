// porting/ioctl_compat.h
#ifndef IOCTL_COMPAT_H
#define IOCTL_COMPAT_H

#include <linux/types.h>

static inline int kernel_ioctl(int fd, unsigned long request, const void *arg)
{
	(void)fd;
    (void)request;
    (void)arg;
    return 0; // stub: pretend ioctl succeeds
}

#ifndef ioctl
#define ioctl(fd, request, arg) kernel_ioctl(fd, request, arg)
#endif

#endif /* IOCTL_COMPAT_H */

