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


#endif
