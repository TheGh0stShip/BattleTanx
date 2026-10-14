#include "types.h"

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct CollisionContact {
    u8 pad00[0xC];
    u8 flags;
    u8 pad0D[5];
    u16 ownerIndex;
    s32 kind;
    u16 value18;
    u8 pad1A[2];
    f32 value1C;
    f32 value20;
    u8 pad24[8];
    s16 value2C;
} CollisionContact;

typedef struct ContactOwner {
    u8 pad00[0x1BF];
    u8 value1BF;
} ContactOwner;

extern Vec3 D_80072CCC;
extern f32 D_80072D94;
extern s32 D_80125FB0[];
extern f32 D_80126038[];

extern void func_800ED8C0(f32 *pos, s32 sound);
extern ContactOwner *get_entity_record(u16 index) __asm__("func_800A6688");
extern s32 spawn_effect_kind_08(Vec3 *position, Vec3 *direction, s16 arg2, u16 arg3, u16 arg4, f32 scale, s32 arg6,
                                u8 arg7, f32 arg8, s32 arg9) __asm__("func_8008EF1C");

void spawn_contact_impact_effect(CollisionContact *contact) __asm__("func_800A2DC0");

void spawn_contact_impact_effect(CollisionContact *contact) {
    Vec3 pos;
    Vec3 dir;
    u8 ownerValue;

    dir = D_80072CCC;
    contact->value2C = 0;
    pos.x = contact->value20;
    pos.y = 0.0f;
    pos.z = contact->value1C;
    func_800ED8C0(&pos.x, 5);
    ownerValue = get_entity_record(contact->ownerIndex)->value1BF;
    spawn_effect_kind_08(&pos, &dir, 0, contact->value18, 0, D_80072D94, D_80125FB0[contact->kind], 1,
                         D_80126038[contact->kind], ownerValue);
    contact->flags |= 0x11;
}
