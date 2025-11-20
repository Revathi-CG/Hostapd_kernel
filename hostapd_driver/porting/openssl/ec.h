#ifndef __EC_H_
#define __EC_H_

#ifdef __KERNEL__

/* Dummy OpenSSL types for kernel mode */
typedef void EC_GROUP;
typedef void EC_POINT;
typedef void BIGNUM;
typedef void BN_CTX;


/* Stub functions to satisfy compiler in kernel mode */

static inline int EC_POINT_get_affine_coordinates_GFp(const EC_GROUP *group,
                                                      const EC_POINT *point,
                                                      BIGNUM *x, BIGNUM *y,
                                                      BN_CTX *ctx)
{
    return 0;
}


static inline int EC_POINT_set_affine_coordinates_GFp(const EC_GROUP *group,
                                                      EC_POINT *point,
                                                      const BIGNUM *x,
                                                      const BIGNUM *y,
                                                      BN_CTX *ctx)
{
    return 0;
}


static inline int EC_POINT_set_compressed_coordinates_GFp(const EC_GROUP *group,
                                                          EC_POINT *point,
                                                          const BIGNUM *x,
                                                          int y_bit,
                                                          BN_CTX *ctx)
{
    return 0;
}


static inline int EC_GROUP_get_curve_GFp(const EC_GROUP *group,
                                         BIGNUM *p, BIGNUM *a,
                                         BIGNUM *b, BN_CTX *ctx)
{
    return 0;
}

static inline BIGNUM *get_rfc3526_prime_1536(BIGNUM *bn)
{
    return NULL;
}

#endif /* __KERNEL__ */



#endif /* __EC_H_ */
