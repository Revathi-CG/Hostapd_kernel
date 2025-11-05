#ifndef __ERRNO_H_
#define __ERRNO_H_

/* Kernel doesn't have errno; define a dummy macro for hostapd use */
#define errno (-1)   // placeholder, kernel errors are returned as negative ints

/* Dummy strerror for kernel builds */
static inline const char *strerror(int err)
{
    switch (err) {
        case -1: return "generic error";
        default: return "unknown error";
    }
}

#endif
