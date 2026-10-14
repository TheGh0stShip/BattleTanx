#include "types.h"

typedef struct SessionRecord {
    u32 words[17];
} SessionRecord;

extern u8 D_803283B8[];
extern u8 D_803282A0[];
extern SessionRecord D_803282A8[];
extern u8 callback_return_zero(void) __asm__("func_80096760");
extern SessionRecord *get_entity_record_68(s32 index) __asm__("func_80096768");

void copy_four_session_records(void) __asm__("func_800D4410");

void copy_four_session_records(void) {
    s32 i = 0;
    u8 *id = D_803283B8;
    SessionRecord *record = D_803282A8;

    do {
        D_803282A0[i] = *id = callback_return_zero();
        *record = *get_entity_record_68(*id);
        id++;
        i++;
        record++;
    } while (i < 4);
}
