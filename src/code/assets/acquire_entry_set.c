#include "types.h"

typedef struct EntrySet {
    u8 count;
    u8 pad01;
    u16 first;
    u8 pad04[0x8];
} EntrySet;

typedef struct EntrySetState {
    s32 refs;
    s32 value04;
} EntrySetState;

typedef struct EntrySetBankState {
    u8 pad00[0xC];
    EntrySetState sets[450];
} EntrySetBankState;

typedef struct EntrySetBank {
    u8 pad00[0xC];
    EntrySet *sets;
    u8 pad10[0x18];
    EntrySetBankState *state;
} EntrySetBank;

extern s32 acquire_entry_range(EntrySetBank *bank, s32 group, s32 hold) __asm__("func_800874F4");

s32 acquire_entry_set(EntrySetBank *bank, s32 set, s32 hold) __asm__("func_80087634");

s32 acquire_entry_set(EntrySetBank *bank, s32 set, s32 hold)
{
    EntrySetBankState *state = bank->state;
    s32 refs;
    s32 i;

    if (set >= 450) {
        return -1;
    }
    refs = state->sets[set].refs;
    if (refs == 0) {
        state->sets[set].refs = (hold != 0) ? 2 : 1;
        for (i = 0; i < bank->sets[set].count; i++) {
            if (acquire_entry_range(bank, bank->sets[set].first + i, hold) < 0) {
                return -1;
            }
        }
        return 0;
    }
    if (hold != 0) {
        state->sets[set].refs = refs + 1;
        for (i = 0; i < bank->sets[set].count; i++) {
            if (acquire_entry_range(bank, bank->sets[set].first + i, hold) < 0) {
                return -1;
            }
        }
    }
    return 0;
}
