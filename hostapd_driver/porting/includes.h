#ifndef __PORTING_INCLUDES_H_
#define __PORTING_INCLUDES_H_

/*
	 * Ensure networking address structs (in_addr, in6_addr) exist before hostapd uses them.
	 * Required when building hostapd in kernel space.
	 */
	#include <linux/in.h>      // struct in_addr
	#include <linux/in6.h>     // struct in6_addr

#define strtol(buf, end, base)    simple_strtol(buf, end, base)


// Hostapd expects FILE*
// Replace FILE with struct file (kernel)

typedef struct file FILE;
#define fopen(path, mode)        k_fopen(path, mode)
#define fgets(buf, size, fp)     k_fgets(buf, size, fp)
#define fclose(fp)               k_fclose(fp)


/* This file gets force-included via Makefile to override random_init() */
#include "random.h"
#include "errno.h"
#include "stdlib.h"
#include "time.h"

#include "string.h"
#include "grp.h"
#include "common.h"
#include "file_ops.h"
#include "wpabuf_fix.h"
#include "aes_encrypt_fix.h"
#include "sha1_prf_fix.h"
#include "byteswap.h"
#include "signal.h"

// Replace atoi() with kstrtoint() for kernel environment
#include <linux/kernel.h>    // kstrtoint()

/* required for size_t */
#include <linux/types.h>
#include <linux/kernel.h>

/* hostapd expects be16/be32 (big-endian) types from BSD socket headers.
 * Kernel equivalent types exist: __be16, __be32.
 */

typedef __be16 be16;
typedef __be32 be32;
typedef __be64 be64;


#include <linux/kstrtox.h>     // kstrtoul(), kstrtoint()

/* ---- Replacement for strtoul() ---- */
static inline unsigned long strtoul(const char *str, char **endp, int base)
{
    unsigned long val = 0;
        int ret = kstrtoul(str, base, &val);   // handle return value to avoid warning
    (void)ret;                             // silence unused warning

    if (endp)
	    *endp = (char *)str;  // hostapd never uses endp
    return val;
}
/*........atoi*/
static inline int k_atoi(const char *str)
{
    int val = 0;
        int ret = kstrtoint(str, 10, &val);    // handle return
        (void)ret;
    return val;
}

#define atoi(x) k_atoi(x)

/* Declare missing libc functions without including stdlib.h */
#ifndef __DECLARE_QSORT_ATOI_STRTOL
#define __DECLARE_QSORT_ATOI_STRTOL

/* qsort */
void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *));

#endif
// forward declaration (instead of including pbkdf2.h)
int pbkdf2_sha1(const char *passphrase, const unsigned char *ssid, size_t ssid_len,
                int iterations, unsigned char *buf, size_t buflen);

#include <linux/ip.h>
#include <linux/udp.h>

/* Map struct ip → struct iphdr for hostapd */
#define ip     iphdr

#endif

