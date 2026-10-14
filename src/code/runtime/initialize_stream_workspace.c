#include "types.h"
extern s32 D_801C9188;
extern void *D_801C918C;
extern u8 D_801C9190[];
void initialize_stream_workspace(void) __asm__("func_80081A50");
void initialize_stream_workspace(void) { D_801C918C = D_801C9190; D_801C9188 = 0xF8240; }
