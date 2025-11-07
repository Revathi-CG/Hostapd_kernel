#ifndef __SIGNAL_H_
#define __SIGNAL_H_

/* assert() */
//#include <assert.h>

/* struct timeval */
//#include <sys/time.h>

#include <linux/signal.h>      // signals

/* assert() is not available in kernel — define dummy */
#define assert(expr) ((void)0)

/*
 * Kernel does not define struct timeval anymore.
 * Define a minimal version to satisfy hostapd.
 */
#ifndef _STRUCT_TIMEVAL_DEFINED
#define _STRUCT_TIMEVAL_DEFINED
struct timeval {
    long tv_sec;
    long tv_usec;
};
#endif

struct timespec {
    __s64 tv_sec;
    long tv_nsec;
};

/*
 * DO NOT typedef fd_set. Kernel already defines it.
 * Simply forward declare the struct to silence compiler warnings.
 */
struct __kernel_fd_set;     // forward declaration ONLY

#define FD_ZERO(set)       do { } while(0)
#define FD_SET(fd,set)      do { } while(0)
#define FD_ISSET(fd,set)    (0)

static inline int select(int n, fd_set *r, fd_set *w, fd_set *e, void *tv)
{
    return 0; // Pretend nothing happened
}

static inline void signal(int sig, void (*handler)(int)) {}
static inline void alarm(int sec) {}

#endif
