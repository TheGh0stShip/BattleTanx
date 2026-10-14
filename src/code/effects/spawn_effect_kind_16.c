#include "types.h"

typedef struct EffectMatrix16 {
    f32 m[4][4];
} EffectMatrix16;

typedef struct EffectVec16 {
    f32 x;
    f32 y;
    f32 z;
} EffectVec16;

typedef struct EffectKind16 {
    u8 pad00[0xC];
    EffectVec16 pos;
    f32 speed;
    u16 angle;
    u16 value1E;
    u16 value20;
    s16 value22;
    u8 value24;
    u8 value25;
    s8 value26;
    u8 value27;
    EffectVec16 localStart;
    EffectVec16 localEnd;
    s32 value40;
    s16 value44;
    u8 value46;
} EffectKind16;

extern EffectKind16 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern EffectMatrix16 D_80071B6C;
extern f32 D_80071BAC;
extern f32 D_80071BB0;
extern void build_render_rotation(EffectMatrix16 *target, EffectMatrix16 *matrix, u16 angle) __asm__("func_800A82B8");
extern void apply_render_matrix(EffectMatrix16 *matrix, EffectMatrix16 *target, u16 angle) __asm__("func_800A841C");
extern void matrix_transpose_3x3(EffectMatrix16 *source, EffectMatrix16 *destination) __asm__("func_800A81F0");
extern void rotate_vector_by_matrix(EffectMatrix16 *matrix, EffectVec16 *vector, EffectVec16 *out)
    __asm__("func_800A7BE8");

EffectKind16 *spawn_effect_kind_16(EffectVec16 *pos, f32 speed, u16 angle, s8 arg3, u8 arg4, u16 arg5, u8 useLocalPoints,
                                   EffectVec16 *start, EffectVec16 *end, s32 arg9, s16 arg10) __asm__("func_8008DF2C");

EffectKind16 *spawn_effect_kind_16(EffectVec16 *pos, f32 speed, u16 angle, s8 arg3, u8 arg4, u16 arg5, u8 useLocalPoints,
                                   EffectVec16 *start, EffectVec16 *end, s32 arg9, s16 arg10)
{
    EffectMatrix16 rotation;
    EffectMatrix16 inverse;
    EffectVec16 startOffset;
    EffectVec16 endOffset;
    EffectKind16 *e;

    e = allocate_effect(1, 0x16, 0x48);
    if (e == 0) {
        return 0;
    }
    e->value20 = arg5;
    e->pos.x = pos->x;
    e->pos.y = pos->y;
    e->pos.z = pos->z;
    if (arg10 != 0) {
        f32 divisor = D_80071BAC;

        if (arg10 < 0) {
            divisor = D_80071BB0;
        }
        e->speed = speed / divisor;
    } else {
        e->speed = speed;
    }
    e->value25 = arg4;
    e->angle = angle;
    e->value22 = arg10 ? 8000 : 400;
    e->value26 = arg3;
    e->value27 = 1;
    e->value24 = 1;
    e->value1E = 0;
    e->value40 = arg9;
    e->value44 = arg10;
    e->value46 = arg10 != 0;
    if (useLocalPoints) {
        rotation = D_80071B6C;
        inverse = D_80071B6C;
        build_render_rotation(&rotation, &inverse, ~(e->value1E * 3));
        apply_render_matrix(&inverse, &rotation, e->angle);
        matrix_transpose_3x3(&rotation, &inverse);
        startOffset.x = start->x - e->pos.x;
        startOffset.y = start->y - e->pos.y;
        startOffset.z = start->z - e->pos.z;
        endOffset.x = end->x - e->pos.x;
        endOffset.y = end->y - e->pos.y;
        endOffset.z = end->z - e->pos.z;
        rotate_vector_by_matrix(&inverse, &startOffset, &e->localStart);
        rotate_vector_by_matrix(&inverse, &endOffset, &e->localEnd);
    }
    return e;
}
