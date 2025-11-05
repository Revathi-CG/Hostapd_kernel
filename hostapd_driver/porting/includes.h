#ifndef __PORTING_INCLUDES_H_
#define __PORTING_INCLUDES_H_

/*
	 * Ensure networking address structs (in_addr, in6_addr) exist before hostapd uses them.
	 * Required when building hostapd in kernel space.
	 */
	#include <linux/in.h>      // struct in_addr
	#include <linux/in6.h>     // struct in6_addr


/* This file gets force-included via Makefile to override random_init() */
#include "random.h"

#endif

