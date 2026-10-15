#include "types.h"

typedef struct EntryRange {
    u8 count;
    u8 pad01;
    u16 first;
} EntryRange;

typedef struct EntryGroupState {
    s32 refs;
    s32 value04;
} EntryGroupState;

typedef struct EntryBankState {
    u8 pad00[0x1028];
    EntryGroupState groups[600];
} EntryBankState;

typedef struct EntryBank {
    u8 pad00[0x14];
    EntryRange *ranges;
    u8 pad18[0x10];
    EntryBankState *state;
} EntryBank;

extern s32 load_entry_bank_item(EntryBank *bank, s32 index, s32 hold) __asm__("func_8008716C");

s32 acquire_entry_range(EntryBank *bank, s32 group, s32 hold) __asm__("func_800874F4");

s32 acquire_entry_range(EntryBank *bank, s32 group, s32 hold)
{
    EntryBankState *state = bank->state;
    s32 refs;
    s32 i;

    if (group >= 600) {
        return -1;
    }
    refs = state->groups[group].refs;
    if (refs == 0) {
        state->groups[group].refs = (hold != 0) ? 2 : 1;
        for (i = 0; i < bank->ranges[group].count; i++) {
            if (load_entry_bank_item(bank, bank->ranges[group].first + i, hold) < 0) {
                return -1;
            }
        }
        return 0;
    }
    if (hold != 0) {
        state->groups[group].refs = refs + 1;
        for (i = 0; i < bank->ranges[group].count; i++) {
            if (load_entry_bank_item(bank, bank->ranges[group].first + i, hold) < 0) {
                return -1;
            }
        }
    }
    return 0;
}
