#include "types.h"

typedef struct EntityPoolRecord {
    u8 first;
    u8 second;
    u8 pad002[0x506];
} EntityPoolRecord;

extern EntityPoolRecord D_802D8180[];

void clear_entity_pool_markers(void) __asm__("func_800A0380");

void clear_entity_pool_markers(void)
{
    s32 i;

    for (i = 0; i < 20; i++) {
        D_802D8180[i].first = 0;
        D_802D8180[i].second = 0;
    }
}
