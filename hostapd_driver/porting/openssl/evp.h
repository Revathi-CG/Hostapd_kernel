#ifndef __EVP_H_
#define __EVP_H_

#ifdef __KERNEL__

/* Dummy OpenSSL types */
typedef void BIGNUM;
typedef void BN_CTX;
typedef void EVP_MD;

/* Stub functions returning NULL or 0 */
static inline BIGNUM *BN_bin2bn(const unsigned char *s, int len, BIGNUM *ret)
{
    return NULL;
}

static inline int openssl_digest_vector(const EVP_MD *type, size_t num_elem,
                                        const unsigned char *addr[], const size_t *len,
                                        unsigned char *mac)
{
    return -1;
}

#endif
#endif /* __EVP_H_ */
