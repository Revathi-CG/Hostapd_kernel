#ifndef __RANDOM_H_
#define __RANDOM_H_

/*
 * Fix conflict between:
 *   kernel:  void random_init(void);
 *   hostapd: void random_init(const char *entropy_file);
 */

#include <linux/random.h>   // bring kernel declaration first

#ifdef random_init
#undef random_init          // remove kernel definition
#endif

// redirect hostapd's random_init() to our kernel-safe stub
#define random_init(entropy_file) hostapd_random_init(entropy_file)

static inline void hostapd_random_init(const char *entropy_file)
{
    /* NO-OP stub: kernel already handles RNG initialization */
//    (void) entropy_file;  // prevent unused variable warning
}

#endif /* __RANDOM_H_ */

