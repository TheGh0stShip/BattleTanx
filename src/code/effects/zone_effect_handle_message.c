#include "types.h"

typedef struct ZoneSlot {
    u8 pad00[4];
    u32 mode;
    u8 pad08[0x50];
} ZoneSlot;

typedef struct ZoneSession {
    u8 pad000[0x568];
    ZoneSlot *slots;
} ZoneSession;

typedef struct ZoneEffect {
    u8 pad00[0xC];
    u8 flags;
    u8 frameCount;
    u8 frame;
    u8 pad0F[3];
    s16 health;
    s16 slot;
} ZoneEffect;

typedef struct ZoneMessage {
    u8 pad00[8];
    u32 kind;
    s32 target;
} ZoneMessage;

typedef struct ZoneHit {
    u8 pad00[0x10];
    s32 damage;
    u8 pad14[2];
    u16 sourceId;
    u8 shielded;
} ZoneHit;

typedef struct ZoneOwner {
    u8 pad000[0x1AE];
    u8 teamIndex;
} ZoneOwner;

extern u8 gSlotRank[4] __asm__("D_801260A4");

ZoneSession *get_spawn_session(void) __asm__("func_800821C0");
void release_effect(ZoneEffect *effect) __asm__("func_8008B89C");
void remove_effects_by_owner(ZoneEffect *owner) __asm__("func_80093F3C");
void unit_update_sound_ramp(s32 unit, s32 soundId) __asm__("func_80099CD8");
void start_cooldown_timed_event(ZoneOwner *owner, s32 event, f32 duration)
    __asm__("func_800A51E8");
void add_entity_progress(ZoneOwner *entity, s32 amount)
    __asm__("func_800A59E8");
ZoneOwner *get_entity_record(u16 index) __asm__("func_800A6688");

void zone_effect_handle_message(ZoneEffect *effect, ZoneMessage *message,
                                ZoneHit *hit, s32 *result)
    __asm__("func_80093080");

void zone_effect_handle_message(ZoneEffect *effect, ZoneMessage *message,
                                ZoneHit *hit, s32 *result)
{
    u8 rank;
    ZoneOwner *source;
    ZoneOwner *owner;
    ZoneSlot *slot;

    switch (message->kind) {
    case 2:
    case 12:
    case 22:
    case 34:
        slot = &get_spawn_session()->slots[effect->slot];
        if (slot->mode == 0x14 && hit->shielded == 0) {
            hit->damage = 0;
        }
        if (effect->flags & 0x80) {
            *result = 0;
            effect->health -= hit->damage;
            if (effect->health < 0) {
                effect->health = 0;
            }
            return;
        }
        effect->health -= hit->damage;
        if (effect->health < 0) {
            effect->health = 0;
        }
        switch (slot->mode) {
        case 11:
            rank = gSlotRank[0];
            goto notify;
        case 12:
            rank = gSlotRank[1];
            goto notify;
        case 13:
            rank = gSlotRank[2];
            goto notify;
        case 14:
            rank = gSlotRank[3];
        notify:
            start_cooldown_timed_event(get_entity_record(rank), 1, 3.0f);
            break;
        }
        if (effect->health == 0) {
            release_effect(effect);
            effect->flags |= 0x80;
            *result = 0;
            remove_effects_by_owner(effect);
            effect->health = (effect->flags & 0x20) ? 1 : 0x11;
            if (effect->frame == effect->frameCount - 2) {
                switch (slot->mode) {
                case 11:
                    rank = gSlotRank[0];
                    goto award;
                case 12:
                    rank = gSlotRank[1];
                    goto award;
                case 13:
                    rank = gSlotRank[2];
                    goto award;
                case 14:
                    rank = gSlotRank[3];
                award:
                    owner = get_entity_record(rank);
                    source = get_entity_record(hit->sourceId);
                    if (owner->teamIndex != source->teamIndex) {
                        add_entity_progress(source, 1000);
                    }
                    break;
                }
            }
        } else {
            *result = 2;
        }
        return;
    case 0:
        unit_update_sound_ramp(message->target, 0x11);
    default:
        *result = 0;
        break;
    }
}
