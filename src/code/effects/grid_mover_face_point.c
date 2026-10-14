#include "types.h"

typedef struct GridMover {
    u8 pad00[0xC];
    s32 value0C;
    s32 value10;
    u8 pad14[0x1C - 0x14];
    u8 value1C;
    u8 pad1D;
    s16 heading1E;
} GridMover;

typedef struct FloatPoint2 {
    f32 value00;
    f32 value04;
} FloatPoint2;

extern float sqrtf(float);
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern void func_8008B89C(GridMover *mover);

void grid_mover_face_point(GridMover *mover, s32 unused, FloatPoint2 *point) __asm__("func_80090A0C");

void grid_mover_face_point(GridMover *mover, s32 unused, FloatPoint2 *point) {
    f32 dy = point->value04 - (f32)mover->value0C;
    f32 dx = point->value00 - (f32)mover->value10;
    s16 heading;

    if (dy != 0.0f || dx != 0.0f) {
        mover->value1C = 1;
        if (-dy < 0.0f) {
            heading = -radians_to_angle(-dx / sqrtf(dy * dy + dx * dx));
        } else {
            heading = radians_to_angle(-dx / sqrtf(dy * dy + dx * dx));
        }
        mover->heading1E = heading;
    }
    func_8008B89C(mover);
}
