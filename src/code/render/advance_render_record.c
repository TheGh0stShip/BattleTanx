#include "types.h"
typedef struct RenderState { u8 pad00[0xD0]; u16 current; u8 padD2[2]; s32 pending; } RenderState;
extern RenderState *D_801257D0;
s32 advance_render_record(void) __asm__("func_8007F040");
s32 advance_render_record(void) { s32 pending = D_801257D0->pending; D_801257D0->pending = 0; D_801257D0->current ^= 1; return pending; }
