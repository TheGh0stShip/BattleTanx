#include "types.h"

typedef struct AnimDesc {
    u8 pad00[0x18];
    s32 index;
    u8 pad1C[0x8];
    f32 x;
    u8 pad28[0x4];
    f32 z;
    u8 pad30[0x3CC];
    f32 heading;
} AnimDesc;

typedef struct AnimSource {
    u8 pad00[0x8];
    s32 kind;
    union {
        AnimDesc *desc;
        u8 flag;
    } value0C;
} AnimSource;

typedef struct AnimOwner {
    u8 pad00[0x17];
    u8 value17;
    u8 pad18[0x2C];
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
extern AnimSource *spawn_effect_kind_07(f32 value14, f32 value10, u16 value0E, u8 variant, u8 value18)
    __asm__("func_80078834");
extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern s32 D_801256C0;
extern s32 D_801256D8;
extern s32 D_80126128[2][3];
extern s32 D_80126140[2][3];

void respawn_owner_refresh_animation(AnimOwner *owner) __asm__("func_800A5050");

void respawn_owner_refresh_animation(AnimOwner *owner)
{
    AnimSource *source = owner->source;
    AnimDesc *target;
    AnimSource *spawned;
    AnimDesc *desc;
    void *record;
    s32 *table;

    switch (source->kind) {
    case 7:
        source->value0C.flag = 0;
        break;
    case 0:
        target = source->value0C.desc;
        spawned = spawn_effect_kind_07(target->x, target->z, (u32)(target->heading * 182.04445f), 0, owner->value17);
        if (spawned == 0) {
            break;
        }
        owner->source = spawned;
        if (owner->started == 0) {
            break;
        }
        record = owner->record;
        set_refresh_record_value18(record, spawned);
        switch (owner->source->kind) {
        case 0:
            desc = owner->source->value0C.desc;
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
        break;
    }
}
