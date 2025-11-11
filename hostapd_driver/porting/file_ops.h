#ifndef __FILE_OPS_H
#define __FILE_OPS_H

#pragma once

#include <linux/fs.h>       // struct file, filp_open(), filp_close()
#include <linux/kernel.h>   // kernel_read()
#include <linux/uaccess.h>  // needed for file ops

#define FILE struct file
#define fseek   k_fseek
#define ftell   k_ftell
#define fopen(path, mode)        k_fopen(path, mode)
#define fgets(buf, size, fp)     k_fgets(buf, size, fp)
#define fclose(fp)               k_fclose(fp)
#define access k_access
#ifndef F_OK
#define F_OK 0   // "file exists" check flag used by access()
#endif
#define fflush(stream) k_fflush(stream)
#define fdatasync(fp) k_fdatasync(fp)
#define fileno(fp) k_fileno(fp)


// fopen → kernel file open
static inline FILE *k_fopen(const char *path, const char *mode)
{
    int flags = O_RDONLY;   // mode ignored for now
    return filp_open(path, flags, 0);
}

// fgets → read from kernel file
static inline char *k_fgets(char *buf, size_t size, FILE *fp)
{
    loff_t pos = fp->f_pos;
    int ret = kernel_read(fp, buf, size - 1, &pos);

    if (ret <= 0)
        return NULL;

    buf[ret] = '\0';
    fp->f_pos = pos;
    return buf;
}

// fclose → kernel file close
static inline int k_fclose(FILE *fp)
{
    return filp_close(fp, NULL);
}

// fread → kernel_read() equivalent
static inline size_t fread(void *ptr, size_t size, size_t nmemb, FILE *fp)
{
    loff_t pos = fp->f_pos;
    ssize_t ret = kernel_read(fp, ptr, size * nmemb, &pos);

    if (ret < 0)
        return 0;

    fp->f_pos = pos;
    return ret;
}

// fseek → move cursor in file
static inline int k_fseek(FILE *fp, loff_t offset, int whence)
{
    loff_t new_pos;

    switch (whence) {
    case SEEK_SET:
        new_pos = offset;
        break;
    case SEEK_CUR:
        new_pos = fp->f_pos + offset;
        break;
    default:
        return -EINVAL;
    }

    fp->f_pos = new_pos;
    return 0;
}

// ftell → get current cursor position
static inline long k_ftell(FILE *fp)
{
    return fp->f_pos;
}

// access() → check if file exists
static inline int k_access(const char *path, int mode)
{
    struct file *fp = filp_open(path, O_RDONLY, 0);
    if (IS_ERR(fp))
        return -ENOENT;

    filp_close(fp, NULL);
    return 0; // success (file exists)
}

// Flush file buffer (fflush equivalent in kernel)
static inline int k_fflush(FILE *fp)
{
    // Kernel does not buffer like userspace fflush() does,
    // but filp_flush() will sync metadata and dirty data.
    return vfs_fsync(fp, 0);
}

// fdatasync equivalent for kernel files
static inline int k_fdatasync(FILE *fp)
{
    // vfs_fsync flushes data & metadata to disk, closest match to fdatasync()
    return vfs_fsync(fp, 0);
}

// fileno() replacement (kernel FILE = struct file*)
static inline FILE *k_fileno(FILE *fp)
{
    return fp;  // we keep FILE as struct file* directly
}


#endif

