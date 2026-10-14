#include "types.h"

typedef struct DamageOwner {
    u8 pad000[0x60];
    s32 value60;
    u8 pad064[0x2AC];
    f32 armorScale;
    f32 damageScale;
} DamageOwner;

typedef struct DamageShield {
    u8 pad00[4];
    s32 id;
    u8 pad08[0x10];
    s32 strength;
} DamageShield;

typedef struct DamageUnit {
    u8 pad000;
    u8 active;
    u8 pad002;
    u8 warnOnHalf;
    u8 owner;
    u8 pad005[3];
    s32 value08;
    u8 pad00C[4];
    s32 value10;
    u16 flags;
    u8 pad016[2];
    s32 state;
    s32 health;
    s32 maxHealth;
    u8 pad024[0x494];
    s32 lastHitTick;
    u8 pad4BC[0x40];
    DamageShield *shield;
    s32 shieldId;
    s32 value504;
} DamageUnit;

extern f32 D_8007222C;
extern f32 D_80072230;
extern u8 D_80135762;
extern u8 D_80135763;
extern s32 gGameTicks __asm__("D_801B4AA8");

extern s32 entity_state_is_two(DamageUnit *unit) __asm__("func_800E3460");
extern s32 game_mode_is_3_through_6(void) __asm__("func_8007C6D8");
extern DamageOwner *get_entity_record(u16 index) __asm__("func_800A6688");
extern void configure_audio_slot(s32 slot, s32 value, s32 param, s32 period) __asm__("func_800A8EF8");
extern void start_cooldown_timed_event(DamageOwner *owner, s32 event, f32 duration) __asm__("func_800A51E8");
extern void func_8009EDD0(DamageUnit *unit);
extern void func_80097DD0(DamageUnit *unit, u32 attacker, s32 destroyed);

s32 apply_unit_damage(DamageUnit *unit, s32 amount, u32 attacker, s32 direct) __asm__("func_800983E0");

s32 apply_unit_damage(DamageUnit *unit, s32 amount, u32 attacker, s32 direct) {
    DamageOwner *owner;
    DamageShield *shield;
    f32 percent;
    f32 scale;
    s32 rumble;
    s32 burst;

    if (D_80135762 != 0) {
        return 0;
    }
    if (D_80135763 != 0 && entity_state_is_two(unit) == 0) {
        return 0;
    }
    if (unit->active == 0) {
        return 0;
    }
    if (unit->flags & 0x8001) {
        return 0;
    }
    if (unit->flags & 2) {
        func_8009EDD0(unit);
        func_80097DD0(unit, attacker, 0);
        return 1;
    }
    if (amount == 0) {
        return 0;
    }
    if ((unit->flags & 0x100) && game_mode_is_3_through_6() != 0) {
        owner = get_entity_record(1);
    } else {
        owner = get_entity_record(unit->owner);
    }
    scale = owner->damageScale;
    percent = D_8007222C;
    amount *= scale / percent;
    if (attacker < 4) {
        amount /= get_entity_record(attacker)->armorScale / percent;
    }
    owner = get_entity_record(unit->owner);
    if (amount == 0) {
        amount = 1;
    }
    if (entity_state_is_two(unit) == 0) {
        rumble = amount / 3 + 20;
        if (rumble > 40) {
            rumble = 40;
        }
        configure_audio_slot(unit->owner, rumble, 6, 4);
    }
    shield = unit->shield;
    if (shield != 0 && unit->shieldId == shield->id) {
        if (shield->strength >= amount) {
            shield->strength -= amount;
            amount = 0;
        } else {
            amount -= shield->strength;
            shield->strength = 0;
        }
    }
    if ((attacker == unit->owner) & (direct != 0)) {
        start_cooldown_timed_event(get_entity_record(attacker), 10, 3.0f);
    } else if (unit->state == 2 && owner->value60 != unit->value504) {
        start_cooldown_timed_event(owner, 2, 3.0f);
    }
    unit->health -= amount;
    if (unit->warnOnHalf != 0 && unit->health < unit->maxHealth / 2) {
        start_cooldown_timed_event(owner, 0x21, 3.0f);
    }
    if (unit->value10 == 0) {
        unit->value08 = 0xF0;
    }
    unit->lastHitTick = gGameTicks;
    if (unit->health <= 0) {
        if (entity_state_is_two(unit) == 0) {
            burst = amount / 3 + 20;
            if (burst > 40) {
                burst = 40;
            }
            configure_audio_slot(unit->owner, (u32)(burst * D_80072230), 2, 1);
        }
        unit->health = 0;
        func_80097DD0(unit, attacker, 1);
        return 1;
    }
    if (entity_state_is_two(unit) == 0) {
        rumble = amount / 3 + 20;
        if (rumble > 40) {
            rumble = 40;
        }
        configure_audio_slot(unit->owner, rumble, 6, 4);
    }
    return 0;
}
