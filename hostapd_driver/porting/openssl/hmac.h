#ifndef __HMAC_H_
#define __HMAC_H_


#include <linux/crypto.h>
#include <linux/err.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/types.h>

/* ======================================================================
 * Hostapd crypto_openssl.c must use its own HMAC_CTX_new/HMAC_CTX_free.
 * Prevent ANY kernel HMAC override when compiling crypto_openssl.c.
 * ====================================================================== */
#ifdef HOSTAPD_COMPILING_CRYPTO_OPENSSL

/* OpenSSL 1.1+ removed these: make them harmless stubs */
#define HMAC_CTX_init(ctx)       do {} while (0)
#define HMAC_CTX_cleanup(ctx)    do {} while (0)

/* Remove our kernel HMAC replacement to avoid redefinition */
#undef HMAC_CTX_new
#undef HMAC_CTX_free

/* DO NOT define hostapd_HMAC_CTX_new/free for this file */
#define PORTING_DISABLE_KERNEL_HMAC

#endif /* HOSTAPD_COMPILING_CRYPTO_OPENSSL */

/* ================================================================
 * Disable EVP_MD_CTX fallback code in crypto_openssl.c
 * to avoid missing type/implicit declaration errors.
 * ================================================================ */
#ifdef HOSTAPD_COMPILING_CRYPTO_OPENSSL

/* Define dummy EVP_MD_CTX type so hostapd's fallback compiles */
typedef void EVP_MD_CTX;

/* Stub out old OpenSSL 1.0.2-style init/cleanup APIs */
#define EVP_MD_CTX_init(ctx)        do {} while (0)
#define EVP_MD_CTX_cleanup(ctx)     do {} while (0)

/* Prevent hostapd's fallback definitions from conflicting */
#define PORTING_DISABLE_EVP_MD_CTX

#endif /* HOSTAPD_COMPILING_CRYPTO_OPENSSL */


/* Kernel-space HMAC-MD5 replacement for hostapd */
static inline int kernel_hmac_md5(const u8 *key, size_t key_len,
                                  const u8 *data, size_t data_len,
                                  u8 *mic)
{
    struct crypto_shash *tfm;
    struct shash_desc *shash;
    int ret;

    tfm = crypto_alloc_shash("hmac(md5)", 0, 0);
    if (IS_ERR(tfm))
        return PTR_ERR(tfm);

    shash = kmalloc(sizeof(*shash) + crypto_shash_descsize(tfm), GFP_KERNEL);
    if (!shash) {
        crypto_free_shash(tfm);
        return -ENOMEM;
    }

    shash->tfm = tfm;
    // Remove the line: shash->flags = 0;

    ret = crypto_shash_setkey(tfm, key, key_len);
    if (ret)
        goto out;

    ret = crypto_shash_init(shash);
    if (ret)
        goto out;

    ret = crypto_shash_update(shash, data, data_len);
    if (ret)
        goto out;

    ret = crypto_shash_final(shash, mic);

out:
    kfree(shash);
    crypto_free_shash(tfm);
    return ret;
}

/* Redirect all calls to hmac_md5() to kernel_hmac_md5() */
#define hmac_md5 kernel_hmac_md5


#include <linux/kernel.h>

/* Kernel-space HMAC-SHA1 implementation */
static inline int kernel_hmac_sha1(const u8 *key, size_t key_len,
                                   const u8 *data, size_t data_len,
                                   u8 *digest)
{
    struct crypto_shash *tfm;
    struct shash_desc *shash;
    int ret;

    tfm = crypto_alloc_shash("hmac(sha1)", 0, 0);
    if (IS_ERR(tfm))
        return PTR_ERR(tfm);

    shash = kmalloc(sizeof(*shash) + crypto_shash_descsize(tfm), GFP_KERNEL);
    if (!shash) {
        crypto_free_shash(tfm);
        return -ENOMEM;
    }

    shash->tfm = tfm;
    // Modern kernels: no shash->flags

    ret = crypto_shash_setkey(tfm, key, key_len);
    if (ret)
        goto out;

    ret = crypto_shash_init(shash);
    if (ret)
        goto out;

    ret = crypto_shash_update(shash, data, data_len);
    if (ret)
        goto out;

    ret = crypto_shash_final(shash, digest);

out:
    kfree(shash);
    crypto_free_shash(tfm);
    return ret;
}

/* Redirect hostapd calls */
#define hmac_sha1(key, key_len, data, data_len, digest) \
        kernel_hmac_sha1(key, key_len, data, data_len, digest)

/* Kernel-space HMAC-SHA1 for multiple buffers */
static inline int kernel_hmac_sha1_vector(const u8 *key, size_t key_len,
                                          size_t num_elem,
                                          const u8 *addr[], const size_t *len,
                                          u8 *digest)
{
    struct crypto_shash *tfm;
    struct shash_desc *shash;
    int ret, i;

    tfm = crypto_alloc_shash("hmac(sha1)", 0, 0);
    if (IS_ERR(tfm))
        return PTR_ERR(tfm);

    shash = kmalloc(sizeof(*shash) + crypto_shash_descsize(tfm), GFP_KERNEL);
    if (!shash) {
        crypto_free_shash(tfm);
        return -ENOMEM;
    }

    shash->tfm = tfm;

    ret = crypto_shash_setkey(tfm, key, key_len);
    if (ret)
        goto out;

    ret = crypto_shash_init(shash);
    if (ret)
        goto out;

    for (i = 0; i < num_elem; i++) {
        ret = crypto_shash_update(shash, addr[i], len[i]);
        if (ret)
            goto out;
    }

    ret = crypto_shash_final(shash, digest);

out:
    kfree(shash);
    crypto_free_shash(tfm);
    return ret;
}

#define hmac_sha1_vector(key, key_len, num_elem, addr, len, digest) \
        kernel_hmac_sha1_vector(key, key_len, num_elem, addr, len, digest)


#ifndef MD5_MAC_LEN
#define MD5_MAC_LEN 16   /* MD5 produces 16-byte digests */
#endif

#ifndef SHA1_MAC_LEN
#define SHA1_MAC_LEN 20  /* SHA1 produces 20-byte digests */
#endif

#include <linux/crypto.h>
#include <linux/slab.h>
#include <linux/err.h>
typedef struct {
    struct crypto_shash *tfm;
    struct shash_desc desc;
} HMAC_CTX;

#ifndef PORTING_DISABLE_KERNEL_HMAC
static inline HMAC_CTX *hostapd_HMAC_CTX_new(void)
{
    HMAC_CTX *ctx = kmalloc(sizeof(HMAC_CTX), GFP_KERNEL);
    if (!ctx)
        return NULL;

    ctx->tfm = crypto_alloc_shash("hmac(sha256)", 0, 0);
    if (IS_ERR(ctx->tfm)) {
        kfree(ctx);
        return NULL;
    }

    ctx->desc.tfm = ctx->tfm;
    return ctx;
}

static inline void HMAC_CTX_free(HMAC_CTX *ctx)
{
    if (!ctx)
        return;
    if (ctx->tfm && !IS_ERR(ctx->tfm))
        crypto_free_shash(ctx->tfm);
    kfree(ctx);
}
#endif


static inline int HMAC_Init_ex(HMAC_CTX *ctx, const u8 *key, int keylen,
                               const void *unused1, void *unused2)
{
    return crypto_shash_setkey(ctx->tfm, key, keylen);
}

static inline int HMAC_Update(HMAC_CTX *ctx, const u8 *data, size_t datalen)
{
    return crypto_shash_update(&ctx->desc, data, datalen);  // pass desc
}

static inline int HMAC_Final(HMAC_CTX *ctx, u8 *out, unsigned int *outlen)
{
    int ret = crypto_shash_final(&ctx->desc, out);
    if (outlen)
        *outlen = 32;  // SHA256 output size
    return ret;
}

/* Only map HMAC_CTX_new to hostapd_HMAC_CTX_new if not compiling crypto_openssl.c */
#ifndef HOSTAPD_COMPILING_CRYPTO_OPENSSL
#ifndef HMAC_CTX_new
#define HMAC_CTX_new hostapd_HMAC_CTX_new
#define HMAC_CTX_free hostapd_HMAC_CTX_free
#endif
#endif /* HOSTAPD_COMPILING_CRYPTO_OPENSSL */

/* ----------------------------------------------------------
 * Default lengths
 * ---------------------------------------------------------- 
#ifndef MD5_MAC_LEN
#define MD5_MAC_LEN 16
#endif

#ifndef SHA1_MAC_LEN
#define SHA1_MAC_LEN 20
#endif

#ifndef SHA256_MAC_LEN
#define SHA256_MAC_LEN 32
#endif
*/
#endif /* __HMAC_H_ */
