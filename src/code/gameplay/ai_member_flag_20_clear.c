#include "types.h"

typedef struct FlagMember {
    u8 pad00[0x14];
    u16 flags;
} FlagMember;

s32 ai_member_flag_20_clear(FlagMember *member) __asm__("func_800E262C");

s32 ai_member_flag_20_clear(FlagMember *member)
{
    return ((member->flags >> 5) ^ 1) & 1;
}
