#ifndef __BYTESWAP_H_
#define __BYTESWAP_H_

#include <linux/swab.h>   // gives swab16(), swab32(), swab64()

// hostapd expects bswap_16/32/64, but kernel uses swab16/32/64
#ifndef bswap_16
#define bswap_16(x) swab16(x)
#endif

#ifndef bswap_32
#define bswap_32(x) swab32(x)
#endif

#ifndef bswap_64
#define bswap_64(x) swab64(x)
#endif

#endif
