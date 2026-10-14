#include "types.h"

extern void *gCurrentRenderContext __asm__("D_801257D0");

void set_current_render_context(void *context) __asm__("func_8007E140");

void set_current_render_context(void *context)
{
    gCurrentRenderContext = context;
}
