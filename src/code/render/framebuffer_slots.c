#include "types.h"

#define FRAMEBUFFER_SLOT_COUNT 3

typedef struct FramebufferState {
    u8 pad00[0xC2];
    s16 busySlots[FRAMEBUFFER_SLOT_COUNT];
    s32 width;
    u16 *base;
} FramebufferState;

extern FramebufferState *gFramebufferState __asm__("D_801257D0");

u16 *get_framebuffer_slot(s16 slot) __asm__("func_8007E150");
s16 find_framebuffer_slot(u16 *framebuffer) __asm__("func_8007E18C");
s16 find_free_framebuffer_slot(void) __asm__("func_8007E1E4");

u16 *get_framebuffer_slot(s16 slot)
{
    if (slot != -1) {
        return gFramebufferState->base + slot * gFramebufferState->width;
    }
    return 0;
}

s16 find_framebuffer_slot(u16 *framebuffer)
{
    u16 *candidate;
    s16 i;

    i = 0;
    if (framebuffer == 0) {
        return -1;
    }
    candidate = gFramebufferState->base;
    for (; i < FRAMEBUFFER_SLOT_COUNT; i++) {
        if (candidate == framebuffer) {
            break;
        }
        candidate += gFramebufferState->width;
    }
    return i;
}

s16 find_free_framebuffer_slot(void)
{
    s16 i;

    for (i = 0; i < FRAMEBUFFER_SLOT_COUNT; i++) {
        if (i != gFramebufferState->busySlots[2] && i != gFramebufferState->busySlots[1]
            && i != gFramebufferState->busySlots[0]) {
            return i;
        }
    }
    return -1;
}
