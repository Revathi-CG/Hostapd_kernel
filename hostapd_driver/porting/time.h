#ifndef __TIME_H_
#define __TIME_H_

#include <linux/delay.h>

/* Replace userspace sleep(sec) with kernel sleep in seconds */
static inline void sleep(unsigned int sec) {
    ssleep(sec);
}

#endif /* __TIME_H_ */
