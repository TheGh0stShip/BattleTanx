#include "types.h"

typedef struct FramebufferState {
    u8 pad00[0xC0];
    s16 roleSlots[4];
    s32 width;
    u16 *base;
} FramebufferState;

extern FramebufferState *gFramebufferState __asm__("D_801257D0");

static inline s16 find_framebuffer_slot(u16 *framebuffer) {
    s16 slot;
    u16 *candidate;

    slot = 0;
    if (framebuffer == 0) {
        return -1;
    }
    candidate = gFramebufferState->base;
    for (; slot < 3; slot++) {
        if (candidate == framebuffer) {
            break;
        }
        candidate += gFramebufferState->width;
    }
    return slot;
}

void set_role_framebuffer(s32 role, u16 *framebuffer) __asm__("func_8007F070");

void set_role_framebuffer(s32 role, u16 *framebuffer) {
    if (role == 0) {
        gFramebufferState->roleSlots[3] = find_framebuffer_slot(framebuffer);
    } else if (role == 1) {
        gFramebufferState->roleSlots[2] = find_framebuffer_slot(framebuffer);
    } else if (role == 2) {
        gFramebufferState->roleSlots[1] = find_framebuffer_slot(framebuffer);
    } else if (role == 3) {
        gFramebufferState->roleSlots[0] = find_framebuffer_slot(framebuffer);
    }
}
