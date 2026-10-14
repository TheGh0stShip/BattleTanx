#include "types.h"

typedef struct CounterUnit {
    u8 pad00[0x1C];
    s32 counter;
} CounterUnit;

typedef struct CounterObject {
    u8 pad00[0xC];
    CounterUnit *unit;
    s8 flag;
} CounterObject;

void clear_object_flag_when_unit_active(CounterObject *object, s32 arg1, s32 arg2, s8 *result)
    __asm__("func_8009F34C");

void clear_object_flag_when_unit_active(CounterObject *object, s32 arg1, s32 arg2, s8 *result)
{
    if (object->unit->counter > 0) {
        *result = 2;
        object->flag = 0;
    }
}
