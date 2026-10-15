#include "types.h"

typedef struct AnimDesc {
    u8 pad00[0x18];
    s32 index;
} AnimDesc;

typedef struct AnimSource {
    u8 pad00[0x8];
    s32 kind;
    AnimDesc *desc;
} AnimSource;

typedef struct AnimOwner {
    u8 pad00[0x44];
    u16 variant;
    u8 pad46[0x2];
    u8 record[0xA4];
    AnimSource *source;
    u8 started;
} AnimOwner;

extern void set_refresh_record_value18(void *record, AnimSource *value) __asm__("func_80078634");
extern void advance_refresh_record(void *record, s32 value) __asm__("func_80078654");
extern void set_refresh_record_previous(void *record, s32 *value) __asm__("func_800786B0");
extern void set_refresh_record_value1c(void *record, s32 value) __asm__("func_800786D4");
extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern s32 D_801256C0;
extern s32 D_801256D8;
extern s32 D_80126128[2][3];
extern s32 D_80126140[2][3];

void start_owner_refresh_animation(AnimOwner *owner) __asm__("func_800A4F44");

void start_owner_refresh_animation(AnimOwner *owner)
{
    void *record = owner->record;
    AnimDesc *desc;
    s32 *table;

    if (owner->started == 0) {
        owner->started = 1;
        set_refresh_record_value18(record, owner->source);
        switch (owner->source->kind) {
        case 0:
            desc = owner->source->desc;
            if (owner->variant == 1) {
                table = D_80126140[get_difficulty_level() >= 3];
            } else {
                table = D_80126128[get_difficulty_level() >= 3];
            }
            advance_refresh_record(record, table[desc->index]);
            set_refresh_record_value1c(record, 2);
            set_refresh_record_previous(owner->record, &D_801256D8);
            break;
        case 7:
            advance_refresh_record(record, (s32)&D_801256C0);
            break;
        }
    }
}
