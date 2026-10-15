#include "types.h"

typedef struct EffectMatrix {
    f32 m[4][4];
    f32 pad;
} EffectMatrix;

typedef struct GfxWord {
    u32 w0;
    u32 w1;
} GfxWord;

typedef struct StreakEffect {
    u8 pad00[0xC];
    f32 x;
    f32 y;
    f32 z;
    f32 endX;
    f32 endY;
    f32 endZ;
    f32 axisB[3];
    f32 axisA[3];
    u8 age;
    u8 life;
    u8 mode;
    u8 r;
    u8 g;
    u8 b;
} StreakEffect;

extern void *get_spawn_session(void) __asm__("func_800821C0");
extern u8 func_8008488C(void *session, f32 x, f32 z, f32 scale);
extern void func_80082AA8(void *session, s16 model, f32 *matrix, s32 count, s32 arg4, s32 shade, GfxWord *color,
                          s32 arg7, void *arg8);
extern s16 D_802D5A44;
extern u8 D_80125808[];

extern EffectMatrix D_80074D68;
extern f32 D_80074DC4;
extern f64 D_80074DC8;
extern f64 D_80074DD0;
extern f32 D_80074DD8;

void draw_streak_effect(void *arg) __asm__("func_800F1708");

void draw_streak_effect(void *arg) {
    f32 scale = D_80074DC4;
    f32 stretch = scale;
    f32 xz[2];
    EffectMatrix matrix = D_80074D68;
    StreakEffect *effect = arg;
    GfxWord color;
    void *session;

    switch (effect->mode) {
    case 0:
        scale = (f32)effect->age / (f32)effect->life * D_80074DC8 + D_80074DD0;
        if (effect->age < (effect->life >> 1)) {
            return;
        }
        stretch = ((f32)effect->life - (f32)effect->age) / (f32)(effect->life >> 1);
        break;
    case 1:
        stretch = D_80074DD8;
        scale = (f32)effect->age / (f32)effect->life;
        break;
    }
    matrix.m[3][0] = effect->x;
    matrix.m[3][1] = effect->y;
    matrix.m[3][2] = effect->z;
    matrix.m[2][0] = stretch * (effect->endX - effect->x);
    matrix.m[2][1] = stretch * (effect->endY - effect->y);
    matrix.m[2][2] = stretch * (effect->endZ - effect->z);
    matrix.m[1][0] = effect->axisB[0] * scale;
    matrix.m[1][1] = effect->axisB[1] * scale;
    matrix.m[1][2] = effect->axisB[2] * scale;
    matrix.m[0][0] = effect->axisA[0] * scale;
    matrix.m[0][1] = effect->axisA[1] * scale;
    matrix.m[0][2] = effect->axisA[2] * scale;
    session = get_spawn_session();
    xz[1] = effect->x;
    xz[0] = effect->z;
    color.w0 = 0xFA000000;
    color.w1 = (effect->r << 24) | (effect->g << 16) | (effect->b << 8) | 0xFF;
    func_80082AA8(session, D_802D5A44, matrix.m[0], 3, 0, func_8008488C(session, xz[1], xz[0], 1.0f), &color, 1,
                  D_80125808);
}
