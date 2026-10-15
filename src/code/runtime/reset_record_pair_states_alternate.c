#include "types.h"

typedef struct RecordState {
    u8 pad00[0x10];
    s32 value10;
    s32 value14;
    f32 value18;
    s32 value1C;
} RecordState;

extern f32 D_80074340;
extern f32 D_80074344;
extern RecordState *D_80135810;
extern RecordState *D_80135814;

void reset_record_pair_states_alternate(void) __asm__("func_800DD860");

void reset_record_pair_states_alternate(void)
{
    RecordState *first = D_80135810;
    f32 firstValue = D_80074340;
    RecordState *second = D_80135814;
    f32 secondValue = D_80074344;
    f32 unused[2];

    first->value1C = 1;
    first->value14 = 0;
    first->value10 = 0;
    first->value18 = firstValue;
    second->value1C = 0x4D;
    second->value14 = 0;
    second->value10 = 0;
    second->value18 = secondValue;
}
