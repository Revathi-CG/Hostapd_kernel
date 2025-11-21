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
//typedef void DH;
typedef void BIGNUM;
typedef struct {
    BIGNUM *p;
    BIGNUM *g;
    BIGNUM *q;
    BIGNUM *pub_key;
    BIGNUM *priv_key;
} DH;


/* Stub functions returning NULL or 0 */
static inline BIGNUM *BN_bin2bn(const unsigned char *s, int len, BIGNUM *ret)
{
	(void)s;
    (void)len;
    (void)ret;
    return (BIGNUM *)0x1;  // dummy non-NULL pointer
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
/* Add missing CBC stubs */
static inline const EVP_CIPHER *EVP_aes_128_cbc(void) { return NULL; }
static inline const EVP_CIPHER *EVP_aes_192_cbc(void) { return NULL; }
static inline const EVP_CIPHER *EVP_aes_256_cbc(void) { return NULL; }

#endif
#ifdef __KERNEL__

/* Dummy OpenSSL types */
typedef void BIGNUM;
typedef void BN_CTX;

/* Stub BIGNUM functions */
static inline BIGNUM *BN_new(void) { return (BIGNUM *)0x1; }
static inline void BN_clear_free(BIGNUM *bn) { (void)bn; }
static inline int BN_is_zero(const BIGNUM *bn) { (void)bn; return 0; }
static inline int BN_is_one(const BIGNUM *bn) { (void)bn; return 0; }
static inline int BN_cmp(const BIGNUM *a, const BIGNUM *b) { (void)a; (void)b; return 0; }
static inline BN_CTX *BN_CTX_new(void) { return (BN_CTX *)0x1; }
static inline void BN_CTX_free(BN_CTX *ctx) { (void)ctx; }
static inline int BN_mod_exp(BIGNUM *r, const BIGNUM *a, const BIGNUM *p, const BIGNUM *m, BN_CTX *ctx)
{ (void)r; (void)a; (void)p; (void)m; (void)ctx; return 0; }
static inline int BN_mod_exp_mont_consttime(BIGNUM *r, const BIGNUM *a, const BIGNUM *p, const BIGNUM *m, BN_CTX *ctx, void *mont)
{ (void)r; (void)a; (void)p; (void)m; (void)ctx; (void)mont; return 0; }
static inline int BN_bn2bin(const BIGNUM *a, unsigned char *to) { (void)a; (void)to; return 0; }

static inline void BN_free(BIGNUM *bn) { (void)bn; }

/* Random */
static inline int BN_rand_range(BIGNUM *r, const BIGNUM *m)
{ (void)r; (void)m; return 1; }

/* Basic arithmetic */
static inline int BN_add(BIGNUM *c, const BIGNUM *a, const BIGNUM *b)
{ (void)c; (void)a; (void)b; return 1; }

static inline int BN_sub(BIGNUM *c, const BIGNUM *a, const BIGNUM *b)
{ (void)c; (void)a; (void)b; return 1; }

/* Mod operations */
static inline int BN_mod(BIGNUM *c, const BIGNUM *a, const BIGNUM *b, BN_CTX *ctx)
{ (void)c; (void)a; (void)b; (void)ctx; return 1; }

static inline BIGNUM *BN_mod_inverse(BIGNUM *r, const BIGNUM *a, const BIGNUM *n, BN_CTX *ctx)
{ (void)r; (void)a; (void)n; (void)ctx; return NULL; }

static inline int BN_mod_add(BIGNUM *r, const BIGNUM *a, const BIGNUM *b,
                             const BIGNUM *m, BN_CTX *ctx)
{ (void)r; (void)a; (void)b; (void)m; (void)ctx; return 1; }

static inline int BN_mod_mul(BIGNUM *r, const BIGNUM *a, const BIGNUM *b,
                             const BIGNUM *m, BN_CTX *ctx)
{ (void)r; (void)a; (void)b; (void)m; (void)ctx; return 1; }

static inline int BN_mod_sqr(BIGNUM *r, const BIGNUM *a, const BIGNUM *m, BN_CTX *ctx)
{ (void)r; (void)a; (void)m; (void)ctx; return 1; }

/* Shifts */
static inline int BN_rshift(BIGNUM *r, const BIGNUM *a, int n)
{ (void)r; (void)a; (void)n; return 1; }

static inline int BN_rshift1(BIGNUM *r, const BIGNUM *a)
{ (void)r; (void)a; return 1; }

/* Flags */
#define BN_FLG_CONSTTIME 1

static inline void BN_set_flags(BIGNUM *a, int flags)
{ (void)a; (void)flags; }

/* Misc */
static inline int BN_is_odd(const BIGNUM *a)
{ (void)a; return 0; }

static inline const BIGNUM *BN_value_one(void)
{ return (const BIGNUM *)0x1; }

static inline int BN_is_word(const BIGNUM *a, unsigned long w)
{ (void)a; (void)w; return 0; }

/* Division */
static inline int BN_div(BIGNUM *dv, BIGNUM *rem,
                         const BIGNUM *a, const BIGNUM *d, BN_CTX *ctx)
{ (void)dv; (void)rem; (void)a; (void)d; (void)ctx; return 1; }

#endif
static inline const EVP_CIPHER *EVP_des_ede3_cbc(void) { return NULL; }
static inline const EVP_CIPHER *EVP_des_cbc(void)      { return NULL; }
static inline const EVP_CIPHER *EVP_rc2_ecb(void)      { return NULL; }
static inline int EVP_CIPHER_CTX_set_key_length(EVP_CIPHER_CTX *ctx, int key_len)
{
    (void)ctx;
    (void)key_len;
    return 1;  // Return success
}

static inline DH *DH_new(void) { return (DH *)0x1; }
static inline void DH_free(DH *dh) { (void)dh; }

static inline int DH_generate_key(DH *dh) { (void)dh; return 1; }

static inline int BN_set_word(BIGNUM *bn, unsigned long w) { (void)bn; (void)w; return 1; }
/* BN functions */
static inline int BN_num_bytes(const BIGNUM *bn) { (void)bn; return 1; }

/* DH functions */
static inline int DH_size(const DH *dh) { (void)dh; return 1; }
static inline int DH_compute_key(unsigned char *key, const BIGNUM *pub_key, const DH *dh)
{ (void)key; (void)pub_key; (void)dh; return 1; }

/* EVP digest stubs */
static inline const EVP_MD *EVP_md5(void) { return (EVP_MD *)0x5; }

#ifdef __KERNEL__

/* RAND_bytes: use kernel RNG so code expecting RAND_bytes gets real random bytes */
#include <linux/random.h>
static inline int RAND_bytes(unsigned char *buf, int num)
{
    if (!buf || num <= 0)
        return 0;
    /* get_random_bytes returns void; fill buf with num bytes */
    get_random_bytes(buf, num);
    return 1; /* OpenSSL returns 1 on success */
}

/*
 * PBKDF2-HMAC-SHA1:
 * A full, correct PBKDF2 implementation should be done with HMAC-SHA1.
 * Implementing PBKDF2 properly is a bit more work; for now provide a
 * stub that returns failure (0) so compilation succeeds and callers
 * are aware. Replace with a proper implementation using kernel crypto
 * (crypto_shash/hmac) when you need real PBKDF2.
 *
 * Signature:
 * int PKCS5_PBKDF2_HMAC_SHA1(const char *pass, int passlen, const unsigned char *salt,
 *                            int saltlen, int iter, int keylen, unsigned char *out);
 */
static inline int PKCS5_PBKDF2_HMAC_SHA1(const char *pass, int passlen,
                                         const unsigned char *salt, int saltlen,
                                         int iter, int keylen, unsigned char *out)
{
    (void)pass; (void)passlen; (void)salt; (void)saltlen; (void)iter; (void)keylen; (void)out;
    /* TODO: Implement PBKDF2 using kernel crypto API. Return 0 to indicate failure now. */
    return 0;
}
typedef void CMAC_CTX;
static inline CMAC_CTX *CMAC_CTX_new(void) { return (CMAC_CTX *)0x1; }
static inline void CMAC_CTX_free(CMAC_CTX *ctx) { (void)ctx; }

/* CMAC_Init(ctx, key, keylen, cipher, impl) returns 1 on success in OpenSSL.
 * We return 1 to indicate success, but do NOT actually initialize.
 */
static inline int CMAC_Init(CMAC_CTX *ctx, const void *key, size_t keylen,
                            const void *cipher, void *impl)
{
    (void)ctx; (void)key; (void)keylen; (void)cipher; (void)impl;
    return 1;
}
static inline int CMAC_Update(CMAC_CTX *ctx, const unsigned char *data, size_t datalen)
{
    (void)ctx; (void)data; (void)datalen;
    return 1;
}
static inline int CMAC_Final(CMAC_CTX *ctx, unsigned char *out, size_t *poutlen)
{
    (void)ctx;
    if (poutlen) *poutlen = 16; /* typical AES-CMAC output length */
    if (out) memset(out, 0, 16); /* zero output as placeholder */
    return 1;
}

/* EVP_CIPHER_CTX_set_key_length stub (returns success) */
#endif

/* =========================
 *   RSA / EVP_PKEY / X509 STUBS
 * ========================= */

typedef void EVP_PKEY;
typedef void EVP_PKEY_CTX;
typedef void X509;

#define EVP_PKEY_RSA 1
#define RSA_PKCS1_OAEP_PADDING 4

/* PEM reader stubs */
static inline EVP_PKEY *PEM_read_PUBKEY(FILE *fp, void *a, void *b, void *c)
{
    (void)fp; (void)a; (void)b; (void)c;
    return (EVP_PKEY *)0x1;
}

static inline EVP_PKEY *PEM_read_PrivateKey(FILE *fp, void *a, void *b, void *c)
{
    (void)fp; (void)a; (void)b; (void)c;
    return (EVP_PKEY *)0x1;
}

static inline X509 *PEM_read_X509(FILE *fp, void *a, void *b, void *c)
{
    (void)fp; (void)a; (void)b; (void)c;
    return (X509 *)0x1;
}

/* X509 helper stubs */
static inline void X509_free(X509 *x509) { (void)x509; }

static inline int X509_cmp_current_time(const void *tm)
{
    (void)tm;
    return 0; /* valid */
}


static inline EVP_PKEY *X509_get_pubkey(X509 *x)
{
    (void)x;
    return (EVP_PKEY *)0x1;
}

/* EVP_PKEY functions */
static inline void EVP_PKEY_free(EVP_PKEY *p) { (void)p; }

static inline int EVP_PKEY_base_id(EVP_PKEY *pkey)
{
    (void)pkey;
    return EVP_PKEY_RSA;
}

/* EVP_PKEY_CTX stubs */
static inline EVP_PKEY_CTX *EVP_PKEY_CTX_new(EVP_PKEY *p, void *e)
{
    (void)p; (void)e;
    return (EVP_PKEY_CTX *)0x1;
}

static inline void EVP_PKEY_CTX_free(EVP_PKEY_CTX *ctx)
{
    (void)ctx;
}

static inline int EVP_PKEY_encrypt_init(EVP_PKEY_CTX *ctx)
{
    (void)ctx;
    return 1;
}

static inline int EVP_PKEY_decrypt_init(EVP_PKEY_CTX *ctx)
{
    (void)ctx;
    return 1;
}

static inline int EVP_PKEY_CTX_set_rsa_padding(EVP_PKEY_CTX *ctx, int pad)
{
    (void)ctx; (void)pad;
    return 1;
}

static inline int EVP_PKEY_CTX_set_rsa_oaep_md(EVP_PKEY_CTX *ctx, const EVP_MD *md)
{
    (void)ctx; (void)md;
    return 1;
}

static inline int EVP_PKEY_encrypt(EVP_PKEY_CTX *ctx,
                                   unsigned char *out, size_t *outlen,
                                   const unsigned char *in, size_t inlen)
{
    (void)ctx; (void)in; (void)inlen;
    if (outlen) *outlen = 32;
    if (out) memset(out, 0xAA, 32);
    return 1;
}

static inline int EVP_PKEY_decrypt(EVP_PKEY_CTX *ctx,
                                   unsigned char *out, size_t *outlen,
                                   const unsigned char *in, size_t inlen)
{
    (void)ctx; (void)in; (void)inlen;
    if (outlen) *outlen = 32;
    if (out) memset(out, 0xBB, 32);
    return 1;
}

/* rewind stub (kernel mode has no stdio rewind) */
#ifndef rewind
#define rewind(x) do { (void)(x); } while (0)
#endif


#endif /* __EVP_H_ */
