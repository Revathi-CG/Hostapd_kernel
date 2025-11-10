#ifndef __FILE_OPS_H
#define __FILE_OPS_H

#pragma once

#include <linux/fs.h>       // struct file, filp_open(), filp_close()
#include <linux/kernel.h>   // kernel_read()
#include <linux/uaccess.h>  // needed for file ops

#define FILE struct file

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


#endif

