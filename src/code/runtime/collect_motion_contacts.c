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

typedef struct MotionContact {
    s32 owner;
    s32 value04;
    u8 pad08[4];
    s32 value0C;
    u8 pad10[8];
} MotionContact;

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

u8 collect_motion_contacts(s32 self, MotionContact *contacts, s32 *count) __asm__("func_80107B44");

u8 collect_motion_contacts(s32 self, MotionContact *contacts, s32 *count) {
    GridCells cells;
    s32 scratch[1];
    MotionContact *out = contacts;
    s32 baseX;
    s32 baseZ;
    MotionContact *search;
    EffectMotion *me;
    EffectMotion *other;
    s32 n;
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
    u8 found;
    u8 anyHit;
    MotionContact *first;

    if (self == -1) {
        return 0;
    }
    n = 0;
    anyHit = 0;
    baseX = D_803B8248[self].body.x;
    baseZ = D_803B8248[self].body.z;
    me = &D_803B8248[self];
    cellCount = 0;
    first = contacts;
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
            if (!(other->mode & 0x20) && id != self) {
                dx = me->body.x - other->body.x;
                dz = me->body.z - other->body.z;
                dist = sqrtf(dx * dx + dz * dz);
                if (dist < (f32)(me->body.radius + other->body.radius)) {
                    if (other->body.flags & 0x10) {
                        hit = point_hits_motion_body(other->body.x, other->body.z, &me->body);
                    } else {
                        hit = motion_bodies_overlap(&me->body, &other->body, scratch);
                    }
                    if (hit) {
                        anyHit = 1;
                        search = first;
                        found = 0;
                        if (other->owner != 0) {
                            for (j = 0; j < n; j++) {
                                if (search->owner == other->owner) {
                                    found = 1;
                                    break;
                                }
                                search++;
                            }
                        }
                        if (!found) {
                            n++;
                            out->owner = other->owner;
                            out->value04 = 0;
                            out->value0C = 0;
                            out++;
                        }
                        if (n >= 16) {
                            break;
                        }
                    }
                }
            }
            id = other->cellLinks[layer & 3];
        }
    }
    *count = n;
    return anyHit;
}
