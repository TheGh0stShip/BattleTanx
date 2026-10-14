#include "types.h"

typedef struct PerspectiveMtx {
    s32 m[4][4];
} PerspectiveMtx;

extern s32 gRandomPairModulus __asm__("D_80141050");
extern f32 D_80074F78;
extern f32 D_80074F7C;
extern f32 D_80074F80;
extern f32 D_80074F84;
extern f32 D_8035BC68;
extern f32 D_8035BC6C;
extern u8 D_8035BC70;
extern u8 D_8035BC71;
extern s16 D_8035BC72;
extern u8 D_8035BC74;
extern u8 D_8035BC75;
extern s16 D_8035BC76;
extern s16 D_8035BC78;
extern PerspectiveMtx D_8035BC80;
extern u16 D_8035BCC4;

extern u32 next_random_u32(void) __asm__("func_800F38F4");
extern void guPerspective(PerspectiveMtx *m, u16 *perspNorm, f32 fovy, f32 aspect, f32 near, f32 far,
                          f32 scale) __asm__("func_80114970");

void init_random_perspective_state(void) __asm__("func_800F45C8");

void init_random_perspective_state(void)
{
    u8 first;

    first = next_random_u32() % (u32)gRandomPairModulus;
    D_8035BC72 = 0;
    D_8035BC70 = first;
    D_8035BC71 = (u32)(first + 1) % (u32)gRandomPairModulus;
    D_8035BC74 = next_random_u32();
    D_8035BC75 = next_random_u32();
    D_8035BC76 = 0;
    D_8035BC78 = 0x80;
    D_8035BC68 = D_80074F78;
    D_8035BC6C = D_80074F78;
    guPerspective(&D_8035BC80, &D_8035BCC4, 37.0f, 4.0f / 3.0f, D_80074F7C, D_80074F80, D_80074F84);
}
