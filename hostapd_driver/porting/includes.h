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

#include "string.h"
#include "grp.h"
#include "common.h"
#include "file_ops.h"

// Replace atoi() with kstrtoint() for kernel environment
#include <linux/kernel.h>    // kstrtoint()

static inline int k_atoi(const char *str)
{
    int val = 0;
    kstrtoint(str, 10, &val);
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


#endif

