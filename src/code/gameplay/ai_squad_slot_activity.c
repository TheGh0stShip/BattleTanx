#include "types.h"

typedef struct AiSquadUnit {
    u8 pad00;
    u8 active;
    u8 pad02[0x96];
    s32 controller;
} AiSquadUnit;

extern s32 ai_get_squad_count(void) __asm__("func_8007AAB0");
extern s16 *ai_get_squad_member_ids(u16 slot) __asm__("func_800A6688");
extern AiSquadUnit *resolve_ai_member_id(s16 id) __asm__("func_800A03B8");

f32 ai_squad_slot_0_has_active_unit(void) __asm__("func_800E7FDC");
f32 ai_squad_slot_1_has_active_unit(void) __asm__("func_800E808C");
f32 ai_squad_slot_2_has_active_unit(void) __asm__("func_800E8148");

#define DEFINE_SQUAD_SLOT_ACTIVE(name, slot)       \
f32 name(void)                                     \
{                                                  \
    s16 *memberIds;                                \
    AiSquadUnit *unit;                             \
    s32 i;                                         \
    f32 active;                                    \
                                                   \
    active = 0.0f;                                 \
    if ((slot) < ai_get_squad_count()) {           \
        goto scan_members;                         \
    }                                              \
    goto done;                                     \
found_active:                                      \
    active = 1.0f;                                 \
    goto done;                                     \
scan_members:                                      \
    memberIds = ai_get_squad_member_ids(slot);     \
    i = 0;                                         \
    do {                                           \
        unit = resolve_ai_member_id(memberIds[(u16)i]); \
        if (unit->active != 0) {                   \
            if (unit->controller != 0) {           \
                goto found_active;                 \
            }                                      \
        }                                          \
        i++;                                       \
    } while ((u16)i < 5);                          \
done:                                              \
    return active;                                 \
}

#define DEFINE_NONZERO_SQUAD_SLOT_ACTIVE(name, slot) \
f32 name(void)                                       \
{                                                    \
    s16 *memberIds;                                  \
    AiSquadUnit *unit;                               \
    s32 i;                                           \
    s32 count;                                       \
    f32 active;                                      \
    register s32 threshold __asm__("$3") = (slot); \
                                                     \
    active = 0.0f;                                   \
    count = ai_get_squad_count();                    \
    threshold = (slot);                              \
    threshold = threshold < count;                   \
    if (threshold != 0) {                            \
        goto scan_members;                           \
    }                                                \
    goto done;                                       \
found_active:                                        \
    active = 1.0f;                                   \
    goto done;                                       \
scan_members:                                        \
    memberIds = ai_get_squad_member_ids(slot);       \
    i = 0;                                           \
    do {                                             \
        unit = resolve_ai_member_id(memberIds[(u16)i]); \
        if (unit->active != 0) {                     \
            if (unit->controller != 0) {             \
                goto found_active;                   \
            }                                        \
        }                                            \
        i++;                                         \
    } while ((u16)i < 5);                            \
done:                                                \
    return active;                                   \
}

DEFINE_SQUAD_SLOT_ACTIVE(ai_squad_slot_0_has_active_unit, 0)
DEFINE_NONZERO_SQUAD_SLOT_ACTIVE(ai_squad_slot_1_has_active_unit, 1)
DEFINE_NONZERO_SQUAD_SLOT_ACTIVE(ai_squad_slot_2_has_active_unit, 2)
