/* libultra 2.0I gu/mtxutil.c: guMtxIdent (follows guMtxF2L/guMtxIdentF in gu_mtx.c). */
#include "types.h"

typedef struct Mtx {
    s32 m[4][4];
} Mtx;

extern void guMtxIdentF(f32 mf[4][4]);
extern void guMtxF2L(f32 mf[4][4], Mtx *m);

void guMtxIdent(Mtx *m)
{
    f32 mf[4][4];

    guMtxIdentF(mf);
    guMtxF2L(mf, m);
}
