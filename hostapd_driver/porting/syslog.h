#ifndef __SYSLOG_H_
#define __SYSLOG_H_

#include <linux/kernel.h>  // For printk
#include <linux/printk.h>
#include <linux/stdarg.h>  // For va_list

/* Fake syslog priority values for kernel build */
#define LOG_EMERG   0
#define LOG_ALERT   1
#define LOG_CRIT    2
#define LOG_ERR     3
#define LOG_WARNING 4
#define LOG_NOTICE  5
#define LOG_INFO    6
#define LOG_DEBUG   7

/* Stub functions for kernel space (no-op) */
static inline void openlog(const char *ident, int option, int facility)
{
    /* Do nothing in kernel build */
}

static inline void closelog(void)
{
    /* Do nothing in kernel build */
}

/* Kernel-compatible syslog stub */
static inline void syslog(int priority, const char *fmt, ...)
{
    const char *klevel;

    switch (priority) {
    case LOG_EMERG:
    case LOG_ALERT:
    case LOG_CRIT:
    case LOG_ERR:     klevel = KERN_ERR; break;
    case LOG_WARNING: klevel = KERN_WARNING; break;
    case LOG_NOTICE:  klevel = KERN_NOTICE; break;
    case LOG_INFO:    klevel = KERN_INFO; break;
    case LOG_DEBUG:   klevel = KERN_DEBUG; break;
    default:          klevel = KERN_INFO; break;
    }

    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);   // format string safely
    va_end(args);

    printk("%s%s", klevel, buf);  // prepend KERN_* prefix
}

#endif

