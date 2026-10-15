#include "types.h"

typedef struct LinkedMarker {
    u8 pad00[0x2C];
    struct LinkedMarker *next;
} LinkedMarker;

typedef struct HandlerObject {
    u8 pad00[0x8];
    s32 kind;
} HandlerObject;

typedef struct ObjectHandlerEntry {
    void (*handler)(HandlerObject *object, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
    u8 pad04[0x8];
} ObjectHandlerEntry;

typedef struct DyingUnit {
    u8 pad00;
    u8 alive;
    u8 pad02;
    u8 reportLoss;
    u8 owner;
    u8 pad05[0xF];
    union {
        u16 half;
        u8 bytes[2];
    } flags;
    u8 pad16[0x2];
    u32 type;
    s32 value1C;
    u8 pad20[0x4];
    f32 x;
    f32 y;
    f32 z;
    u8 pad30[0x4];
    f32 turret;
    u8 pad38[0x60];
    LinkedMarker *markers;
    u8 pad9C[0x360];
    f32 heading;
    u8 pad400[0x58];
    s32 sound458;
    s32 sound45C;
    u8 pad460[0x44];
    s32 value4A4;
    u8 pad4A8[0x48];
    s32 sound4F0;
    u8 pad4F4[0x8];
    HandlerObject *attached;
    u8 pad500[0x4];
    s32 attachedArg;
} DyingUnit;

typedef struct OwnerState {
    u8 pad000[0x22];
    u8 lives;
    u8 pad023;
    u8 flag24;
    u8 flag25;
    u8 pad026[0x6];
    s32 teamKills;
    s32 losses;
    u8 pad034[0x4];
    u8 reserve;
    u8 pad039;
    s16 value3A;
    u8 pad03C[0x16A];
    u8 value1A6;
    u8 pad1A7[0x7];
    u8 team;
    u8 pad1AF[0x159];
    u8 value308;
} OwnerState;

typedef struct GameModeInfo {
    s32 mode;
    u8 pad004[0x204];
    s32 wave;
} GameModeInfo;

extern u32 D_8012578C;
extern ObjectHandlerEntry D_802C3804[];

extern OwnerState *func_800A6688(s32 owner);
extern s32 func_8007C6D8(void);
extern void func_800A5B6C(s32 player, s32 arg1);
extern void func_800A5AA4(s32 player, s32 points);
extern GameModeInfo *get_game_mode(void) __asm__("func_8007AAF4");
extern s32 start_sound_scaled_by_listener_distance(s32 soundId, f32 x, f32 z) __asm__("func_80085B4C");
extern void func_80085C68(s32 soundId, f32 x, f32 z, f32 volume);
extern void spawn_effect_kind_26(f32 *position, s32 variant) __asm__("func_800ED8C0");
extern s32 func_800A5D5C(void);
extern s32 sprintf(char *buf, const char *fmt, ...) __asm__("func_8011CC84");
extern void func_800A52AC(OwnerState *owner, char *line1, char *line2, f32 duration);
extern void func_800798C0(s32 handle);
extern void func_800A6FC0(LinkedMarker *marker, f32 x, f32 z, s32 index);
extern void func_800E445C(DyingUnit *unit);
extern s32 func_800EC644(void);
extern void func_800A424C(OwnerState *owner);
extern void func_800A4368(OwnerState *owner);
extern s32 func_80078834(f32 x, f32 z, u16 angle, s32 mode, s32 owner);
extern void func_800A4E40(OwnerState *owner, s32 arg1);
extern s32 func_800A0400(s32 type, f32 *pos, u16 angle, s32 owner, s32 arg4, s32 arg5);
extern void func_80107170(s32 arg0);
extern s32 func_8009FBE4(DyingUnit *unit);
extern void spawn_effect_kind_03(f32 *pos, s32 kind, s32 arg2, s32 arg3) __asm__("func_800911A0");

void destroy_unit(DyingUnit *u, u32 killer, s32 spawnWreck) __asm__("func_80097DD0");

void destroy_unit(DyingUnit *u, u32 killer, s32 spawnWreck)
{
    char line1[32];
    char line2[32];
    f32 pos[2];
    OwnerState *owner;
    LinkedMarker *next;
    s32 count;
    s32 i;
    s32 marker;

    owner = func_800A6688(u->owner);
    if (u->alive == 0) {
        return;
    }
    switch (D_8012578C) {
    case 6:
    case 7:
        u->value1C = 1;
        return;
    }
    if (func_8007C6D8() == 0 || !(u->flags.half & 0x900)) {
        owner->losses++;
    }
    if (killer < 4) {
        if (owner->team != func_800A6688(killer & 0xFFFF)->team) {
            func_800A5B6C(killer, 1);
            switch (u->type) {
            case 1:
                func_800A5AA4(killer, 500);
                break;
            case 0:
                if (get_game_mode()->mode == 7) {
                    func_800A5AA4(killer, ((get_game_mode()->wave - 5) / 3 + 1) * 1000);
                } else {
                    func_800A5AA4(killer, 1000);
                }
                break;
            case 2:
                if (u->flags.half & 4) {
                    func_800A5AA4(killer, 5000);
                } else {
                    func_800A5AA4(killer, 3000);
                }
                break;
            }
        } else {
            owner->teamKills++;
        }
    }
    if (u->flags.half & 0x10) {
        start_sound_scaled_by_listener_distance(0x1F, u->x, u->z);
    } else {
        func_80085C68(0xD, u->x, u->z, 0.75f);
    }
    spawn_effect_kind_26(&u->x, (u->type == 1) ? 5 : 0xE);
    if (!(u->flags.half & 0x100) && owner->value1A6 == 0) {
        if (u->flags.half & 0x800) {
            owner->flag25 = 0;
        } else {
            owner->flag24 = 0;
        }
    }
    owner->lives--;
    if (get_game_mode()->mode == 5 || get_game_mode()->mode == 7) {
        if (u->owner != 0) {
            count = func_800A5D5C();
            if (count > 0) {
                if (count == 1) {
                    sprintf(line1, "1 ENEMY");
                    sprintf(line2, "TANK REMAINS");
                } else {
                    sprintf(line1, "%d ENEMY", count);
                    sprintf(line2, "TANKS REMAIN");
                }
                func_800A52AC(func_800A6688(0), line1, line2, 3.0f);
            }
        }
    }
    if (u->flags.half & 0x800) {
        if (owner->reserve >= 2) {
            owner->reserve--;
        }
    }
    owner->lives = (owner->lives < 6) ? owner->lives : 0;
    if (u->sound458 != -1) {
        func_800798C0(u->sound458);
        u->sound458 = -1;
    }
    if (u->sound45C != -1) {
        func_800798C0(u->sound45C);
        u->sound45C = -1;
    }
    if (u->sound4F0 != -1) {
        func_800798C0(u->sound4F0);
        u->sound4F0 = -1;
    }
    if (u->attached != 0) {
        if (D_802C3804[u->attached->kind].handler != 0) {
            D_802C3804[u->attached->kind].handler(u->attached, u->attachedArg, 4, 0, 0);
        }
    }
    if (u->markers != 0) {
        i = 0;
        do {
            next = u->markers->next;
            func_800A6FC0(u->markers, u->x, u->z, i++);
            u->markers = next;
        } while (next != 0);
    }
    u->alive = 0;
    func_800E445C(u);
    if (func_800EC644() == 0) {
        func_800A424C(owner);
        if (u->reportLoss != 0) {
            func_800A4368(owner);
            if (owner->value1A6 == 0) {
                if (owner->lives != 0 || owner->value3A != 0 || owner->value308 != 0) {
                    marker = func_80078834(u->x, u->z, (u32)(u->heading * 182.04445f), 3, u->owner);
                } else {
                    marker = func_80078834(u->x, u->z, (u32)(u->heading * 182.04445f), 2, u->owner);
                }
                if (marker != 0) {
                    func_800A4E40(owner, marker);
                }
            }
        }
    }
    if (!spawnWreck || func_800A0400(u->type, &u->x, (u32)(u->turret * 182.04445f), u->owner, u->value4A4,
                                     u->flags.bytes[1] & 0x10) < 0) {
        func_80107170(u->value4A4);
    }
    pos[1] = u->x;
    pos[0] = u->z;
    spawn_effect_kind_03(pos, 0xB, 0xD2, func_8009FBE4(u) & 0xFF);
}
