#ifndef __ENDIAN_H_
#define __ENDIAN_H_

#include <linux/types.h>          // Needed for uint32_t etc.
#include <asm/byteorder.h>        // Provides __LITTLE_ENDIAN__, __BIG_ENDIAN__

/*
 * User-space compatibility macros for hostapd
 */

#ifndef __LITTLE_ENDIAN
#define __LITTLE_ENDIAN 1234
#endif

#ifndef __BIG_ENDIAN
#define __BIG_ENDIAN 4321
#endif

#ifndef __BYTE_ORDER
#ifdef __LITTLE_ENDIAN__
#define __BYTE_ORDER __LITTLE_ENDIAN
#else
#define __BYTE_ORDER __BIG_ENDIAN
#endif
#endif

#endif
