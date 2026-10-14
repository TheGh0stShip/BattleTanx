#include "types.h"
typedef struct RenderRecord { u8 bytes[0x18]; } RenderRecord;
typedef struct RenderState { u8 pad00[0x90]; RenderRecord records[2]; u8 padC0[0x10]; u16 current; } RenderState;
extern RenderState *D_801257D0;
RenderRecord *get_current_render_record(void) __asm__("func_8007F00C");
RenderRecord *get_current_render_record(void) { return &D_801257D0->records[D_801257D0->current]; }
