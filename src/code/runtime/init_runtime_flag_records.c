#include "types.h"

typedef struct RuntimeFlagRecord {
    u16 flags;
    s16 next;
    s16 prev;
    u8 pad06[0x18];
    s16 value1E;
    s16 value20;
    s16 value22;
    s16 value24;
    u8 pad26[2];
} RuntimeFlagRecord;

extern void bzero(void *buffer, s32 size) __asm__("func_80110C00");
extern RuntimeFlagRecord gRuntimeFlagRecords[0x514] __asm__("D_803B8248");
extern s16 D_803B75B0[0x640];
extern s16 D_803B8230;
extern s32 D_803B8234;
extern s32 D_803B8238;
extern s32 D_803B823C;
extern s32 D_803B8240;

void init_runtime_flag_records(s32 width, s32 height) __asm__("func_80106B60");

void init_runtime_flag_records(s32 width, s32 height)
{
    u32 i;

    bzero(gRuntimeFlagRecords, sizeof(gRuntimeFlagRecords));
    for (i = 0; i < 0x514; i++) {
        gRuntimeFlagRecords[i].value1E = -1;
        gRuntimeFlagRecords[i].value20 = -1;
        gRuntimeFlagRecords[i].value22 = -1;
        gRuntimeFlagRecords[i].value24 = -1;
    }
    for (i = 0; i < 0x513; i++) {
        gRuntimeFlagRecords[i].next = i + 1;
        gRuntimeFlagRecords[i].prev = i - 1;
    }
    gRuntimeFlagRecords[0x513].next = -1;
    gRuntimeFlagRecords[0].prev = -1;
    D_803B8240 = -1;
    D_803B8238 = width + 0x1F4;
    D_803B8234 = 0;
    D_803B823C = height + 0x1F4;
    for (i = 0; i < 0x640; i++) {
        D_803B75B0[i] = -1;
    }
    D_803B8230 = -1;
}
