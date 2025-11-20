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

void openssl_load_legacy_provider(void);
#endif
#endif /* __EVP_H_ */
