#include "types.h"

typedef struct Point2f {
    f32 value00;
    f32 value04;
} Point2f;

typedef struct EffectKind30 {
    u8 pad00[0xC];
    s32 value0C;
    s32 value10;
    Point2f value14;
    Point2f value1C;
    Point2f value24;
    s32 value2C;
    u16 value30;
    u8 value32;
} EffectKind30;

extern EffectKind30 *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");

void spawn_effect_kind_30(Point2f *a, Point2f *b, Point2f *c, s32 param, u16 value30, u8 value32) __asm__("func_8010DED4");

void spawn_effect_kind_30(Point2f *a, Point2f *b, Point2f *c, s32 param, u16 value30, u8 value32) {
    EffectKind30 *e = allocate_effect(1, 0x1E, 0x34);

    if (e != 0) {
        e->value14.value04 = a->value04;
        e->value14.value00 = a->value00;
        e->value1C.value04 = b->value04;
        e->value1C.value00 = b->value00;
        e->value24.value04 = c->value04;
        e->value24.value00 = c->value00;
        e->value2C = param;
        e->value10 = 0;
        e->value0C = 0;
        e->value30 = value30;
        e->value32 = value32;
    }
}
