#include "types.h"

typedef struct SoundUnit {
    u8 pad000[0x1];
    u8 inUse;
    u8 pad002[0x456];
    s32 soundHandle458;
    s32 soundHandle45C;
    u8 pad460[0x90];
    s32 soundHandle4F0;
} SoundUnit;

extern SoundUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void stop_sound(s32 handle) __asm__("func_800798C0");

void stop_all_unit_sounds(void) __asm__("func_80097B7C");

void stop_all_unit_sounds(void)
{
    SoundUnit *unit;
    s32 i;

    for (i = 0; i < 20; i++) {
        unit = get_unit(i);
        if (unit->inUse == 0) {
            continue;
        }
        if (unit->soundHandle458 != -1) {
            stop_sound(unit->soundHandle458);
            unit->soundHandle458 = -1;
        }
        if (unit->soundHandle45C != -1) {
            stop_sound(unit->soundHandle45C);
            unit->soundHandle45C = -1;
        }
        if (unit->soundHandle4F0 != -1) {
            stop_sound(unit->soundHandle4F0);
            unit->soundHandle4F0 = -1;
        }
    }
}
