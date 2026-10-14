#include "types.h"

typedef struct GfxCmd {
    u32 w0;
    u32 w1;
} GfxCmd;

typedef struct RenderTask {
    u8 pad00[0x30];
    GfxCmd *start;
    s32 size;
    u8 pad38[0x8];
    s32 value40;
    u8 pad44[0x4];
} RenderTask;

typedef struct RenderState {
    RenderTask tasks[2];
    u8 pad90[0x30];
    s16 valueC0;
    u8 padC2[0x6];
    s32 valueC8;
    s32 valueCC;
    u16 current;
    u8 padD2[0x2];
    RenderTask *active;
} RenderState;

extern RenderState *D_801257D0;
extern void func_80122720(s32 index);
extern s32 func_80078F60(s32 index);
extern void func_801193E0(s32 value, s32 id, s32 flag);

GfxCmd *close_render_display_list(GfxCmd **start, GfxCmd *gfx) __asm__("func_8007E320");

/* Appends full-sync and end-display-list commands, then records the list in the current render task. */
GfxCmd *close_render_display_list(GfxCmd **start, GfxCmd *gfx) {
    s32 current = D_801257D0->current;
    RenderTask *task;
    s32 value;
    s32 index;

    {
        GfxCmd *cmd = gfx++;
        cmd->w0 = 0xE9000000;
        cmd->w1 = 0;
    }
    {
        GfxCmd *cmd = gfx++;
        cmd->w0 = 0xB8000000;
        cmd->w1 = 0;
    }
    task = &D_801257D0->tasks[current];
    func_80122720(current);
    task->start = *start;
    task->size = (gfx - *start) * sizeof(GfxCmd);
    index = D_801257D0->valueC0;
    D_801257D0->active = task;
    if (index != -1) {
        value = D_801257D0->valueCC + index * D_801257D0->valueC8 * 2;
    } else {
        value = 0;
    }
    D_801257D0->active->value40 = value;
    func_801193E0(func_80078F60(index), 0x29D, 1);
    return gfx;
}
