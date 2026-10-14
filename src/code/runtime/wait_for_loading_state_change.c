#include "types.h"

extern u8 gLoadingState __asm__("D_80134E75");
extern void process_graphics_messages(void) __asm__("func_80079064");
extern void initialize_loading_state(void) __asm__("func_800AB690");
extern s32 update_loading_state(void) __asm__("func_800CEE2C");

void wait_for_loading_state_change(void) __asm__("func_800D0940");

void wait_for_loading_state_change(void)
{
    process_graphics_messages();
    initialize_loading_state();
    gLoadingState = 3;
    do {
    } while ((update_loading_state() & 0xFFFF) == 0xA);
    process_graphics_messages();
}
