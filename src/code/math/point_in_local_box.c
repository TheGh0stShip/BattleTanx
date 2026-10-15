#include "types.h"

typedef struct LocalBox {
    u16 flags;
    s16 x;
    s16 z;
    s16 minZ;
    s16 maxZ;
    s16 minX;
    s16 maxX;
    u8 pad0E[2];
    u16 angle;
} LocalBox;

extern f32 sinf_u16(u16 angle) __asm__("func_800F3AE0");
extern f32 cosf_u16(u16 angle) __asm__("func_800F3B40");

s32 point_in_local_box(s32 x, s32 z, LocalBox *box) __asm__("func_80109498");

s32 point_in_local_box(s32 x, s32 z, LocalBox *box)
{
    f32 local[2];
    f32 dz;
    f32 dx;
    f32 sine;
    f32 cosine;

    dx = x - box->x;
    dz = z - box->z;
    if (box->flags & 1) {
        local[1] = dx;
        local[0] = dz;
    } else {
        sine = sinf_u16(box->angle);
        cosine = cosf_u16(box->angle);
        local[0] = sine * dx + cosine * dz;
        local[1] = cosine * dx + -sine * dz;
    }
    if (local[1] < box->minZ || box->maxZ < local[1] ||
        local[0] < box->minX || box->maxX < local[0]) {
        return 0;
    }
    return 1;
}
