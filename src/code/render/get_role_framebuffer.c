#include "types.h"

typedef struct FramebufferState {
    u8 pad00[0xC0];
    s16 roleSlots[4];
    s32 width;
    u16 *base;
} FramebufferState;

extern FramebufferState *gFramebufferState __asm__("D_801257D0");

u16 *get_role_framebuffer(s32 role) __asm__("func_8007F204");

u16 *get_role_framebuffer(s32 role)
{
    u16 *framebuffer = 0;
    FramebufferState *state;
    s32 slot;

    if (role == 0) {
        state = gFramebufferState;
        slot = state->roleSlots[3];
    } else if (role == 1) {
        state = gFramebufferState;
        slot = state->roleSlots[2];
    } else if (role == 2) {
        state = gFramebufferState;
        slot = state->roleSlots[1];
    } else if (role == 3) {
        state = gFramebufferState;
        slot = state->roleSlots[0];
    } else {
        goto done;
    }
    if (slot != -1) {
        framebuffer = state->base + slot * state->width;
    }
done:
    return framebuffer;
}
