#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

typedef struct RenderLists {
    u8 pad00[0xD8];
    GfxCommand *listA;
    GfxCommand *listB;
} RenderLists;

/* F3DEX G_MTX: opcode 0x01, parameter byte, 0x40-byte matrix. */
#define GFX_MATRIX_WORD(params) ((((params) & 0xFF) << 16) | 0x01000040)
#define GFX_SEGMENT_ADDRESS(address) ((address) - 0x80000000)

extern RenderLists *gRenderLists __asm__("D_801257D0");

void load_matrix_list_a(u32 address, s32 params) __asm__("func_8007EB64");
void load_matrix_list_a_copy(u32 address, s32 params) __asm__("func_8007EBA0");

void load_matrix_list_a(u32 address, s32 params)
{
    GfxCommand *command;

    command = gRenderLists->listA++;
    command->w0 = GFX_MATRIX_WORD(params);
    command->w1 = GFX_SEGMENT_ADDRESS(address);
}

void load_matrix_list_a_copy(u32 address, s32 params)
{
    GfxCommand *command;

    command = gRenderLists->listA++;
    command->w0 = GFX_MATRIX_WORD(params);
    command->w1 = GFX_SEGMENT_ADDRESS(address);
}
