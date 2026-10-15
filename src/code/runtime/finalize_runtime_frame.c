#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct RuntimeBufferSet {
    Gfx *list0;
    Gfx *list1;
    Gfx *list2;
} RuntimeBufferSet;

typedef struct RuntimeFrameSource {
    Gfx *commands;
    s32 list0Start;
    s32 list1Start;
    s32 list2Start;
    u8 pad10[8];
} RuntimeFrameSource;

typedef struct RuntimeState {
    u8 pad00[0x90];
    RuntimeFrameSource sources[2];
    s16 slot0;
    u8 padC2[0xE];
    u16 sourceIndex;
    u8 padD2[6];
    RuntimeBufferSet buffers;
} RuntimeState;

extern RuntimeState *D_801257C8;
extern void func_8007E248(void);
extern s32 func_8007E150(s16 slot);
extern Gfx *func_8007DC5C(RuntimeFrameSource *source, Gfx *commands);
extern Gfx *func_8007E320(RuntimeFrameSource *source, Gfx *commands);

s32 finalize_runtime_frame(void) __asm__("func_8007D998");

s32 finalize_runtime_frame(void)
{
    RuntimeFrameSource *source;
    RuntimeBufferSet *buffers;
    Gfx *commands;
    s32 slot;
    Gfx *command;

    func_8007E248();
    slot = func_8007E150(D_801257C8->slot0);
    source = &D_801257C8->sources[D_801257C8->sourceIndex];
    buffers = &D_801257C8->buffers;
    commands = source->commands;
    commands = func_8007DC5C(source, commands);

    command = buffers->list0++;
    command->w0 = 0xB8000000;
    command->w1 = 0;
    command = buffers->list1++;
    command->w0 = 0xB8000000;
    command->w1 = 0;
    command = buffers->list2++;
    command->w0 = 0xB8000000;
    command->w1 = 0;

    if ((u32)buffers->list0 > (u32)(source->list0Start + 0x8000)) {
    }
    if ((u32)buffers->list1 > (u32)(source->list1Start + 0x6000)) {
    }
    if ((u32)buffers->list2 > (u32)(source->list2Start + 0x400)) {
    }

    command = commands++;
    command->w0 = 0x06000000;
    command->w1 = source->list0Start;
    command = commands++;
    command->w0 = 0x06000000;
    command->w1 = source->list1Start;
    command = commands++;
    command->w0 = 0x06000000;
    command->w1 = source->list2Start;
    commands = func_8007E320(source, commands);
    return slot;
}
