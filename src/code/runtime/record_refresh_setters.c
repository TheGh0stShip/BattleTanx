#include "types.h"

typedef struct RefreshRecord {
    u8 pad00[0xC];
    s32 current;
    s32 previous;
    u8 mode;
    u8 pad15[0x3];
    s32 value18;
    s32 value1C;
} RefreshRecord;

extern void refresh_record(RefreshRecord *record) __asm__("func_80077E94");

void set_refresh_record_value18(RefreshRecord *record, s32 value) __asm__("func_80078634");
void advance_refresh_record(RefreshRecord *record, s32 value) __asm__("func_80078654");
void advance_refresh_record_mode_64(RefreshRecord *record, s32 value) __asm__("func_80078680");
void set_refresh_record_previous(RefreshRecord *record, s32 value) __asm__("func_800786B0");
void set_refresh_record_value1c(RefreshRecord *record, s32 value) __asm__("func_800786D4");

void set_refresh_record_value18(RefreshRecord *record, s32 value) { record->value18 = value; refresh_record(record); }
void advance_refresh_record(RefreshRecord *record, s32 value) { record->previous = record->current; record->current = value; record->mode = 0; refresh_record(record); }
void advance_refresh_record_mode_64(RefreshRecord *record, s32 value) { record->previous = record->current; record->current = value; record->mode = 0x40; refresh_record(record); }
void set_refresh_record_previous(RefreshRecord *record, s32 value) { record->previous = value; record->mode = 0; refresh_record(record); }
void set_refresh_record_value1c(RefreshRecord *record, s32 value) { record->value1C = value; refresh_record(record); }
