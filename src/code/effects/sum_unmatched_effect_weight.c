#include "types.h"

typedef struct EffectOwner {
    u8 pad00[4];
    u8 group;
} EffectOwner;

typedef struct EffectSource {
    u8 pad00[8];
    s32 value08;
    EffectOwner *owner;
} EffectSource;

typedef struct EffectRecord {
    u8 pad00[0x28];
    EffectSource *source;
    u8 pad2C[4];
    struct EffectRecord *next;
} EffectRecord;

typedef struct EffectQuery {
    u8 pad00[0x1A];
    u16 group;
} EffectQuery;

extern EffectRecord *get_effect_list_head(void) __asm__("func_800A68F0");
extern f32 D_800747D0;

f32 sum_unmatched_effect_weight(EffectQuery *query) __asm__("func_800E8934");

f32 sum_unmatched_effect_weight(EffectQuery *query) {
    EffectRecord *record;
    EffectSource *source;
    f32 total = 0.0f;

    for (record = get_effect_list_head(); record != 0; record = record->next) {
        source = record->source;
        if (source != 0 && source->value08 == 0 && source->owner->group != query->group) {
            total += D_800747D0;
        }
    }
    return total;
}
