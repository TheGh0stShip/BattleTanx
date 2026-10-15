#include "types.h"

typedef struct OffsetPair {
    f32 y;
    f32 x;
} OffsetPair;

typedef struct SlotEffect SlotEffect;

typedef struct EffectGroup {
    u8 pad00[0x10];
    SlotEffect *head;
} EffectGroup;

struct SlotEffect {
    u8 pad00[0xC];
    u8 ownerId;
    u8 pad0D[3];
    s32 state;
    u8 groupId;
    u8 pad15[3];
    s32 motion;
    f32 y;
    f32 x;
    u8 pad24[4];
    EffectGroup *group;
    SlotEffect *next;
};

typedef struct EffectOwner {
    u8 pad000[0x1AE];
    u8 team;
    u8 pad1AF;
    f32 y;
    f32 x;
    EffectGroup *group;
} EffectOwner;

extern OffsetPair D_801266D0[];
extern u8 D_801266F0;
extern void func_80107170(s32 resource);
extern s32 create_effect_motion(SlotEffect *owner, s32 x, s32 y, s32 minX, s32 maxX, s32 minY,
                                s32 maxY, s32 mode, s32 flags) __asm__("func_80106D18");
extern EffectOwner *get_entity_record(u16 index) __asm__("func_800A6688");
extern void increment_effect_owner_count(s32 owner) __asm__("func_800A6864");
extern void add_entity_progress(EffectOwner *entity, s32 amount) __asm__("func_800A59E8");
extern void start_cooldown_timed_event(EffectOwner *owner, s32 event, f32 duration) __asm__("func_800A51E8");

void attach_effect_to_owner_group(SlotEffect *effect, s32 ownerId) __asm__("func_800A6E30");

void attach_effect_to_owner_group(SlotEffect *effect, s32 ownerId)
{
    EffectOwner *owner;
    EffectGroup *group;
    SlotEffect *it;
    s32 slot;

    effect->state = 0;
    effect->groupId = ownerId;
    effect->next = 0;
    if (effect->motion != -1) {
        func_80107170(effect->motion);
        effect->motion = -1;
    }
    owner = get_entity_record(ownerId);
    group = owner->group;
    slot = 0;
    for (it = group->head; it != 0; it = it->next) {
        slot++;
    }
    effect->motion = create_effect_motion(effect, owner->x + D_801266D0[slot].x, owner->y + D_801266D0[slot].y,
                                          -20, 20, -20, 20, 2, 0);
    effect->x = owner->x + D_801266D0[slot].x;
    effect->y = owner->y + D_801266D0[slot].y;
    effect->next = group->head;
    group->head = effect;
    increment_effect_owner_count(owner->team);
    if (get_entity_record(effect->ownerId)->team != owner->team) {
        add_entity_progress(owner, 5000);
    }
    start_cooldown_timed_event(owner, 0x26, 3.0f);
    if (D_801266F0 != 0) {
        effect->ownerId = ownerId;
    }
    effect->group = group;
}
