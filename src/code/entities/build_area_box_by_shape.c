#include "types.h"

typedef struct AreaBox AreaBox;

extern void func_80109268(AreaBox *box, s32 x, s32 y, s32 minA, s32 maxA, s32 minB, s32 maxB, s32 flags);
extern f32 D_80072120;
extern f32 D_80072124;
extern f32 D_80072128;
extern f32 D_8007212C;
extern f32 D_80072130;
extern f32 D_80072134;
extern f32 D_80072138;
extern f32 D_8007213C;
extern f32 D_80072140;
extern f32 D_80072144;
extern f32 D_80072148;

void build_area_box_by_shape(f32 x, f32 y, u16 flags, u32 shape, AreaBox *box, f32 scale) __asm__("func_80096E80");

void build_area_box_by_shape(f32 x, f32 y, u16 flags, u32 shape, AreaBox *box, f32 scale)
{
    switch (shape) {
    case 0:
        func_80109268(box, x, y, scale * D_8007212C, scale * D_80072120, scale * D_80072124, scale * D_80072128, flags);
        break;
    case 1:
        func_80109268(box, x, y, scale * D_80072130, scale * D_80072138, scale * D_80072134, scale * D_80072138, flags);
        break;
    case 2:
        func_80109268(box, x, y, scale * D_80072148, scale * D_8007213C, scale * D_80072140, scale * D_80072144, flags);
        break;
    }
}
