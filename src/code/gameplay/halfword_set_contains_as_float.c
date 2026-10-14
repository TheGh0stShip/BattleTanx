#include "types.h"

typedef struct HalfwordIdSet {
    u16 ids[3];
    u16 count;
} HalfwordIdSet;

extern f32 D_8007476C; /* 1.0f */

f32 halfword_set_contains_as_float(HalfwordIdSet **setp, u16 id) __asm__("func_800E82C0");

f32 halfword_set_contains_as_float(HalfwordIdSet **setp, u16 id) {
    HalfwordIdSet *set = *setp;
    u16 i;

    for (i = 0; i < set->count; i++) {
        if (id == set->ids[i]) {
            return D_8007476C;
        }
    }
    return 0.0f;
}
