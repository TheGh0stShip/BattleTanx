#include "types.h"

typedef struct SpawnPlacement {
    f32 x;
    f32 y;
    u16 angle;
} SpawnPlacement;

typedef struct UnitSpawnCommand {
    s8 value00;
    u8 pad01;
    u16 owner;
    f32 x;
    s32 value08;
    f32 y;
    u16 angle;
    s8 value12;
    u8 pad13;
    s16 value14;
    s8 value16;
    u8 pad17;
    s32 shape;
    u16 flags;
    u8 value1E;
} UnitSpawnCommand;

extern void func_800A03B8(s16 unit);
extern s32 *func_8007AAF4(void);
extern s32 func_8007C6D8(void);
extern s32 spawn_unit(s16 unit, UnitSpawnCommand *command) __asm__("func_80097038");

void spawn_unit_at_placement(s16 unit, s32 owner, SpawnPlacement *placement, s32 shape, u8 kind,
                             u8 option, u8 force) __asm__("func_8009FA70");

void spawn_unit_at_placement(s16 unit, s32 owner, SpawnPlacement *placement, s32 shape, u8 kind,
                             u8 option, u8 force)
{
    UnitSpawnCommand command;
    s32 base;
    u16 flags;

    func_800A03B8(unit);
    command.value00 = 0;
    command.owner = owner;
    command.x = placement->x;
    command.value08 = 0;
    command.y = placement->y;
    command.angle = placement->angle;
    command.value12 = 0;
    command.value14 = 0;
    command.value16 = 0;
    command.shape = shape;
    base = (option != 0) << 8;
    if (*func_8007AAF4() != 9 && force == 0) {
        flags = base;
    } else {
        flags = base | 0x1000;
    }
    command.flags = flags;
    if (func_8007C6D8() != 0 && ((command.owner == 0) & (option == 0))) {
        command.flags |= 0x8000;
    }
    command.value1E = kind;
    spawn_unit(unit, &command);
}
