#ifndef HOSTAPD_PORTING_X509_H
#define HOSTAPD_PORTING_X509_H

/* Do NOT expose OpenSSL types or functions to the kernel */
#ifdef __KERNEL__

/* Kernel mode: create dummy placeholders so compilation doesn't fail */
typedef void ASN1_TIME;
typedef void X509;

#ifndef NEED_X509_COMPAT
static inline const ASN1_TIME *X509_get0_notBefore(const X509 *x)
{
    return NULL;
}

static inline const ASN1_TIME *X509_get0_notAfter(const X509 *x)
{
    return NULL;
}
#endif /* !NEED_X509_COMPAT */

#else /* !__KERNEL__ */

/* User space build uses real OpenSSL */
#include <openssl/asn1.h>
#include <openssl/x509.h>

#endif /* __KERNEL__ */

#ifdef __KERNEL__

/* Kernel: no OpenSSL available — return NULL safely */
static inline const ASN1_TIME *X509_get_notBefore(const X509 *x)
{
    return NULL;
}

static inline const ASN1_TIME *X509_get_notAfter(const X509 *x)
{
    return NULL;
}

#else /* user-space build */

/* User space: real OpenSSL fallback */
#ifndef HAVE_X509_GET_NOTBEFORE
static inline const ASN1_TIME * X509_get_notBefore(const X509 *x)
{
    return X509_get0_notBefore(x);
}
#endif

#ifndef HAVE_X509_GET_NOTAFTER
static inline const ASN1_TIME * X509_get_notAfter(const X509 *x)
{
    return X509_get0_notAfter(x);
}
#endif

#endif /* __KERNEL__ */


#endif /* HOSTAPD_PORTING_X509_H */

