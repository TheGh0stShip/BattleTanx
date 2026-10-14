#include "types.h"

typedef struct {
    u8 pad00[0x2];
    u16 firstPart;
    u8 pad04[0x8];
} PartGroup;

typedef struct {
    u8 partCount;
    u8 pad01;
    u16 firstPart;
} PartSet;

typedef struct {
    u8 pad00[0xC];
} PartRecord;

typedef struct {
    u8 pad000[0x570];
    PartGroup *groups;
    PartSet *sets;
    PartRecord *parts;
} PartTables;

extern PartTables *get_part_tables(void) __asm__("func_800821C0");
extern u32 random_u32(void) __asm__("func_800F38F4");
extern void spawn_part_debris(s32 arg0, u16 arg1, u16 arg2, u16 arg3, u16 angleX, u16 angleY, u16 angleZ,
                              u16 arg7, s32 arg8, s32 arg9, f32 arg10, PartRecord *part, s32 arg12,
                              s32 arg13) __asm__("func_8008F6F4");
extern f32 D_80071CF0;

void spawn_group_part_debris_mode(s32 group, s32 arg1, u16 arg2, u16 arg3, u16 arg4, s32 arg5, u8 mode) __asm__("func_800905D8");

void spawn_group_part_debris_mode(s32 group, s32 arg1, u16 arg2, u16 arg3, u16 arg4, s32 arg5, u8 mode) {
    PartTables *tables;
    PartGroup *groupEntry;
    PartSet *set;
    s32 i;
    s32 angleX;
    s32 angleY;
    s32 angleZ;
    s32 spin;
    s32 flags;

    tables = get_part_tables();
    groupEntry = tables->groups + group;
    set = &tables->sets[groupEntry->firstPart];
    for (i = 0; i < set->partCount; i++) {
        angleX = (random_u32() % 1280) & 0xFFFF;
        angleY = (random_u32() % 1280) & 0xFFFF;
        angleZ = (random_u32() % 1280) & 0xFFFF;
        spin = (random_u32() % 65535) & 0xFFFF;
        if (mode == 0) {
            flags = ((random_u32() & 7) == 0) * 2;
        } else {
            flags = mode;
        }
        spawn_part_debris(arg1, arg2, arg3, arg4, angleX, angleY, angleZ, spin, 0x2000, 0,
                          D_80071CF0, &tables->parts[set->firstPart + i], arg5, flags);
    }
}
