#include "types.h"

typedef struct RefSlot {
    s32 index;
    s32 refs;
} RefSlot;

typedef struct BlockSlot {
    s32 pad00;
    s32 size;
    s32 offset;
    s32 copies;
} BlockSlot;

typedef struct BankState {
    s32 setCount;
    s32 setRefs;
    RefSlot sets[450];
    s32 groupCount;
    RefSlot groups[64];
    s32 rangeCount;
    s32 rangeRefs;
    RefSlot ranges[600];
    s32 itemCount;
    s32 itemRefs;
    RefSlot items[3600];
    s32 blockCount;
    BlockSlot blocks[256];
    s32 blockBytes;
    s32 bufferCount;
    BlockSlot buffers[1800];
    s32 bufferBytes;
    s32 totalBytes;
    s32 summarySets;
    s32 summaryRanges;
    s32 summaryItems;
    s32 summaryBuffers;
} BankState;

typedef struct GroupRange {
    u8 count;
    u8 pad01;
    u16 first;
} GroupRange;

typedef struct EntryList {
    u16 count;
    u16 first;
    u8 pad04[0x10];
} EntryList;

typedef struct BankEntry {
    u8 flags;
    u8 pad01[0x15];
    s16 group;
    s16 set;
    u8 pad1A[0x2];
} BankEntry;

typedef struct BankRecord {
    u8 pad000[0x27C];
    s32 listCount;
    s32 listOffset;
    u8 pad284[0x58];
    s32 setBase;
} BankRecord;

typedef struct GroupBank {
    BankRecord *records;
    EntryList *lists;
    BankEntry *entries;
    u8 pad0C[0x4];
    GroupRange *ranges;
    u8 pad14[0x14];
    BankState *state;
} GroupBank;

extern s16 D_802D5A30[182];

extern s32 load_bank_entry(GroupBank *bank, s32 index, s32 arg2) __asm__("func_80087634");

static inline s32 load_entry_group_once(GroupBank *bank, s32 group)
{
    BankState *state = bank->state;
    s32 i;

    if (group >= 64) {
        return -1;
    }
    if (state->groups[group].refs == 0) {
    state->groups[group].refs = 1;
    for (i = 0; i < bank->ranges[group].count; i++) {
        if (load_bank_entry(bank, bank->ranges[group].first + i, 0) < 0) {
            return -1;
        }
    }
    }
    return 0;
}

s32 plan_bank_record_resources(GroupBank *bank, s32 index) __asm__("func_8008785C");

s32 plan_bank_record_resources(GroupBank *bank, s32 index)
{
    BankState *state;
    s32 k;
    s32 total;
    s32 i;
    BankRecord *record;
    s32 bytes;
    BankEntry *entry;
    EntryList *list;
    s32 j;

    total = 0;
    record = &bank->records[index];
    state = bank->state;
    for (i = 0; i < record->listCount; i++) {
        list = &bank->lists[(record->listOffset != -1) ? i + 1 : i];
        for (j = 0; j < list->count; j++) {
            entry = &bank->entries[list->first + j];
            total++;
            if (entry->group != -1) {
                if (load_entry_group_once(bank, entry->group) < 0) {
                    return -1;
                }
            }
            if (entry->set != -1) {
                if (load_bank_entry(bank, entry->set, entry->flags & 1) < 0) {
                    return -1;
                }
            }
        }
    }
    for (k = 0; k < 182; k++) {
        if (D_802D5A30[k] != -1) {
            load_bank_entry(bank, k + record->setBase, 0);
        }
    }
    for (k = 0; k < 450; k++) {
        if (state->sets[k].refs != 0) {
            state->sets[k].index = state->setCount++;
            state->setRefs += state->sets[k].refs;
        }
    }
    for (k = 0; k < 64; k++) {
        if (state->groups[k].refs != 0) {
            state->groups[k].index = state->groupCount++;
        }
    }
    for (k = 0; k < 600; k++) {
        if (state->ranges[k].refs != 0) {
            state->ranges[k].index = state->rangeCount++;
            state->rangeRefs += state->ranges[k].refs;
        }
    }
    for (k = 0; k < 3600; k++) {
        if (state->items[k].refs != 0) {
            state->items[k].index = state->itemCount++;
            state->itemRefs += state->items[k].refs;
        }
    }
    bytes = 0;
    for (k = 0; k < state->blockCount; k++) {
        state->blocks[k].offset = bytes;
        bytes += state->blocks[k].size;
        bytes = (bytes + 7) & ~7;
    }
    state->blockBytes = bytes;
    bytes = 0;
    for (k = 0; k < state->bufferCount; k++) {
        state->buffers[k].offset = bytes;
        bytes += state->buffers[k].size;
        bytes = (bytes + 7) & ~7;
    }
    state->bufferBytes = bytes;
    for (k = 0; k < state->bufferCount; k++) {
        if (state->buffers[k].copies >= 2) {
            bytes += ((state->buffers[k].size + 7) & ~7) * (state->buffers[k].copies - 1);
        }
    }
    state->totalBytes = bytes;
    state->summarySets = state->setCount;
    state->summaryRanges = state->rangeCount;
    state->summaryItems = state->itemCount;
    state->summaryBuffers = state->bufferBytes;
    return total;
}
