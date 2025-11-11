#ifndef __INET_H_
#define __INET_H_

#include <linux/kernel.h>
#include <linux/in.h>
#include <linux/socket.h>
#include <linux/net.h>
#include <linux/string.h>
#include <linux/inet.h>   // <-- this one declares in6_pton()

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

/*
 * Replacement for inet_aton() — convert string IPv4 to struct in_addr
 */
static inline int kernel_inet_aton(const char *cp, struct in_addr *addr)
{
    unsigned int b0, b1, b2, b3;

    if (!cp || !addr)
        return 0;

    /*
     * sscanf parses dotted IPv4 string into 4 integers
     */
    if (sscanf(cp, "%u.%u.%u.%u", &b0, &b1, &b2, &b3) != 4)
        return 0;

    addr->s_addr = (b0 & 0xff) |
                   ((b1 & 0xff) << 8) |
                   ((b2 & 0xff) << 16) |
                   ((b3 & 0xff) << 24);

    return 1;   // success
}

#define inet_aton(txt, addr) kernel_inet_aton(txt, addr)

#include <linux/in6.h>

/*
 * Replacement for inet_pton() supporting IPv4 and IPv6
 */
static inline int kernel_inet_pton(int af, const char *src, void *dst)
{
    if (!src || !dst)
        return -1;

    if (af == AF_INET) {
               struct in_addr *addr4 = (struct in_addr *)dst;
	    return kernel_inet_aton(src, addr4);  // reuse earlier implementation
    }

    if (af == AF_INET6) {
        /* Kernel native IPv6 parser */
    	    return in6_pton(src, strlen(src), dst, '\0', NULL) ? 1 : 0;
    }

    return -1;
}

#define inet_pton(af, src, dst) kernel_inet_pton(af, src, dst)


#endif
