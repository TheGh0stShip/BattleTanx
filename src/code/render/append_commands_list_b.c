#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

typedef struct CommandLists {
    GfxCommand *listA;
    GfxCommand *listB;
} CommandLists;

typedef struct RenderLists {
    u8 pad00[0xD8];
    CommandLists lists;
} RenderLists;

extern RenderLists *gRenderLists __asm__("D_801257D0");

void append_commands_list_b(s32 count, GfxCommand *src) __asm__("func_8007EFB8");

void append_commands_list_b(s32 count, GfxCommand *src)
{
    CommandLists *lists = &gRenderLists->lists;

    while (count--) {
        *lists->listB++ = *src++;
    }
}
