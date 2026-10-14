#include "types.h"

typedef struct AreaBoxDef {
    s16 value00;
    s16 value02;
    s16 value04;
    s16 value06;
    s16 value08;
    s16 value0A;
    s16 value0C;
    s16 value0E;
    u16 value10;
    u8 pad12[0x16];
} AreaBoxDef;

typedef struct AreaCorner {
    f32 x;
    f32 y;
} AreaCorner;

extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern AreaBoxDef D_803B8254[];

void area_box_corners(s32 index, AreaCorner *out) __asm__("func_80108E74");

void area_box_corners(s32 index, AreaCorner *out) {
    AreaBoxDef *area = &D_803B8254[index];
    f32 s = -angle_sin(area->value10);
    f32 c = angle_cos(area->value10);

    out[0].y = ((c * (f32)area->value06) - (s * (f32)area->value0A)) + (f32)area->value02;
    out[0].x = (s * (f32)area->value06) + (c * (f32)area->value0A) + (f32)area->value04;
    out[1].y = ((c * (f32)area->value08) - (s * (f32)area->value0A)) + (f32)area->value02;
    out[1].x = (s * (f32)area->value08) + (c * (f32)area->value0A) + (f32)area->value04;
    out[2].y = ((c * (f32)area->value08) - (s * (f32)area->value0C)) + (f32)area->value02;
    out[2].x = (s * (f32)area->value08) + (c * (f32)area->value0C) + (f32)area->value04;
    out[3].y = ((c * (f32)area->value06) - (s * (f32)area->value0C)) + (f32)area->value02;
    out[3].x = (s * (f32)area->value06) + (c * (f32)area->value0C) + (f32)area->value04;
}
