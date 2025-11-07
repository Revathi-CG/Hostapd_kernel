#ifndef __TIME_H_
#define __TIME_H_

#include <linux/delay.h>

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
