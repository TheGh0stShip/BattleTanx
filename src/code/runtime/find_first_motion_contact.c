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

extern float sqrtf(float);
extern u8 point_hits_motion_body(s32 x, s32 z, MotionBody *body) __asm__("func_80109498");
extern u8 motion_bodies_overlap(MotionBody *a, MotionBody *b, s32 *out) __asm__("func_8010A8A8");
extern s32 D_80142B50[4];
extern s32 D_80142B60[4];
extern s16 D_803B75B0[4][20][20];
extern s16 D_803B8230;
extern s32 D_803B8238;
extern s32 D_803B823C;
extern EffectMotion D_803B8248[];

s32 find_first_motion_contact(s32 self, MotionBody *body, u16 mask, s32 *scratch, s32 *owner)
    __asm__("func_80107F14");

s32 find_first_motion_contact(s32 self, MotionBody *body, u16 mask, s32 *scratch, s32 *owner)
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
    f32 dx;
    f32 dz;
    f32 dist;
    u8 hit;

    if (self == -1) {
        return 0;
    found:
        *owner = other->owner;
        return 1;
    }
    baseX = body->x;
    baseZ = body->z;
    cellCount = 0;
    baseX += D_803B8238;
    baseZ += D_803B823C;
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
                dx = body->x - other->body.x;
                dz = body->z - other->body.z;
                dist = sqrtf(dx * dx + dz * dz);
                if (dist < (f32)(body->radius + other->body.radius)) {
                    if (other->body.flags & 0x10) {
                        hit = point_hits_motion_body(other->body.x, other->body.z, body);
                    } else {
                        hit = motion_bodies_overlap(body, &other->body, scratch);
                    }
                    if (hit) {
                        goto found;
                    }
                }
            }
            id = other->cellLinks[layer & 3];
        }
    }
    return 0;
}
