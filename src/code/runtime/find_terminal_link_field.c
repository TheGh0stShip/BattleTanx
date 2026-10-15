#include "types.h"

typedef struct LinkedPoolRecord {
    u8 pad00[4];
    u16 nextIndex;
    u8 pad06[0x12];
} LinkedPoolRecord;

u16 *find_terminal_link_field(LinkedPoolRecord *pool, LinkedPoolRecord *record)
    __asm__("func_800DF55C");

u16 *find_terminal_link_field(LinkedPoolRecord *pool, LinkedPoolRecord *record)
{
    u16 *link;

    while ((link = &record->nextIndex), *link != 0) {
        record = &pool[*link];
    }
    return link;
}
