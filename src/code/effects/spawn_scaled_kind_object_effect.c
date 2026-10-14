#include "types.h"

typedef struct ScaledKindObject {
    u8 pad00[0x4];
    u8 ownerIndex;
    u8 pad05[0x13];
    s32 kind;
    s32 value1C;
    u8 pad20[0x4];
    u8 position[0x10];
    f32 scale;
} ScaledKindObject;

typedef struct OwnerRecord {
    u8 pad000[0x1BF];
    u8 value1BF;
} OwnerRecord;

extern s16 D_802D5A5A;
extern s16 D_802D5A76;
extern s16 D_802D5A8E;
extern f32 D_80072980;

extern OwnerRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern void func_800905D8(s32 value, void *position, s32 a2, u16 a3, s32 a4, s32 a5, s32 a6);

void spawn_scaled_kind_object_effect(ScaledKindObject *object) __asm__("func_8009EDD0");

void spawn_scaled_kind_object_effect(ScaledKindObject *object) {
    s32 value;
    OwnerRecord *owner;
    s32 flag;

    switch (object->kind) {
    case 1:
        value = D_802D5A76;
        break;
    case 2:
        value = D_802D5A8E;
        break;
    default:
        value = D_802D5A5A;
        break;
    }
    owner = get_entity_record(object->ownerIndex);
    flag = owner->value1BF;
    func_800905D8(value, object->position, 0, (u32)(object->scale * D_80072980), 0, flag, 0);
    object->value1C = -1;
}
