#ifndef __SIGNAL_H_
#define __SIGNAL_H_



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
