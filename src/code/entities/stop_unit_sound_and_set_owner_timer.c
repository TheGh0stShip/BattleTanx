#include "types.h"

typedef struct TimerUnit {
    u8 pad000[0x4];
    u8 ownerId;
    u8 pad005[0x457];
    s32 soundHandle45C;
} TimerUnit;

extern void stop_sound(s32 handle) __asm__("func_800798C0");
extern void *get_entity_record(u16 index) __asm__("func_800A6688");
extern void func_800A51E8(void *owner, s32 key, f32 value);

void stop_unit_sound_and_set_owner_timer(TimerUnit *unit) __asm__("func_8009BB5C");

void stop_unit_sound_and_set_owner_timer(TimerUnit *unit)
{
    if (unit->soundHandle45C != -1) {
        stop_sound(unit->soundHandle45C);
        unit->soundHandle45C = -1;
    }
    func_800A51E8(get_entity_record(unit->ownerId), 0x24, 3.0f);
}
