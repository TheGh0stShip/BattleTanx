#include "types.h"

typedef struct LinkRecord LinkRecord;

extern LinkRecord *get_link_record(s16 fromId, s16 toId) __asm__("func_800E52A0");
extern void clear_link_record(LinkRecord *record) __asm__("func_800E566C");

void clear_unit_link_records(s16 unitId) __asm__("func_800E4094");

void clear_unit_link_records(s16 unitId) {
    s16 other;

    for (other = 0; other < 20; other++) {
        if (unitId != other) {
            clear_link_record(get_link_record(unitId, other));
        }
    }
}
