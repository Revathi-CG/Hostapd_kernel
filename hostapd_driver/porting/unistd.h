#ifndef __UNISTD_H_
#define __UNISTD_H_

#include <linux/fs.h>
#include <linux/dcache.h>
#include <linux/path.h>
#include <linux/sched.h>
#include <linux/mount.h>
#include <linux/namei.h>
#include <linux/version.h>
#include <linux/fs_struct.h>   // REQUIRED for get_pwd()

/* Kernel-space stub for getopt */
static inline int getopt(int argc, char * const argv[], const char *optstring)
{
    /* Stub: do nothing, always return -1 to indicate end of options */
    return -1;
}

/* Provide stub for optind if code uses it */
static int optind  __attribute__((unused)) = 1;

/* Stub for optarg in kernel space */
static char *optarg  __attribute__((unused))= NULL;

#ifndef __KERNEL_GETPID_STUB__
#define __KERNEL_GETPID_STUB__

/* Kernel equivalent of getpid() is task_pid_nr(current) */
#include <linux/sched.h>

static inline int getpid(void)
{
    return task_pid_nr(current);
}

#endif

#ifndef _PORTING_UNISTD_H
#define _PORTING_UNISTD_H

#include <linux/fs.h>
#include <linux/namei.h>
#include <linux/version.h>

static inline int unlink(const char *path)
{
    struct path kpath;
    int err;

    err = kern_path(path, LOOKUP_FOLLOW, &kpath);
    if (err)
        return err;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,3,0)
    {
        struct mnt_idmap *idmap = NULL;

        err = vfs_unlink(
                idmap,
                d_inode(kpath.dentry->d_parent),
                kpath.dentry,
                NULL);
    }
#else
    err = vfs_unlink(
            d_inode(kpath.dentry->d_parent),
            kpath.dentry,
            NULL);
#endif

    path_put(&kpath);
    return err;
}

#endif

static inline char *getcwd(char *buf, size_t size)
{
    struct path pwd;
    char *tmp;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,17,0)
    // New API
//    get_pwd(current, &pwd);
#else
    // Old API
    get_fs_pwd(current->fs, &pwd);
#endif

    tmp = d_path(&pwd, buf, size);

    return IS_ERR(tmp) ? NULL : tmp;
}

#pragma once

// stub setenv() for kernel space
static inline int setenv(const char *name, const char *value, int overwrite)
{
    // Kernel space has no process-level environment variables.
    // Just pretend that setting the variable worked.
    return 0;
}

// stub unsetenv() for kernel space
static inline int unsetenv(const char *name)
{
    // No environment variables exist in kernel modules.
    return 0;
}

static inline int fork(void)
{
    printk(KERN_ERR "fork() not supported in kernel\n");
    return -1;
}

static inline int execv(const char *path, char *const argv[])
{
    printk(KERN_WARNING "hostapd(kernel): execv() called but not supported in kernel\n");
    return -1;  // act like exec failed
}

/*
 * Kernel-space stub for lchown()
 * In kernel, file ownership management is not available to modules directly.
 * So, we stub it to return success (0) to satisfy hostapd build.
 */
static inline int kernel_lchown(const char *path, uid_t owner, gid_t group)
{
    printk(KERN_WARNING "hostapd(kernel): lchown() called on '%s', ignored\n", path);
    return 0;  // pretend success
}

/* Redirect lchown() to our stub */
#define lchown(path, owner, group) kernel_lchown(path, owner, group)

/*
 * Kernel-space replacement for close()
 * Works for both sockets and regular file descriptors.
 */
static inline int kernel_close(int fd)
{
    struct socket *sock;
    struct file *filp;
    int ret = 0;

    // Try to interpret fd as a socket
    sock = sockfd_lookup(fd, &ret);
    if (sock) {
        sockfd_put(sock);   // release socket reference
        return 0;
    }

    // Otherwise treat it as a normal file
    filp = fget(fd);
    if (filp) {
        ret = filp_close(filp, NULL);
        fput(filp);
        return ret;
    }

    return -EBADF;  // Invalid FD
}

/* Redirect user-space close() to our kernel version */
#define close(fd) kernel_close(fd)


#endif
