#include "types.h"

typedef struct MotionBody {
    u16 flags;
    s16 x;
    s16 z;
    u8 pad06[8];
    s16 radius;
} MotionBody;

typedef struct EffectMotion {
    u16 mode;
    s16 next;
    s16 prev;
    u8 pad06[2];
    s32 owner;
    MotionBody body;
    u8 pad1C[2];
    s16 cellLinks[4];
    u8 pad26[2];
} EffectMotion;

typedef struct GridCells {
    s32 row[4];
    s32 col[4];
    s32 layer[4];
} GridCells;

extern u8 sweep_oriented_box_against_box(MotionBody *body, f32 *delta, MotionBody *other, s32 arg3, s32 arg4)
    __asm__("func_8010B9C8");
extern s32 D_80142B50[4];
extern s32 D_80142B60[4];
extern s16 D_803B75B0[4][20][20];
extern s16 D_803B8230;
extern s32 D_803B8238;
extern s32 D_803B823C;
extern EffectMotion D_803B8248[];

u8 sweep_motion_body(MotionBody *body, s32 self, u16 mask, f32 *delta, f32 *out, s32 arg5, s32 arg6,
                     s32 *owner) __asm__("func_80108B68");

u8 sweep_motion_body(MotionBody *body, s32 self, u16 mask, f32 *delta, f32 *out, s32 arg5, s32 arg6,
                     s32 *owner)
{
    GridCells cells;
    s32 baseX;
    s32 baseZ;
    EffectMotion *other;
    s32 cellCount;
    s32 i;
    s32 j;
    s32 row;
    s32 col;
    s32 layer;
    s16 id;
    u8 hit;

    hit = 0;
    cellCount = 0;
    *owner = 0;
    baseX = body->x + D_803B8238;
    baseZ = body->z + D_803B823C;
    for (i = 0; i < 4; i++) {
        row = (baseX + D_80142B50[i]) >> 11;
        col = (baseZ + D_80142B60[i]) >> 11;
        if (((row >= 20) | (col >= 20)) == 0 && ((row < 0) | (col < 0)) == 0) {
            for (j = 0; j < i; j++) {
                if (row == cells.row[j] && col == cells.col[j]) {
                    break;
                }
            }
            cells.layer[cellCount] = i;
            cells.row[cellCount] = row;
            cells.col[cellCount] = col;
            cellCount++;
        }
    }
    for (i = 0; i < cellCount + 1; i++) {
        if (i < cellCount) {
            layer = cells.layer[i];
            row = cells.row[i];
            col = cells.col[i];
            id = D_803B75B0[layer][row][col];
        } else {
            id = D_803B8230;
            layer = 0;
        }
        while (id != -1) {
            other = &D_803B8248[id];
            if ((other->mode & mask) && id != self) {
                if (sweep_oriented_box_against_box(body, delta, &other->body, arg5, arg6)) {
                    *owner = other->owner;
                    hit = 1;
                }
            }
            id = other->cellLinks[layer & 3];
        }
    }
    if (hit) {
        out[1] = body->x;
        out[0] = body->z;
    } else {
        out[1] = body->x + delta[1];
        out[0] = body->z + delta[0];
    }
    return hit;
}
