#include "types.h"

extern u8 *gCurrentRenderContext __asm__("D_801257D0");

void *get_render_frame_record(void) __asm__("func_8007F030");

void *get_render_frame_record(void)
{
    return gCurrentRenderContext + 0xD8;
}
