#include "types.h"

typedef struct SessionRecord {
    s32 words[0x11];
} SessionRecord;

typedef struct SessionState {
    s32 value00;
    s32 value04;
    s8 value08;
    u8 pad09[0x3];
    s32 value0C;
    s32 value10;
    s16 value14;
    s8 value16;
    u8 pad17[0x2];
    s8 value19;
    u8 pad1A[0xA];
    SessionRecord record;
} SessionState;

extern SessionState *D_80134E78;

extern SessionRecord *get_entity_record_68(s32 index) __asm__("func_80096768");

void reset_session_state_defaults(void) __asm__("func_800D05DC");

void reset_session_state_defaults(void)
{
    SessionState *state;

    D_80134E78->value00 = 0x42A;
    D_80134E78->value04 = 0x42A;
    D_80134E78->value08 = 1;
    D_80134E78->value0C = 0;
    D_80134E78->value14 = 0;
    D_80134E78->value16 = 0;
    D_80134E78->value10 = 9;
    D_80134E78->value19 = 0;
    state = D_80134E78;
    state->record = *get_entity_record_68(0);
}
