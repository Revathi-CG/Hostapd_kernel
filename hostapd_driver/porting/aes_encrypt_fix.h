#ifndef __AES_ENCRYPT_FIX_H
#define __AES_ENCRYPT_FIX_H


/* Bring in kernel AES declaration */
#include <crypto/aes.h>

#undef aes_encrypt
#undef aes_decrypt
#ifndef CONFIG_AES_CRYPTO_OPENSSL // or a similar macro that guards hostapd's own implementation
#define aes_encrypt hostapd_aes_encrypt
#define aes_decrypt hostapd_aes_decrypt

/* Wrapper function expected by hostapd */
static inline int hostapd_aes_encrypt(void *ctx, const u8 *plain, u8 *crypt)
{
    /* Correct argument order for kernel aes_encrypt(): out, in */
   aes_encrypt((void *)ctx, crypt,(u8 *)plain);
    return 0;
}

static inline int hostapd_aes_decrypt(void *ctx, const u8 *crypt, u8 *plain)
{
    aes_decrypt((void *)ctx, plain, (u8 *)crypt);
    return 0;
}
#endif

#ifdef __KERNEL__
#include <crypto/hash.h>

static int __attribute__((unused)) hostapd_hmac_sha256(const u8 *key, size_t keylen,
                               const u8 *data, size_t datalen,
                               u8 *out)
{
    struct crypto_shash *tfm;
    struct shash_desc *desc;
    int ret;

    tfm = crypto_alloc_shash("hmac(sha256)", 0, 0);
    if (IS_ERR(tfm))
        return PTR_ERR(tfm);

    desc = kmalloc(sizeof(*desc) + crypto_shash_descsize(tfm), GFP_KERNEL);
    if (!desc) {
        crypto_free_shash(tfm);
        return -ENOMEM;
    }

    desc->tfm = tfm;
//    desc->flags = 0;

    crypto_shash_setkey(tfm, key, keylen);
    ret = crypto_shash_digest(desc, data, datalen, out);

    kfree(desc);
    crypto_free_shash(tfm);
    return ret;
}
#endif


#endif /* HOSTAPD_AES_ENCRYPT_FIX_H */
