#include "types.h"

typedef struct HeadingEffect {
    u8 pad00[0xC];
    u8 flags;
    u8 pad0D[5];
    s16 anchorIndex;
    u8 pad14[0xA];
    s16 heading;
} HeadingEffect;

typedef struct HeadingAnchor {
    u8 pad00[0x48];
    f32 x;
    f32 z;
    u8 pad50[8];
} HeadingAnchor;

typedef struct HeadingSession {
    u8 pad000[0x568];
    HeadingAnchor *anchors;
} HeadingSession;

extern float sqrtf(float);
extern HeadingSession *get_spawn_session(void) __asm__("func_800821C0");
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern void release_effect(HeadingEffect *effect) __asm__("func_8008B89C");

void face_effect_away_from_anchor(HeadingEffect *effect, s32 unused, f32 *point) __asm__("func_800937BC");

void face_effect_away_from_anchor(HeadingEffect *effect, s32 unused, f32 *point) {
    HeadingAnchor *anchor;
    f32 dz;
    f32 dx;
    s16 angle;

    if (!(effect->flags & 4)) {
        effect->flags |= 3;
        anchor = &get_spawn_session()->anchors[effect->anchorIndex];
        dz = point[1] - anchor->z;
        dx = point[0] - anchor->x;
        if ((dz != 0.0f) | (dx != 0.0f)) {
            effect->flags |= 8;
            if (-dz < 0.0f) {
                angle = -radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
            } else {
                angle = radians_to_angle(-dx / sqrtf(dz * dz + dx * dx));
            }
            effect->heading = angle;
        }
        release_effect(effect);
    }
}
