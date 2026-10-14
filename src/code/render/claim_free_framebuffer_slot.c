#include "types.h"

typedef struct FramebufferState {
    u8 pad00[0xC0];
    s16 roleSlots[4];
} FramebufferState;

extern FramebufferState *gFramebufferState __asm__("D_801257D0");

static inline s16 find_unused_framebuffer(void) {
    s16 i;

    for (i = 0; i < 3; i++) {
        if (i != gFramebufferState->roleSlots[3] && i != gFramebufferState->roleSlots[2] &&
            i != gFramebufferState->roleSlots[1]) {
            return i;
        }
    }
    return -1;
}

void claim_free_framebuffer_slot(void) __asm__("func_8007E248");

void claim_free_framebuffer_slot(void) {
    while (gFramebufferState->roleSlots[0] != -1 || find_unused_framebuffer() == -1) {
    }
    gFramebufferState->roleSlots[0] = find_unused_framebuffer();
}
