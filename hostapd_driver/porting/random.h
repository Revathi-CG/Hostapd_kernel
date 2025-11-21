#ifndef __RANDOM_H_
#define __RANDOM_H_

/*
 * Fix conflict between:
 *   kernel:  void random_init(void);
 *   hostapd: void random_init(const char *entropy_file);
 */

#include <linux/random.h>   // bring kernel declaration first
#include <linux/types.h>     // for size_t/ssize_t if needed
#include <linux/compiler.h>  // For compiler attributes
			     //
#ifdef random_init
#undef random_init          // remove kernel definition
#endif

#define random_init(entropy_file) hostapd_random_init(entropy_file)


#ifndef __HOSTAPD_RANDOM_C__ // Or some other non-defined symbol

static inline void hostapd_random_init(const char *entropy_file)
{
    /* NO-OP stub: kernel already handles RNG initialization */
    (void) entropy_file;  // prevent unused variable warning
}
#endif

// Userspace random() → kernel get_random_u32()
static inline long random(void)
{
    return (long)get_random_u32();
}

static inline void srandom(unsigned int seed)
{
	(void)seed;
    // No-op in kernel, random generator is already seeded
}
#ifndef __HOSTAPD_RANDOM_C__ // Or some other non-defined symbol

static inline void random_write_entropy(void)
{
    // Prevents conflict/implicit declaration of fwrite in random.c
}

static inline void random_read_entropy(void)
{
}
#endif
#endif /* __RANDOM_H_ */

