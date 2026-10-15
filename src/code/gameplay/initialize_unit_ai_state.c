#include "types.h"

typedef struct UnitAiState {
    s32 value00;
    s32 value04;
    u8 pad08[0x10];
    s32 value18;
    s32 value1C;
    u8 pad20[0x10];
    u8 playStack[0x40];
    f32 slots[10];
    u8 route[0x200];
    u8 path[0x12];
    s16 pathNode;
    u8 pad2AC[4];
    s32 value2B0;
    s8 value2B4;
    s8 value2B5;
    u8 pad2B6[2];
    s8 value2B8;
    s8 value2B9;
    s8 value2BA;
    s8 value2BB;
    s8 value2BC;
    u8 value2BD;
    s8 value2BE;
    s8 value2BF;
    s16 value2C0;
    s16 value2C2;
    s32 value2C4;
    s32 value2C8;
    s32 value2CC;
    s32 value2D0;
} UnitAiState;

typedef struct UnitRecord {
    u8 pad000[4];
    u8 ownerId;
    u8 pad005[0xF];
    u16 flags;
    u8 pad016[0xE];
    f32 x;
    u8 pad028[0x74];
    UnitAiState ai;
    u8 pad370[0x9A];
    s8 state40A;
    u8 pad40B[0xC5];
    u8 target[4];
} UnitRecord;

typedef struct UnitInfo {
    u8 pad000[0x190];
    f32 value190;
    f32 value194;
    u8 pad198[0xD];
    s8 value1A5;
} UnitInfo;

s32 func_8007B1DC(void);
UnitRecord *func_800A03B8(s16 id);
UnitInfo *func_800A6688(u8 id);
void func_800DDCA4(void *route);
void func_800DE0C0(void *route, s32 index);
s16 func_800DE3EC(void *route, f32 *position);
void func_800E1EE0(void *path);
void func_800E28DC(UnitRecord *unit, void *target, s32 mode, s32 *distance,
                   s32 flags);
void func_800E4344(UnitRecord *unit, s32 arg1);
void func_800E4A38(void);
void func_800EA1B0(void *stack);
void func_800EA1B8(void *stack, s32 play);
f32 func_800F3940(void);

extern f32 D_8007463C;
extern f32 D_80074640;

void initialize_unit_ai_state(s16 id, s32 arg1, s8 arg2)
    __asm__("func_800E4104");

void initialize_unit_ai_state(s16 id, s32 arg1, s8 arg2)
{
    f32 position[20];
    s32 distance;
    UnitRecord *unit;
    UnitAiState *ai;
    UnitInfo *info;
    void *stack;
    u16 i;
    f32 scaleA;
    f32 scaleB;
    f32 value;
    f32 random;
    s32 now;

    unit = func_800A03B8(id);
    ai = &unit->ai;
    info = func_800A6688(unit->ownerId);
    ai->value2B4 = 3;
    unit->state40A = 0x10;
    stack = ai->playStack;
    ai->value00 = 0;
    ai->value04 = 0;
    ai->value18 = 0;
    ai->value1C = 0;
    func_800EA1B0(stack);
    if (unit->flags & 0x8000) {
        func_800EA1B8(stack, 0x1C);
    }
    for (i = 0; i < 10; i++) {
        *(s32 *)&ai->slots[i] = 0;
    }
    value = info->value190;
    scaleA = D_8007463C;
    random = func_800F3940();
    scaleB = D_80074640;
    ai->slots[0] = value * scaleA + random * scaleB;
    value = info->value194;
    ai->slots[1] = value * scaleA + func_800F3940() * scaleB;
    func_800DDCA4(ai->route);
    func_800E1EE0(ai->path);
    position[1] = unit->x;
    position[0] = unit->x;
    ai->pathNode = func_800DE3EC(ai->route, position);
    func_800DE0C0(ai->route, 0);
    ai->value2B0 = 0;
    ai->value2B5 = 0;
    ai->value2B8 = id;
    ai->value2B9 = 0;
    ai->value2BA = 1;
    if (unit->flags & 4) {
        UnitInfo *other;

        ai->value2BB = 0;
        other = func_800A6688(unit->ownerId);
        func_800E28DC(unit, unit->target, 0, &distance, 0);
        other->value1A5 = distance <= 0x7FFF;
    } else {
        ai->value2BB = arg2;
    }
    ai->value2BD = 0xFF;
    ai->value2BE = 1;
    ai->value2BC = 0;
    ai->value2BF = 0;
    ai->value2C0 = 0;
    ai->value2C2 = 0x546;
    now = func_8007B1DC();
    ai->value2C4 = 0;
    ai->value2C8 = now;
    ai->value2CC = now;
    ai->value2D0 = 0;
    func_800E4344(unit, arg1);
    func_800E4A38();
}
