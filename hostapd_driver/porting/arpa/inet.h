#ifndef __INET_H_
#define __INET_H_

#include <linux/kernel.h>
#include <linux/in.h>
#include <linux/socket.h>
#include <linux/net.h>
#include <linux/string.h>

/*
 * Replacement for inet_ntoa() — converts IPv4 to string
 * Kernel version using snprintf into a static buffer.
 */

static inline char *kernel_inet_ntoa(struct in_addr in)
{
    static char buf[16]; // "xxx.xxx.xxx.xxx"
    unsigned char *bytes = (unsigned char *)&in.s_addr;

    snprintf(buf, sizeof(buf), "%u.%u.%u.%u",
            bytes[0], bytes[1], bytes[2], bytes[3]);

    return buf;
}

/*
 * Override inet_ntoa() calls from hostapd to use kernel_inet_ntoa()
 */
#define inet_ntoa(a) kernel_inet_ntoa(a)

/*
 * Replacement for inet_ntop() — IPv4 + IPv6 support
 */
static inline const char *kernel_inet_ntop(int af,
                                           const void *src,
                                           char *dst,
                                           size_t size)
{
    if (!dst || size == 0)
        return NULL;

    if (af == AF_INET) {
        const unsigned char *bytes = src;
        snprintf(dst, size, "%u.%u.%u.%u",
                 bytes[0], bytes[1], bytes[2], bytes[3]);
        return dst;
    }
    else if (af == AF_INET6) {
        const struct in6_addr *addr6 = src;
        snprintf(dst, size,
                 "%pI6", addr6);     // kernel format for IPv6
        return dst;
    }

    return NULL;
}

#define inet_ntop(af, src, dst, size) kernel_inet_ntop(af, src, dst, size)


#endif
