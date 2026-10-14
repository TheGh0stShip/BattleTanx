#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

typedef struct MatrixSlot {
    u8 pad00[0x14];
    u32 address;
} MatrixSlot;

typedef struct RenderLists {
    u8 pad00[0x90];
    MatrixSlot slots[2];
    u8 padC0[0x10];
    u16 currentSlot;
    u8 padD2[0x6];
    GfxCommand *listA;
    GfxCommand *listB;
} RenderLists;

/* F3DEX G_MTX: opcode 0x01, parameter byte, 0x40-byte matrix. */
#define GFX_MATRIX_WORD(params) ((((params) & 0xFF) << 16) | 0x01000040)
#define GFX_SEGMENT_ADDRESS(address) ((address) - 0x80000000)

extern RenderLists *gRenderLists __asm__("D_801257D0");

u32 load_current_matrix_list_a(s32 params) __asm__("func_8007EAA4");

u32 load_current_matrix_list_a(s32 params)
{
    GfxCommand *command;
    MatrixSlot *slot;

    command = gRenderLists->listA++;
    slot = &gRenderLists->slots[gRenderLists->currentSlot];
    command->w0 = GFX_MATRIX_WORD(params);
    command->w1 = GFX_SEGMENT_ADDRESS(slot->address);
    return slot->address;
}
