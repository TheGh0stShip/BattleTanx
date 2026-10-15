#include "types.h"

typedef struct RefreshSource {
    u8 pad00[0x18];
    s32 value18;
} RefreshSource;

typedef struct RefreshEvent {
    u8 pad00[0x8];
    s32 kind;
    RefreshSource *source;
} RefreshEvent;

typedef struct RefreshOwner {
    u8 pad00[0x44];
    u16 value44;
    u8 pad46[0x2];
    u8 record[0xA4];
    RefreshEvent *event;
    u8 enabled;
} RefreshOwner;

extern void refresh_record_begin(void *record) __asm__("func_80078634");
extern void advance_refresh_record(void *record, void *value) __asm__("func_80078654");
extern void refresh_record_set_target(void *record, void *value) __asm__("func_800786B0");
extern void set_refresh_record_value1c(void *record, s32 value) __asm__("func_800786D4");
extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void *D_80126128[];
extern void *D_80126140[];
extern u8 D_801256C0[];
extern u8 D_801256D8[];

void refresh_owner_handle_event(RefreshOwner *owner, RefreshEvent *event)
    __asm__("func_800A4E40");

void refresh_owner_handle_event(RefreshOwner *owner, RefreshEvent *event)
{
    void *record;
    RefreshSource *source;
    void **table;
    s32 low;

    owner->event = event;
    if (owner->enabled == 0) {
        return;
    }
    record = owner->record;
    refresh_record_begin(record);
    switch (owner->event->kind) {
    case 0:
        source = owner->event->source;
        if (owner->value44 == 1) {
            low = get_difficulty_level() < 3;
            table = D_80126140;
        } else {
            low = get_difficulty_level() < 3;
            table = D_80126128;
        }
        if (!low) {
            table += 3;
        }
        advance_refresh_record(record, table[source->value18]);
        set_refresh_record_value1c(record, 2);
        refresh_record_set_target(owner->record, D_801256D8);
        break;
    case 7:
        advance_refresh_record(record, D_801256C0);
        break;
    }
}
