#ifndef __EVP_H_
#define __EVP_H_

#ifdef __KERNEL__

/* Dummy OpenSSL types */
typedef void BIGNUM;
typedef void BN_CTX;
typedef void EVP_MD;
typedef void EVP_MD_CTX;
typedef void EVP_CIPHER;
typedef void EVP_CIPHER_CTX;


/* Stub functions returning NULL or 0 */
static inline BIGNUM *BN_bin2bn(const unsigned char *s, int len, BIGNUM *ret)
{
    return NULL;
}

void openssl_load_legacy_provider(void);


static inline int EVP_DigestInit_ex(EVP_MD_CTX *ctx, const EVP_MD *type, void *impl) { (void)ctx; (void)type; (void)impl; return 0; }
static inline int EVP_DigestUpdate(EVP_MD_CTX *ctx, const void *data, size_t len) { (void)ctx; (void)data; (void)len; return 0; }
static inline int EVP_DigestFinal(EVP_MD_CTX *ctx, unsigned char *md, unsigned int *len) { (void)ctx; (void)md; if (len) *len = 0; return 0; }

static inline unsigned long ERR_get_error(void) { return 0; }
static inline char *ERR_error_string(unsigned long e, char *buf) { (void)e; (void)buf; return "kernel_stub"; }


/* Stub SHA functions returning dummy EVP_MD pointer */
static inline const EVP_MD *EVP_sha1(void)   { return (EVP_MD *)0x1; }
static inline const EVP_MD *EVP_sha256(void) { return (EVP_MD *)0x2; }
static inline const EVP_MD *EVP_sha384(void) { return (EVP_MD *)0x3; }
static inline const EVP_MD *EVP_sha512(void) { return (EVP_MD *)0x4; }

static inline const EVP_CIPHER *EVP_aes_128_ecb(void) { return NULL; }
static inline const EVP_CIPHER *EVP_aes_192_ecb(void) { return NULL; }
static inline const EVP_CIPHER *EVP_aes_256_ecb(void) { return NULL; }
static inline EVP_CIPHER_CTX *EVP_CIPHER_CTX_new(void) { return NULL; }
static inline void EVP_CIPHER_CTX_free(EVP_CIPHER_CTX *ctx) { (void)ctx;}
static inline int EVP_EncryptInit_ex(EVP_CIPHER_CTX *ctx,
                                     const EVP_CIPHER *type,
				     void *engine,
                                     const u8 *key, const u8 *iv) { return 0; }
static inline int EVP_EncryptUpdate(EVP_CIPHER_CTX *ctx, u8 *out, int *outlen,
                                    const u8 *in, int inlen) { return 0; }
static inline int EVP_EncryptFinal_ex(EVP_CIPHER_CTX *ctx, u8 *out, int *outlen) { return 0; }
static inline int EVP_CIPHER_CTX_set_padding(EVP_CIPHER_CTX *ctx, int padding) { return 0; }
static inline int EVP_DecryptInit_ex(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *type,
                                     void *engine, const u8 *key, const u8 *iv) { return 0; }
static inline int EVP_DecryptUpdate(EVP_CIPHER_CTX *ctx, u8 *out, int *outlen,
                                    const u8 *in, int inlen) { return 0; }
static inline int EVP_DecryptFinal_ex(EVP_CIPHER_CTX *ctx, u8 *out, int *outlen) { return 0; }

#endif
#endif /* __EVP_H_ */
