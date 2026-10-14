#include "types.h"

typedef struct SoundUnitRef {
    u8 pad000[0x458];
    s32 soundHandle458;
    s32 soundHandle45C;
    u8 pad460[0x90];
    s32 soundHandle4F0;
} SoundUnitRef;

typedef struct SoundContact {
    u8 pad00[0xC];
    SoundUnitRef *unit;
} SoundContact;

extern void stop_sound(s32 handle) __asm__("func_800798C0");

void stop_contact_unit_sounds(SoundContact *contact) __asm__("func_8009F544");

void stop_contact_unit_sounds(SoundContact *contact)
{
    SoundUnitRef *unit;

    unit = contact->unit;
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
