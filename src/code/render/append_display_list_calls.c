#include "types.h"
typedef struct Gfx { u32 w0; u32 w1; } Gfx;
typedef struct RenderState { u8 pad00[0xD8]; Gfx *lists[3]; } RenderState;
extern RenderState *D_801257D0;
void append_display_list_call_0(void *displayList) __asm__("func_8007EEF8");
void append_display_list_call_1(void *displayList) __asm__("func_8007EF1C");
void append_display_list_call_2(void *displayList) __asm__("func_8007EF40");
void append_display_list_call_0(void *displayList) { Gfx *cmd = D_801257D0->lists[0]++; cmd->w0 = 0x06000000; cmd->w1 = (u32)displayList; }
void append_display_list_call_1(void *displayList) { Gfx *cmd = D_801257D0->lists[1]++; cmd->w0 = 0x06000000; cmd->w1 = (u32)displayList; }
void append_display_list_call_2(void *displayList) { Gfx *cmd = D_801257D0->lists[2]++; cmd->w0 = 0x06000000; cmd->w1 = (u32)displayList; }
