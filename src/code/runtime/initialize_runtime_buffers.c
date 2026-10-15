#include "types.h"

typedef struct RuntimeConfig {
    s32 enabled;
    s32 unk04;
    void *codeStart;
    s32 codeSize;
    void *codeEnd;
    s32 stackSize;
    void *outputBuffer;
    s32 outputSize;
    void *yieldBuffer;
    s32 yieldSize;
    void *framebuffer;
    void *matrixBuffer;
    u8 pad30[8];
    void *depthBuffer;
    s32 depthSize;
    u8 pad40[8];
} RuntimeConfig;

typedef struct RuntimeBuffers {
    void *list0;
    void *list1;
    void *list2;
    void *list3;
    void *framebuffer;
    void *matrixBuffer;
} RuntimeBuffers;

typedef struct RuntimeState {
    RuntimeConfig configs[2];
    RuntimeBuffers buffers[2];
    s16 slots[4];
    s32 allocationSize;
    void *allocationBase;
    u16 bufferIndex;
    u8 padD2[2];
    s32 busy;
} RuntimeState;

extern void func_80110C00(void *address, s32 size);
extern void func_8007E140(void *state);
extern void func_80114828();
extern void func_80077930(void *rom, void *destination, u32 size);

extern u8 D_80000400;
extern u8 D_8010E160;
extern u8 D_8010E230;
extern u8 D_801452A0;
extern u8 D_801B4AF0;
extern u8 D_801B4BF9;
extern u8 D_802E17F0;
extern u8 D_802E1BF0;
extern u8 D_802E27F0;
extern u8 D_802F27F0;
extern u8 D_8030A7F0;
extern u8 D_8030AFF0;
extern u8 D_8031AFF0;
extern u8 D_8031B1F0;
extern u8 D_803271F0;
extern u8 D_803C8880;
extern u8 D_803EF980;
extern u8 D_B00D7040;
extern u8 D_B00D7360;
extern void *D_801257C0;
extern void *D_801257C8;

void initialize_runtime_buffers(void) __asm__("func_8007D4E8");

void initialize_runtime_buffers(void)
{
    u16 index;
    u32 romSize;
    RuntimeConfig *configBase;
    RuntimeConfig *config;
    RuntimeBuffers *buffers;
    RuntimeState *state;

    state = (RuntimeState *)&D_801B4AF0;
    func_80110C00(&D_80000400, 0x70800);
    D_801B4BF9 = 1;
    D_801257C8 = state;
    func_8007E140(state);
    index = 0;
    while (index < 2) {
        configBase = &state->configs[index];
        config = configBase;
        config->enabled = 1;
        config->unk04 = 0;
        config->codeStart = &D_8010E160;
        config->codeSize = &D_8010E230 - &D_8010E160;
        config->codeEnd = &D_8010E230;
        config->stackSize = 0x1000;
        config->outputBuffer = &D_801452A0;
        config->outputSize = 0x800;
        config->yieldBuffer = &D_802E17F0;
        config->yieldSize = 0x400;
        config->framebuffer = &D_802E27F0;
        config->matrixBuffer = &D_802F27F0;
        config->depthBuffer = &D_802E1BF0;
        config->depthSize = 0xC00;

        buffers = &state->buffers[index];
        buffers->framebuffer = (void *)((u32)&D_803271F0 + index * 0x200);
        buffers->list0 = (void *)((u32)&D_8031AFF0 + index * 0x100);
        buffers->list1 = (void *)((u32)&D_8030AFF0 + index * 0x8000);
        buffers->list2 = (void *)((u32)&D_8031B1F0 + index * 0x6000);
        buffers->list3 = (void *)((u32)&D_8030A7F0 + index * 0x400);
        buffers->matrixBuffer = (void *)((u32)&D_802F27F0 + index * 0xC000);
        func_80114828(buffers->matrixBuffer);
        index++;
    }

    state->allocationBase = &D_80000400;
    state->allocationSize = 0x12C00;
    state->slots[0] = -1;
    state->slots[1] = -1;
    state->slots[2] = -1;
    state->slots[3] = -1;
    state->bufferIndex = 0;
    state->busy = 0;
    romSize = &D_B00D7360 - &D_B00D7040;
    if (romSize >= (u32)(&D_803EF980 - &D_803C8880)) {
    }
    D_801257C0 = &D_803C8880;
    func_80077930(&D_B00D7040, D_801257C0, romSize);
}
