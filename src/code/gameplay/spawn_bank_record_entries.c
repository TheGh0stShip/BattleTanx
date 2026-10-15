#include "types.h"
/* RODATA_VRAM 0x80071768 */
/* LDSYM D_801260A4=0x801260A4 */
/* LDSYM D_80134E67=0x80134E67 */
/* LDSYM D_80134E68=0x80134E68 */
/* LDSYM func_8007AAA0=0x8007AAA0 */
/* LDSYM func_8007AAB0=0x8007AAB0 */
/* LDSYM func_8007AAF4=0x8007AAF4 */
/* LDSYM func_8007C6D8=0x8007C6D8 */
/* LDSYM func_8007C728=0x8007C728 */
/* LDSYM func_80090EE0=0x80090EE0 */
/* LDSYM func_800911A0=0x800911A0 */
/* LDSYM func_800A1408=0x800A1408 */
/* LDSYM func_800A7550=0x800A7550 */
/* LDSYM func_800F38F4=0x800F38F4 */
/* LDSYM func_8010D480=0x8010D480 */
/* LDSYM func_8010DAA0=0x8010DAA0 */

typedef struct BankEntry {
    u8 flags;
    u8 pad01;
    u8 type;
    u8 pad03;
    union {
        u16 half;
        u8 bytes[2];
    } param;
    u8 pad06[0x2];
    s32 kind;
    f32 x;
    f32 z;
    u16 value14;
    u8 pad16[0x6];
} BankEntry;

typedef struct EntryList {
    u16 count;
    u16 first;
    u8 pad04[0x10];
} EntryList;

typedef struct BankRecord {
    u8 pad000[0x280];
    s32 listIndex;
    s32 spawnCounts[22];
    u8 pad2DC[0x4];
} BankRecord;

typedef struct GroupBank {
    BankRecord *records;
    EntryList *lists;
    BankEntry *entries;
} GroupBank;

typedef struct MarkerSlot {
    f32 x;
    f32 z;
    u16 value;
    u8 pad0A[0x2];
    s32 low;
    u8 param;
    u8 high;
    u8 pad12[0x6];
} MarkerSlot;

typedef struct MarkerTable {
    u8 pad000[0x370];
    s32 counts[4];
    MarkerSlot slots[4][5];
} MarkerTable;

typedef struct SpawnSpot {
    f32 z;
    f32 x;
    s32 kind;
} SpawnSpot;

typedef struct GameMode {
    u8 pad000[0x1D4];
    s32 teams[4];
} GameMode;

extern u8 D_801260A4[];
extern u8 D_80134E67;
extern u8 D_80134E68;

extern void func_80090EE0(void);
extern s32 func_8007C6D8(void);
extern s32 func_8007C728(void);
extern u32 func_800F38F4(void);
extern void spawn_effect_kind_03(f32 *pos, s32 kind, s32 arg2, s32 arg3) __asm__("func_800911A0");
extern s32 get_view_count(void) __asm__("func_8007AAA0");
extern s32 func_8007AAB0(void);
extern GameMode *get_game_mode(void) __asm__("func_8007AAF4");
extern void func_8010DAA0(f32 *pos, s32 arg1);
extern void func_800A1408(s32 team, s32 player, s32 arg2, s32 arg3, f32 *pos, f32 *pos2, s32 arg6, s32 arg7,
                          s32 arg8);
extern void func_8010D480(s32 arg0, s32 arg1, f32 x, f32 z, s32 arg4, s32 arg5);
extern void func_800A7550(f32 x, f32 z, s32 arg2);

static inline s32 pick_effect_kind(s32 kind)
{
    if (D_80134E68 != 0) {
        switch (kind) {
        case 5:
        case 6:
        case 7:
        case 9:
        case 10:
        case 13:
        case 14:
        case 16:
            switch (func_800F38F4() % 11) {
            case 0:
            case 1:
            case 2:
                return 0;
            case 3:
            case 4:
                return 3;
            case 5:
            case 6:
                return 2;
            case 7:
                return 4;
            case 8:
                return 8;
            case 9:
                return 12;
            case 10:
                return 15;
            }
            break;
        }
    }
    return kind;
}

void spawn_bank_record_entries(GroupBank *bank, s32 index, MarkerTable *markers) __asm__("func_80088670");

void spawn_bank_record_entries(GroupBank *bank, s32 index, MarkerTable *markers)
{
    f32 pos[2];
    SpawnSpot spots[100];
    f32 viewPos[2];
    f32 unitPos[2];
    BankRecord *record;
    EntryList *list;
    BankEntry *entry;
    SpawnSpot *spot;
    MarkerSlot *slot;
    s32 spotCount;
    s32 total;
    s32 i;
    s32 j;
    s32 kind;
    s32 n;
    s32 player;
    s32 team;
    s32 side;
    s32 flag;
    s32 group;
    s32 low;
    s32 param;
    s32 high;

    spotCount = 0;
    total = 0;
    func_80090EE0();
    for (i = 0; i < 100; i++) {
        spots[i].kind = 23;
    }
    record = &bank->records[index];
    if (record->listIndex < 0) {
        return;
    }
    list = &bank->lists[record->listIndex];
    for (i = 0; i < list->count; i++) {
        entry = &bank->entries[list->first + i];
        if ((entry->flags & 0x10) && func_8007C6D8() == 0) {
            continue;
        }
        if ((entry->flags & 0x40) && func_8007C6D8() != 0) {
            continue;
        }
        switch (entry->kind) {
        case 25:
            group = entry->type >> 4;
            low = entry->type & 0xF;
            param = entry->param.half & 0xFF;
            high = (s16)entry->param.half >> 12;
            n = markers->counts[group];
            if (n != 5) {
                markers->counts[group] = n + 1;
                slot = &markers->slots[group][n];
                slot->x = entry->x;
                slot->z = entry->z;
                slot->value = entry->value14;
                slot->low = low;
                slot->param = param;
                slot->high = high & 3;
            }
            break;
        case 10:
            if (!((entry->flags & 0x10) && func_8007C6D8() != 0)) {
                if ((entry->flags & 0x10) || func_8007C6D8() != 0) {
                    break;
                }
            }
            if (entry->type == 22) {
                if (spotCount < 100) {
                    spots[spotCount].x = entry->x;
                    spots[spotCount].z = entry->z;
                    spotCount++;
                }
                break;
            }
            pos[1] = entry->x;
            pos[0] = entry->z;
            kind = entry->type;
            spawn_effect_kind_03(pos, pick_effect_kind(kind), 0, -1);
            break;
        case 23:
            if (get_view_count() == 1) {
                viewPos[1] = entry->x;
                viewPos[0] = entry->z;
                func_8010DAA0(viewPos, -1);
            }
            break;
        case 22:
            if (entry->param.half & 1) {
                if (func_8007C728() == 0) {
                    break;
                }
                if (D_80134E67 == 0) {
                    break;
                }
            }
            player = D_801260A4[(entry->param.half >> 1) & 3];
            if (player >= func_8007AAB0()) {
                break;
            }
            unitPos[1] = entry->x;
            unitPos[0] = entry->z;
            team = get_game_mode()->teams[player];
            side = (entry->param.half >> 3) & 3;
            flag = (func_8007C6D8() != 0) ? 0 : (entry->param.bytes[1] & 1);
            func_800A1408(team & 0xFF, player, side, entry->value14, unitPos, unitPos, 0, flag, 0);
            break;
        case 21:
            if (get_view_count() == 1) {
                func_8010D480(0, entry->param.half, entry->x, entry->z, entry->value14, entry->type);
            }
            break;
        case 24:
            if (get_view_count() == 1) {
                func_800A7550(entry->x, entry->z, (s16)entry->param.half);
            }
            break;
        }
    }
    if (func_8007C6D8() != 0) {
        return;
    }
    for (i = 0; i < 22; i++) {
        total += record->spawnCounts[i];
    }
    if (spotCount < total) {
        return;
    }
    for (i = 0; i < 22; i++) {
        for (j = 0; j < record->spawnCounts[i]; j++) {
        retry:
            spot = &spots[func_800F38F4() % spotCount];
            if (spot->kind != 23) {
                goto retry;
            }
            pos[1] = spot->x;
            pos[0] = spot->z;
            spot->kind = i;
            spawn_effect_kind_03(pos, pick_effect_kind(i), 0, -1);
        }
    }
}
