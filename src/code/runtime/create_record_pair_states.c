#include "types.h"

typedef struct RecordState {
    s32 pad00[4];
    s32 value10;
    s32 value14;
    f32 value18;
    s32 value1C;
} RecordState;

typedef struct RecordKey {
    s32 value00;
    s32 value04;
} RecordKey;

extern RecordState *create_record_state(RecordKey *key, s32 id) __asm__("func_800DD970");
extern RecordState *D_80135810;
extern RecordState *D_80135814;
extern f32 D_80074330;
extern f32 D_80074334;

void create_record_pair_states(void) __asm__("func_800DD7B0");

void create_record_pair_states(void) {
    RecordKey key;
    RecordState *second;

    key.value04 = 0;
    key.value00 = 0;
    D_80135810 = create_record_state(&key, 1);
    D_80135814 = second = create_record_state(&key, 0x4D);
    D_80135810->value18 = D_80074330;
    second->value18 = D_80074334;
}
