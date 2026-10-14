#include "types.h"

typedef struct AiSquadMember {
    u8 pad00[0x24];
    f32 x;
    f32 y;
    f32 z;
} AiSquadMember;

extern f32 ai_horizontal_length(f32 *offset) __asm__("func_800E0BC4");

f32 ai_member_horizontal_distance(AiSquadMember *member, f32 *point) __asm__("func_800E1A20");

f32 ai_member_horizontal_distance(AiSquadMember *member, f32 *point) {
    f32 offset[2];
    f32 d;

    d = member->x - point[1];
    if (!(d > 0.0f)) {
        d = -d;
    }
    offset[1] = d;
    d = member->z - point[0];
    if (!(d > 0.0f)) {
        d = -d;
    }
    offset[0] = d;
    return ai_horizontal_length(offset);
}
