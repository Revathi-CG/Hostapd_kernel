#ifndef __TIME_H_
#define __TIME_H_


#include <linux/delay.h>
#include <linux/timekeeping.h> // for ktime_get_real_ts64
#include <linux/types.h>       // for __kernel_long_t

#include "signal.h"

/* Stub gettimeofday() for kernel space */
static inline int gettimeofday(struct timeval *tv, void *tz)
{
    if (!tv)
        return -1;

    struct timespec64 ts;
    ktime_get_real_ts64(&ts);

    tv->tv_sec = ts.tv_sec;
    tv->tv_usec = ts.tv_nsec / 1000;

    return 0;
}

/* Optional: helper to convert ktime_get_real_ts64 to struct timespec */
static inline void timespec_now(struct timespec *ts)
{
    struct timespec64 ts64;
    ktime_get_real_ts64(&ts64);
    ts->tv_sec = ts64.tv_sec;
    ts->tv_nsec = ts64.tv_nsec;
}

/* Stub clock_gettime for kernel space */
static inline int clock_gettime(int clk_id, struct timespec *ts)
{
    if (!ts)
        return -1;

    struct timespec64 ts64;
    ktime_get_real_ts64(&ts64);

    ts->tv_sec = ts64.tv_sec;
    ts->tv_nsec = ts64.tv_nsec;

    return 0;
}

/* Replace userspace sleep(sec) with kernel sleep in seconds */
static inline void sleep(unsigned int sec) {
    ssleep(sec);
}

static inline void usleep(unsigned int usec)
{
    if (usec < 2000) {
        udelay(usec);        // busy wait for short delays (<2ms)
    } else {
        usleep_range(usec, usec + 100); // proper sleep for longer delays
    }
}



#endif /* __TIME_H_ */
