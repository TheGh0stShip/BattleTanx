#include "types.h"

typedef struct MarkerEffect {
    u8 pad00[4];
    s32 serial;
    u8 pad08[0x10];
    s32 value18;
} MarkerEffect;

typedef struct PickupUnit {
    u8 pad000[4];
    u8 player;
    u8 pad005[3];
    s32 value08;
    s32 boostEnd;
    u8 pad010[4];
    u16 flags;
    u8 pad016[6];
    s32 health;
    s32 maxHealth;
    f32 x;
    u8 pad028[4];
    f32 z;
    u8 pad030[0x438];
    u32 weapon;
    u8 pad46C[8];
    s32 notice;
    u8 pad478[8];
    u16 ammo[4];
    u16 count488;
    u16 count48A;
    u16 count48C;
    u16 count48E;
    u8 pad490[6];
    u16 count496;
    u16 count498;
    u16 count49A;
    u16 count49C;
    u16 count49E;
    u16 count4A0;
    u8 pad4A2[0x5A];
    MarkerEffect *marker;
    s32 markerSerial;
    s32 value504;
} PickupUnit;

extern void *get_entity_record(u16 index) __asm__("func_800A6688");
extern s32 func_800EC644(void);
extern s32 start_sound_scaled_by_listener_distance(s32 soundId, f32 x, f32 z) __asm__("func_80085B4C");
extern void func_800A51E8(void *owner, s32 key, f32 value);
extern void add_entity_progress(void *entity, s32 amount) __asm__("func_800A59E8");
extern MarkerEffect *spawn_effect_kind_17(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
    __asm__("func_800F2044");
extern void func_800A5DD8(void *player, s32 arg1);
extern void func_800A5AA4(u8 player, s32 amount);
extern u8 D_80134E68;
extern u8 D_80134E69;
extern s32 gGameTicks __asm__("D_801B4AA8");

void apply_pickup(PickupUnit *unit, u32 kind, s32 announce) __asm__("func_80099D90");

void apply_pickup(PickupUnit *unit, u32 kind, s32 announce)
{
    void *player;

    player = get_entity_record(unit->player);
    if (func_800EC644() == 0 && announce != 0) {
        start_sound_scaled_by_listener_distance(0x2B, unit->x, unit->z);
        func_800A51E8(player, kind + 11, 3.0f);
        add_entity_progress(player, 100);
    }
    switch (kind) {
    case 0:
        if (unit->health >= unit->maxHealth) {
            unit->count4A0++;
            if (unit->notice == 0) {
                unit->notice = 16;
            }
        } else {
            unit->health += (s32)(unit->maxHealth * 0.3f);
            if (unit->health > unit->maxHealth) {
                unit->health = unit->maxHealth;
            }
        }
        break;
    case 3:
        unit->count48A += 5;
        if (unit->notice == 0) {
            unit->notice = 5;
        }
        break;
    case 7:
        unit->count496 += 5;
        if (unit->notice == 0) {
            unit->notice = 11;
        }
        break;
    case 1:
        unit->count48C += 1;
        if (unit->notice == 0) {
            unit->notice = 6;
        }
        break;
    case 15:
        unit->count48E += 5;
        if (unit->notice == 0) {
            unit->notice = 7;
        }
        break;
    case 2:
        unit->count488 += 5;
        if (unit->notice == 0) {
            unit->notice = 4;
        }
        break;
    case 9:
        unit->count498 += 5;
        if (unit->notice == 0) {
            unit->notice = 12;
        }
        break;
    case 10:
        unit->count49A += 2;
        if (unit->notice == 0) {
            unit->notice = 13;
        }
        break;
    case 19:
        unit->count49A += 1;
        if (unit->notice == 0) {
            unit->notice = 13;
        }
        break;
    case 5:
        switch (unit->weapon) {
        case 1:
        case 3:
            unit->ammo[unit->weapon] += 30;
            unit->ammo[unit->weapon] = unit->ammo[unit->weapon];
            break;
        case 2:
            unit->ammo[2] += 70;
            unit->ammo[unit->weapon] = unit->ammo[unit->weapon];
            break;
        }
        break;
    case 11:
        unit->health += (s32)(unit->maxHealth * 0.2f);
        if (unit->health > unit->maxHealth) {
            unit->health = unit->maxHealth;
        }
        if (D_80134E69 == 0) {
            switch (unit->weapon) {
            case 1:
            case 3:
                unit->ammo[unit->weapon] += 15;
                break;
            case 2:
                unit->ammo[2] += 35;
                break;
            }
        }
        break;
    case 4:
        unit->flags |= 0x80;
        break;
    case 8:
        if (unit->marker != 0 && unit->markerSerial == unit->marker->serial) {
            unit->marker->value18 += 100;
        } else {
            unit->marker = spawn_effect_kind_17(unit->x, unit->z, unit->player, 100, unit->value504);
            if (unit->marker != 0) {
                unit->markerSerial = unit->marker->serial;
            }
        }
        break;
    case 18:
        if (unit->marker != 0 && unit->markerSerial == unit->marker->serial) {
            unit->marker->value18 += 25;
        } else {
            unit->marker = spawn_effect_kind_17(unit->x, unit->z, unit->player, 25, unit->value504);
            if (unit->marker != 0) {
                unit->markerSerial = unit->marker->serial;
            }
        }
        break;
    case 12:
        if (D_80134E68 != 0) {
            if (unit->boostEnd != 0) {
                unit->boostEnd += 900;
            } else {
                unit->value08 = 240;
                unit->boostEnd = gGameTicks + 900;
            }
        } else {
            unit->count49E += 1;
            if (unit->notice == 0) {
                unit->notice = 15;
            }
        }
        break;
    case 13:
        func_800A5DD8(player, 0);
        break;
    case 16:
        unit->count49C += 3;
        if (unit->notice == 0) {
            unit->notice = 14;
        }
        break;
    case 14:
        func_800A5AA4(unit->player, 900);
        break;
    }
}
