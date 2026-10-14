#include "types.h"

typedef struct GroupRange {
    u8 count;
    u8 pad01;
    u16 first;
} GroupRange;

typedef struct GroupState {
    s32 loaded;
    s32 value04;
} GroupState;

typedef struct BankState {
    u8 pad00[0xE20];
    GroupState groups[64];
} BankState;

typedef struct GroupBank {
    u8 pad00[0x10];
    GroupRange *ranges;
    u8 pad14[0x14];
    BankState *state;
} GroupBank;

extern s32 load_bank_entry(GroupBank *bank, s32 index, s32 arg2) __asm__("func_80087634");

s32 load_entry_group_once(GroupBank *bank, s32 group) __asm__("func_80087798");

s32 load_entry_group_once(GroupBank *bank, s32 group) {
    BankState *state = bank->state;
    s32 i;

    if (group >= 64) {
        return -1;
    }
    if (state->groups[group].loaded != 0) {
        return 0;
    }
    state->groups[group].loaded = 1;
    for (i = 0; i < bank->ranges[group].count; i++) {
        if (load_bank_entry(bank, bank->ranges[group].first + i, 0) < 0) {
            return -1;
        }
    }
    return 0;
}
