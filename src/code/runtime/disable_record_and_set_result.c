#include "types.h"

typedef struct OptionalRecord24 {
    u8 pad00[0x24];
    void *record;
} OptionalRecord24;

extern void clear_field_1c_if_disabled(void *record, s32 enabled) __asm__("func_8010CB4C");

void disable_record_and_set_result(OptionalRecord24 *context, s32 *result) __asm__("func_80093EF8");

void disable_record_and_set_result(OptionalRecord24 *context, s32 *result)
{
    if (context->record != 0) {
        clear_field_1c_if_disabled(context->record, 0);
    }
    *result = 2;
}
