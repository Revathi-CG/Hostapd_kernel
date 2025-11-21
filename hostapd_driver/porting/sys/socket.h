#ifndef __SOCKET_H_
#define __SOCKET_H_


#include <linux/net.h>
#include <linux/in.h>
#include <linux/uio.h>
#include <linux/socket.h>
#include <linux/file.h>
#include <linux/sched/signal.h>
#include <linux/errno.h>
#include <linux/slab.h>


// Kernel-space recvfrom wrapper
static inline int kernel_recvfrom(int sockfd, void *buf, size_t len, int flags,
                                  struct sockaddr *src_addr, int *addrlen)
{
    struct socket *sock;
    struct msghdr msg;
    struct kvec iov;
    int ret;

    // Look up kernel socket from integer fd
    sock = sockfd_lookup(sockfd, &ret);
    if (!sock)
        return ret;

    iov.iov_base = buf;
    iov.iov_len = len;

    memset(&msg, 0, sizeof(msg));
    msg.msg_name = src_addr;
    msg.msg_namelen = addrlen ? *addrlen : 0;

    ret = kernel_recvmsg(sock, &msg, &iov, 1, len, flags);

    if (addrlen)
        *addrlen = msg.msg_namelen;

    sockfd_put(sock);  // release reference

    return ret;
}

// Replace all user-space recvfrom calls
#define recvfrom kernel_recvfrom

// porting/sys/socket.h

static inline int kernel_sendto(int sockfd, const void *buf, size_t len, int flags,
                                struct sockaddr *addr, int addr_len)
{
    struct socket *sock;
    struct msghdr msg;
    struct kvec iov;
    int ret;

    sock = sockfd_lookup(sockfd, &ret);
    if (!sock)
        return ret;

    memset(&msg, 0, sizeof(msg));
    msg.msg_name = addr;
    msg.msg_namelen = addr_len;

    iov.iov_base = (void *)buf;
    iov.iov_len = len;

    ret = kernel_sendmsg(sock, &msg, &iov, 1, len);

    sockfd_put(sock);
    return ret;
}

#define sendto kernel_sendto

/*
 * Kernel-space replacement for socket()
 * Returns a fake integer FD (pointer cast) for hostapd compatibility.
 */
static inline int kernel_socket(int family, int type, int protocol)
{
    struct socket *sock;
    int ret;

    ret = sock_create(family, type, protocol, &sock);
    if (ret < 0)
        return ret;

    /*
     * In kernel there are no file descriptors, only struct socket*.
     * We cast it to int so hostapd's code compiles and passes it around,
     * then our wrappers (sendto/recvfrom/close) will convert it back.
     */
    return (int)(long)sock;
}

/* Redirect all user-space socket() calls */
#define socket(family, type, protocol) kernel_socket(family, type, protocol)

/*
 * Ensure your existing kernel_sendto() and kernel_recvfrom() wrappers
 * use sockfd_lookup() to convert this casted int back into struct socket *.
 * That’s why this trick works cleanly.
 */

/*
 * Kernel-space replacement for bind()
 * Works on sockets created via kernel_socket() wrapper.
 */
static inline int kernel_bind_wrapper(int sock_fd, struct sockaddr *uaddr, int addrlen)
{
    struct socket *sock = (struct socket *)(long)sock_fd;
    struct sockaddr_storage kaddr;

    if (!sock || !uaddr)
        return -EINVAL;

    /* Copy user address to kernel memory */
    memset(&kaddr, 0, sizeof(kaddr));
    memcpy(&kaddr, uaddr, addrlen);

    return kernel_bind(sock, (struct sockaddr *)&kaddr, addrlen);
}

/* Redirect all user-space bind() calls */
#define bind(fd, addr, len) kernel_bind_wrapper(fd, addr, len)

/*
 * Kernel-space safe wrapper for user-space connect()
 * Uses kernel_connect() internally.
 */
static inline int kernel_connect_wrapper(int sock_fd, struct sockaddr *uaddr, int addrlen)
{
    struct socket *sock;
    struct sockaddr_storage kaddr;
    int ret;

    // Convert user-space fd to kernel socket
    sock = sockfd_lookup(sock_fd, &ret);
    if (!sock)
        return ret;

    memset(&kaddr, 0, sizeof(kaddr));
    memcpy(&kaddr, uaddr, addrlen);

    // Use real kernel_connect()
    ret = kernel_connect(sock, (struct sockaddr *)&kaddr, addrlen, 0);

    sockfd_put(sock);
    return ret;
}

/* Redirect all user-space connect() calls */
#define connect(fd, addr, len) kernel_connect_wrapper(fd, addr, len)


#endif
