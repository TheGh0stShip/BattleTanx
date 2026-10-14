#include "types.h"

typedef struct MemberStatus {
    u8 pad000[0x350];
    u8 status;
    u8 pad351[0xB9];
    u8 mode;
} MemberStatus;

extern void func_800E4344(MemberStatus *member, s32 arg1);

void reset_member_status(MemberStatus *member) __asm__("func_800E445C");

void reset_member_status(MemberStatus *member)
{
    u8 scratch[0x48];

    func_800E4344(member, 0);
    member->status = 0;
    __asm__ volatile("" : : : "memory");
    member->mode = 16;
}
