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

// Define ENOTSUP if it's missing (it usually is in older kernel headers)
#ifndef ENOTSUP
#define ENOTSUP 95
#endif

// Stub utsname and uname function to allow compilation
struct utsname {
    char sysname[65];
    char nodename[65];
    char release[65];
    char version[65];
    char machine[65];
    char domainname[65];
};

static inline int uname(struct utsname *name)
{
    (void)name;
    return -1; // Indicate failure to acquire info in kernel space
}

#endif
