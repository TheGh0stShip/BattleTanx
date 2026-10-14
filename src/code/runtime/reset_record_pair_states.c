#include "types.h"

typedef struct RecordState {
    s32 pad00[4];
    s32 value10;
    s32 value14;
    f32 value18;
    s32 value1C;
} RecordState;

extern RecordState *D_80135810;
extern RecordState *D_80135814;
extern f32 D_80074338;
extern f32 D_8007433C;

void reset_record_pair_states(void) __asm__("func_800DD814");

void reset_record_pair_states(void) {
    D_80135810->value1C = 1;
    D_80135810->value14 = 0;
    D_80135810->value10 = 0;
    D_80135810->value18 = D_80074338;
    D_80135814->value1C = 0x4D;
    D_80135814->value14 = 0;
    D_80135814->value10 = 0;
    D_80135814->value18 = D_8007433C;
}
