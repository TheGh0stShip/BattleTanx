#include "types.h"

typedef struct RuntimeFlagRecord {
    u16 flags;
    u8 pad02[0x26];
} RuntimeFlagRecord;

extern RuntimeFlagRecord gRuntimeFlagRecords[] __asm__("D_803B8248");

void clear_record_halfword_flags(s32 index, u16 flags) __asm__("func_80106CCC");

void clear_record_halfword_flags(s32 index, u16 flags)
{
    gRuntimeFlagRecords[index].flags &= ~flags;
}
