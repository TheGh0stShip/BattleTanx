#include "types.h"

typedef struct ObjectRecordTable {
    u8 pad00[0x18];
    u8 *kinds;
    u8 *enabled;
} ObjectRecordTable;

extern ObjectRecordTable *gObjectRecordTable __asm__("D_80135834");
extern s32 game_mode_is_3_through_6(void) __asm__("func_8007C6D8");

s32 classify_object_record_kind(u16 id) __asm__("func_800DF214");

s32 classify_object_record_kind(u16 id) {
    s32 kind = gObjectRecordTable->kinds[id];

    if (gObjectRecordTable->enabled[kind] == 0) {
        return 0;
    }
    if (kind >= 15) {
        return 1;
    }
    switch (kind) {
    case 0:
        return 0;
    case 5:
        return 1;
    case 13:
        return game_mode_is_3_through_6() != 0;
    case 6:
        return 2;
    case 14:
        return (game_mode_is_3_through_6() != 0) << 1;
    case 4:
        return 3;
    case 12:
        return game_mode_is_3_through_6() ? 3 : 0;
    }
    return 4;
}
