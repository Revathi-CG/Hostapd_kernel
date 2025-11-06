#ifndef __ERRNO_H_
#define __ERRNO_H_

/* Kernel doesn't have errno; define a dummy macro for hostapd use */
/*#define errno (-1)   // placeholder, kernel errors are returned as negative ints-- wrong*/

#pragma once

/* Hostapd expects errno to exist. In kernel we do not use global errno.
 * Applications should check return values directly, not errno.
 */

#include <linux/errno.h>    // imports -ENOENT, -EINVAL, etc.
static inline int errno_dummy(void)
{
    return -1;   // always return generic error
}
#define errno errno_dummy()


/* Dummy strerror for kernel builds */
static inline const char *strerror(int err)
{
    switch (err) {
        case -1: return "generic error";
        default: return "unknown error";
    }
}

#endif
