#ifndef __STAT_H_
#define __STAT_H_

#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/namei.h>
#include <linux/err.h>

/*
 * Kernel-space stub for mkdir()
 * Logs a warning and returns -EOPNOTSUPP
 */
static inline int kernel_mkdir(const char *path, umode_t mode)
{
    printk(KERN_WARNING "hostapd(kernel): mkdir() called on path '%s', ignoring\n", path);
    return -EOPNOTSUPP;  // operation not supported
}

/* Redirect all hostapd mkdir() calls to kernel stub */
#define mkdir(path, mode) kernel_mkdir(path, mode)

/*
 * Minimal kernel-space replacement for chmod()
 * Uses kern_path() + inode_permission() + notify_change()
 */
static inline int kernel_chmod(const char *filename, umode_t mode)
{
    struct path path;
    struct iattr newattrs;
    int err;

    err = kern_path(filename, LOOKUP_FOLLOW, &path);
    if (err)
        return err;

    newattrs.ia_mode = mode;
    newattrs.ia_valid = ATTR_MODE;

    inode_lock(path.dentry->d_inode);
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(6,3,0)
    // new signature: notify_change(struct mnt_idmap *, struct dentry *, struct iattr *, struct inode **)
    err = notify_change(mnt_idmap(path.mnt), path.dentry, &newattrs, NULL);
#else
    // old signature: notify_change(struct dentry *, struct iattr *, struct inode **)
    err = notify_change(path.dentry, &newattrs, NULL);
#endif
    inode_unlock(path.dentry->d_inode);

    path_put(&path);
    return err;
}

/* Redirect all user-space chmod() calls to our kernel version */
#define chmod(filename, mode) kernel_chmod(filename, mode)


#endif /* __STAT_H_ */
