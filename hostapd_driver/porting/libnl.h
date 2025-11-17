#ifndef __LIBNL_H_
#define __LIBNL_H_

#include <stddef.h>   // <-- Add this
static inline struct nl_sock *nl_socket_alloc_cb(void *cb)
{
    return NULL; /* or allocate dummy struct */
}

static inline int nl_connect(struct nl_sock *sock, int protocol)
{
    return 0;
}

static inline void nl_socket_free(struct nl_sock *sock)
{
}

static inline int genl_connect(struct nl_sock *sock)
{
    return 0;  // dummy stub for kernel-space compilation
}

static inline int nl_socket_set_buffer_size(struct nl_sock *sock,
                                            int txbuf, int rxbuf)
{
    return 0;  // dummy stub for kernel-space compilation
}

static inline const char *nl_geterror(int err)
{
    return "libnl disabled";  // dummy message for kernel-space build
}

static inline void nl_socket_set_nonblocking(struct nl_sock *sock)
{
    // no-op stub for kernel-space build with nl80211 disabled
}

static inline int nl_socket_get_fd(struct nl_sock *sock)
{
    return -1; /* dummy fd, never actually used */
}


#endif
