#include "types.h"
extern volatile s32 D_801257A0;
extern volatile s32 D_801257A4;
s32 read_runtime_counter_pair(void) __asm__("func_8007B268");
s32 read_runtime_counter_pair(void) { s32 first = D_801257A0; (void)D_801257A4; return first; }
