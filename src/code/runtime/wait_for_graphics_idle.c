#include "types.h"

typedef struct GraphicsThreadState {
    u8 pad000[0x1F0];
    u16 completedTasks;
    u16 pad1F2;
    u16 pendingTask;
    u16 pad1F6;
    u32 pad1F8;
    u32 activeTask;
    u32 pad200[2];
} GraphicsThreadState;

extern GraphicsThreadState gGraphicsThreadState __asm__("D_8014E0D0");

void wait_for_graphics_idle(void) __asm__("func_80079064");

void wait_for_graphics_idle(void)
{
    GraphicsThreadState snapshot;
    GraphicsThreadState *state = &gGraphicsThreadState;

    do {
        do {
            snapshot = *state;
        } while (snapshot.pendingTask != 0 || snapshot.activeTask != 0);
    } while (snapshot.completedTasks < 5);
}
