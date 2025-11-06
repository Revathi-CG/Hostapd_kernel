#ifndef __PORTING_INCLUDES_H_
#define __PORTING_INCLUDES_H_

/*
	 * Ensure networking address structs (in_addr, in6_addr) exist before hostapd uses them.
	 * Required when building hostapd in kernel space.
	 */
	#include <linux/in.h>      // struct in_addr
	#include <linux/in6.h>     // struct in6_addr

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

#endif

