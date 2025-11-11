#ifndef __HMAC_H_
#define __HMAC_H_


#include <linux/crypto.h>
#include <linux/err.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/types.h>

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



#endif /* __HMAC_H_ */
