/*
 * GCC 2.8.0 libgcc2 signed double-word division helper.
 *
 * Derived from GCC's libgcc2.c/longlong.h under GPL-2.0-or-later with the
 * GCC Runtime Library Exception.  This unit is built with the SN Systems
 * GCC 2.8.x N64 compiler used for the retail runtime library.
 */

typedef unsigned int UQItype __attribute__((mode(QI)));
typedef int SItype __attribute__((mode(SI)));
typedef unsigned int USItype __attribute__((mode(SI)));
typedef int DItype __attribute__((mode(DI)));
typedef unsigned int UDItype __attribute__((mode(DI)));

typedef union {
    struct {
        SItype high;
        SItype low;
    } s;
    DItype ll;
} DIunion;

#define SI_TYPE_SIZE (sizeof(SItype) * 8)
#define __BITS4 (SI_TYPE_SIZE / 4)
#define __ll_B (1L << (SI_TYPE_SIZE / 2))
#define __ll_lowpart(t) ((USItype)(t) % __ll_B)
#define __ll_highpart(t) ((USItype)(t) / __ll_B)

#define sub_ddmmss(sh, sl, ah, al, bh, bl) \
    do { \
        USItype __x; \
        __x = (al) - (bl); \
        (sh) = (ah) - (bh) - (__x > (al)); \
        (sl) = __x; \
    } while (0)

#define umul_ppmm(w1, w0, u, v) \
    __asm__("multu %2,%3" \
            : "=l" ((USItype)(w0)), "=h" ((USItype)(w1)) \
            : "d" ((USItype)(u)), "d" ((USItype)(v)))

#define udiv_qrnnd(q, r, n1, n0, d) \
    do { \
        USItype __d1, __d0, __q1, __q0; \
        USItype __r1, __r0, __m; \
        __d1 = __ll_highpart(d); \
        __d0 = __ll_lowpart(d); \
        __r1 = (n1) % __d1; \
        __q1 = (n1) / __d1; \
        __m = (USItype)__q1 * __d0; \
        __r1 = __r1 * __ll_B | __ll_highpart(n0); \
        if (__r1 < __m) { \
            __q1--, __r1 += (d); \
            if (__r1 >= (d)) \
                if (__r1 < __m) \
                    __q1--, __r1 += (d); \
        } \
        __r1 -= __m; \
        __r0 = __r1 % __d1; \
        __q0 = __r1 / __d1; \
        __m = (USItype)__q0 * __d0; \
        __r0 = __r0 * __ll_B | __ll_lowpart(n0); \
        if (__r0 < __m) { \
            __q0--, __r0 += (d); \
            if (__r0 >= (d)) \
                if (__r0 < __m) \
                    __q0--, __r0 += (d); \
        } \
        __r0 -= __m; \
        (q) = (USItype)__q1 * __ll_B | __q0; \
        (r) = __r0; \
    } while (0)

static const UQItype __clz_tab[] = {
    0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
    6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
};

#define count_leading_zeros(count, x) \
    do { \
        USItype __xr = (x); \
        USItype __a; \
        if (SI_TYPE_SIZE <= 32) { \
            __a = __xr < (1 << 2 * __BITS4) \
                    ? (__xr < (1 << __BITS4) ? 0 : __BITS4) \
                    : (__xr < (1 << 3 * __BITS4) \
                               ? 2 * __BITS4 : 3 * __BITS4); \
        } else { \
            for (__a = SI_TYPE_SIZE - 8; __a > 0; __a -= 8) \
                if (((__xr >> __a) & 0xff) != 0) \
                    break; \
        } \
        (count) = SI_TYPE_SIZE - (__clz_tab[__xr >> __a] + __a); \
    } while (0)

static inline UDItype
__udivmoddi4(UDItype n, UDItype d, UDItype *rp)
{
    DIunion ww;
    DIunion nn, dd;
    DIunion rr;
    USItype d0, d1, n0, n1, n2;
    USItype q0, q1;
    USItype b, bm;

    nn.ll = n;
    dd.ll = d;
    d0 = dd.s.low;
    d1 = dd.s.high;
    n0 = nn.s.low;
    n1 = nn.s.high;

    if (d1 == 0) {
        if (d0 > n1) {
            count_leading_zeros(bm, d0);
            if (bm != 0) {
                d0 = d0 << bm;
                n1 = (n1 << bm) | (n0 >> (SI_TYPE_SIZE - bm));
                n0 = n0 << bm;
            }
            udiv_qrnnd(q0, n0, n1, n0, d0);
            q1 = 0;
        } else {
            if (d0 == 0)
                d0 = 1 / d0;
            count_leading_zeros(bm, d0);
            if (bm == 0) {
                n1 -= d0;
                q1 = 1;
            } else {
                b = SI_TYPE_SIZE - bm;
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;
                udiv_qrnnd(q1, n1, n2, n1, d0);
            }
            udiv_qrnnd(q0, n0, n1, n0, d0);
        }
        if (rp != 0) {
            rr.s.low = n0 >> bm;
            rr.s.high = 0;
            *rp = rr.ll;
        }
    } else {
        if (d1 > n1) {
            q0 = 0;
            q1 = 0;
            if (rp != 0) {
                rr.s.low = n0;
                rr.s.high = n1;
                *rp = rr.ll;
            }
        } else {
            count_leading_zeros(bm, d1);
            if (bm == 0) {
                if (n1 > d1 || n0 >= d0) {
                    q0 = 1;
                    sub_ddmmss(n1, n0, n1, n0, d1, d0);
                } else {
                    q0 = 0;
                }
                q1 = 0;
                if (rp != 0) {
                    rr.s.low = n0;
                    rr.s.high = n1;
                    *rp = rr.ll;
                }
            } else {
                USItype m1, m0;
                b = SI_TYPE_SIZE - bm;
                d1 = (d1 << bm) | (d0 >> b);
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;
                udiv_qrnnd(q0, n1, n2, n1, d1);
                umul_ppmm(m1, m0, q0, d0);
                if (m1 > n1 || (m1 == n1 && m0 > n0)) {
                    q0--;
                    sub_ddmmss(m1, m0, m1, m0, d1, d0);
                }
                q1 = 0;
                if (rp != 0) {
                    sub_ddmmss(n1, n0, n1, n0, m1, m0);
                    rr.s.low = (n1 << b) | (n0 >> bm);
                    rr.s.high = n1 >> bm;
                    *rp = rr.ll;
                }
            }
        }
    }

    ww.s.low = q0;
    ww.s.high = q1;
    return ww.ll;
}

typedef int word_type __attribute__((mode(SI)));

static inline DItype
__negdi2(DItype u)
{
    DIunion w;
    DIunion uu;

    uu.ll = u;
    w.s.low = -uu.s.low;
    w.s.high = -uu.s.high - ((USItype)w.s.low > 0);
    return w.ll;
}

DItype
__divdi3(DItype u, DItype v)
{
    word_type c = 0;
    DIunion uu, vv;
    DItype w;

    uu.ll = u;
    vv.ll = v;
    if (uu.s.high < 0)
        c = ~c, uu.ll = __negdi2(uu.ll);
    if (vv.s.high < 0)
        c = ~c, vv.ll = __negdi2(vv.ll);
    w = __udivmoddi4(uu.ll, vv.ll, (UDItype *)0);
    if (c)
        w = __negdi2(w);
    return w;
}
