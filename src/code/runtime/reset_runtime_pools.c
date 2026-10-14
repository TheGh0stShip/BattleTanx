#include "types.h"

typedef struct RuntimePools {
    u8 pad0000[0x2680];
    u8 secondaryPool[0x80];
} RuntimePools;

extern s32 gRuntimePoolHead0 __asm__("D_801B6C10");
extern s32 gRuntimePoolHead1 __asm__("D_801B6C14");
extern s32 gRuntimePoolHead2 __asm__("D_801B6C18");
extern s32 gRuntimePoolHead3 __asm__("D_801B6C1C");
extern RuntimePools gRuntimePools __asm__("D_801C0840");
extern s16 gRuntimePoolCount __asm__("D_80125800");
extern u8 gRuntimePoolGeneration __asm__("D_80125802");
extern void clear_memory(void *address, s32 size) __asm__("func_80110C00");

void reset_runtime_pools(void) __asm__("func_800805DC");

void reset_runtime_pools(void)
{
    gRuntimePoolHead0 = 0;
    gRuntimePoolHead1 = 0;
    gRuntimePoolHead2 = 0;
    gRuntimePoolHead3 = 0;
    clear_memory(&gRuntimePools, 0x380);
    clear_memory(gRuntimePools.secondaryPool, 0x80);
    gRuntimePoolCount = 0;
    gRuntimePoolGeneration = (gRuntimePoolGeneration + 1) % 3;
}
