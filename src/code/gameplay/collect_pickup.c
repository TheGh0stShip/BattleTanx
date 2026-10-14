#include "types.h"

typedef struct Pickup Pickup;

typedef struct PickupList {
    u8 pad00[0x10];
    Pickup *head;
} PickupList;

typedef struct EntityRecord {
    u8 pad000[0x16];
    u16 value16;
    u8 pad018[0xB];
    u8 value23;
    u8 pad024[0x182];
    u8 value1A6;
    u8 pad1A7[0x7];
    u8 team;
    u8 pad1AF[0x9];
    PickupList *pickups;
} EntityRecord;

struct Pickup {
    u8 pad00[0xC];
    u8 lastOwner;
    u8 pad0D[0x3];
    s32 state;
    u8 holderEntity;
    u8 pad15[0x3];
    s32 effect;
    u8 pad1C[0xC];
    s32 value28;
    Pickup *next;
};

typedef struct Collector {
    u8 pad000[0x4];
    u8 entity;
    u8 pad005[0xF];
    u16 flags;
    u8 pad016[0x82];
    Pickup *carried;
    u8 pad09C[0x468];
    s32 value504;
} Collector;

extern EntityRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern void decrement_effect_owner_count(s32 owner) __asm__("func_800A6888");
extern s32 ai_member_status_is_2(Collector *member) __asm__("func_800E3460");
extern void func_80107170(s32 effect);
extern void start_cooldown_timed_event(EntityRecord *owner, s32 event, f32 duration) __asm__("func_800A51E8");
extern void add_entity_progress(EntityRecord *entity, s32 amount) __asm__("func_800A59E8");
extern s32 game_mode_is_3_through_6(void) __asm__("func_8007C6D8");
extern s32 find_sound_instance(s32 soundId, s32 index) __asm__("func_800796F0");

void collect_pickup(Collector *collector, Pickup *pickup) __asm__("func_800A70E0");

void collect_pickup(Collector *collector, Pickup *pickup) {
    EntityRecord *holder;
    EntityRecord *previous;
    EntityRecord *self;
    PickupList *list;
    Pickup *prev;
    Pickup *node;

    if (collector->flags & 4) {
        return;
    }
    if (get_entity_record(collector->entity)->value1A6 == 0 && ai_member_status_is_2(collector) != 0) {
        return;
    }
    if (pickup->state == 1) {
        return;
    }
    if (pickup->state == 0) {
        holder = get_entity_record(pickup->holderEntity);
        if (get_entity_record(collector->entity)->team == holder->team) {
            return;
        }
        decrement_effect_owner_count(holder->team);
        list = holder->pickups;
        if (list->head == pickup) {
            list->head = pickup->next;
        } else {
            prev = list->head;
            node = prev->next;
            while (node != 0) {
                if (node == pickup) {
                    break;
                }
                prev = node;
                node = prev->next;
            }
            if (node == 0) {
                return;
            }
            prev->next = pickup->next;
        }
    }
    if (pickup->effect != -1) {
        func_80107170(pickup->effect);
        pickup->effect = -1;
    }
    pickup->state = 1;
    pickup->next = collector->carried;
    collector->carried = pickup;
    previous = get_entity_record(pickup->lastOwner);
    self = get_entity_record(collector->entity);
    if (previous->team != self->team) {
        start_cooldown_timed_event(previous, 4, 3.0f);
        add_entity_progress(self, 1000);
    }
    if (game_mode_is_3_through_6() != 0 && previous->value16 == 0 && self->value16 != 0) {
        find_sound_instance(0x2E, 0);
    } else {
        find_sound_instance(0x2F, 0);
    }
    start_cooldown_timed_event(self, 0x23, 3.0f);
    if (!(collector->flags & 0x100)) {
        previous->value23 |= 1;
    }
    pickup->value28 = collector->value504;
}
