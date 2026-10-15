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


typedef struct MotionHit {
    s32 owner;
    s32 value04;
} MotionHit;

extern float sqrtf(float);
extern s32 D_80142B50[4];
extern s32 D_80142B60[4];
extern s16 D_803B75B0[4][20][20];
extern s16 D_803B8230;
extern s32 D_803B8238;
extern s32 D_803B823C;
extern EffectMotion D_803B8248[];

u8 find_motions_near_point(s32 x, s32 z, s32 range, u16 mask, MotionHit *hits, s32 *count) __asm__("func_8010823C");

u8 find_motions_near_point(s32 x, s32 z, s32 range, u16 mask, MotionHit *hits, s32 *count) {
    s32 n = 0;
    u8 anyHit = 0;
    s32 i;
    s32 j;
    s32 row;
    s32 col;
    s32 baseX;
    s32 baseZ;
    MotionHit *first;
    s16 id;
    f32 dx;
    f32 dz;
    u8 found;
    MotionHit *search;

    first = hits;
    baseX = x + D_803B8238;
    baseZ = z + D_803B823C;
    for (i = 0; i < 5; i++) {
        if (i < 4) {
            row = (baseX + D_80142B50[i]) >> 11;
            col = (baseZ + D_80142B60[i]) >> 11;
            if ((row >= 20) | (col >= 20)) {
                continue;
            }
            if ((row < 0) | (col < 0)) {
                continue;
            }
            id = D_803B75B0[i][row][col];
        } else {
            id = D_803B8230;
        }
        while (id != -1) {
            dx = x - D_803B8248[id].body.x;
            dz = z - D_803B8248[id].body.z;
            if (mask & D_803B8248[id].mode) {
                if (sqrtf(dx * dx + dz * dz) < (f32)(range + D_803B8248[id].body.radius)) {
                    anyHit = 1;
                    found = 0;
                    search = first;
                    if (D_803B8248[id].owner != 0) {
                        for (j = 0; j < n; j++) {
                            if (search->owner == D_803B8248[id].owner) {
                                found = 1;
                                break;
                            }
                            search++;
                        }
                    }
                    if (!found) {
                        hits->owner = D_803B8248[id].owner;
                        n++;
                        hits++;
                    }
                    if (n >= 32) {
                        break;
                    }
                }
            }
            id = D_803B8248[id].cellLinks[i & 3];
        }
    }
    *count = n;
    return anyHit;
}
