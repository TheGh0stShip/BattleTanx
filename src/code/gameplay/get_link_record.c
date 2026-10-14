#include "types.h"

typedef struct LinkRecord {
    u8 value00[12];
} LinkRecord;

extern u8 D_8033B450[][20];
extern LinkRecord D_8033AAE8[];

LinkRecord *get_link_record(s16 fromId, s16 toId) __asm__("func_800E52A0");

LinkRecord *get_link_record(s16 fromId, s16 toId) {
    u8 slot;

    if (fromId < toId) {
        slot = D_8033B450[fromId][toId];
    } else if (toId < fromId) {
        slot = D_8033B450[toId][fromId];
    } else {
        return 0;
    }
    return &D_8033AAE8[slot];
}
