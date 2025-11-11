#ifndef __WAIT_H_
#define __WAIT_H_

#include <linux/kernel.h>  // printk()

/* Stub replacement of userspace waitpid() for kernel environment */
static inline int waitpid(int pid, int *status, int options)
{
    printk(KERN_WARNING "hostapd(kernel): waitpid() called but not supported in kernel\n");

    if (status)
        *status = 0;   // mimic "child exited with success"

    return -1;  // return error to hostapd
}

#endif /* __WAIT_H_ */
