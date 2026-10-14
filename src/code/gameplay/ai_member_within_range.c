#include "types.h"

typedef struct RangeMember RangeMember;

struct RangeMember {
    u8 pad000[0x24];
    u8 position[0x78];
    u32 state;
    u8 padA0[0x4];
    u8 targetPoint[0x8];
    RangeMember *targetMember;
    u8 padB0[0x2AE];
    u16 range;
};

#define MEMBER_STATE_FOLLOW 5
#define MEMBER_STATE_MOVE_A 6
#define MEMBER_STATE_MOVE_B 7

/* Distance used when the member has no current target. */
extern f32 D_800745D0;

extern f32 func_800E0D54(void *from, void *to);
extern f32 func_800E1A20(RangeMember *member, void *point);

s32 ai_member_within_range(RangeMember *member) __asm__("func_800E2D40");

s32 ai_member_within_range(RangeMember *member)
{
    f32 distance;

    switch (member->state) {
    case MEMBER_STATE_MOVE_A:
        distance = func_800E1A20(member, member->targetPoint);
        break;
    case MEMBER_STATE_MOVE_B:
        distance = func_800E1A20(member, member->targetPoint);
        break;
    case MEMBER_STATE_FOLLOW:
        distance = func_800E0D54(member->position, member->targetMember->position);
        break;
    default:
        distance = D_800745D0;
        break;
    }
    return distance < member->range;
}
