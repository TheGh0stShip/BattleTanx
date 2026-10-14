#include "types.h"

extern s32 D_80137900;
extern s32 D_8033B604;
extern s32 D_8033B608;

s32 get_runtime_partition_mode(void) __asm__("func_800EC644");
s32 get_runtime_partition_stride(void) __asm__("func_800EC654");
s32 get_runtime_partition_count(s32 partition) __asm__("func_800EC668");
s32 runtime_partition_local_to_global(s32 partition, s32 localIndex) __asm__("func_800EC6BC");

s32 get_runtime_partition_mode(void)
{
    return D_80137900;
}

s32 get_runtime_partition_stride(void)
{
    return (D_80137900 != 0) * 2;
}

s32 get_runtime_partition_count(s32 partition)
{
    if (D_80137900 == 0) {
        return 0;
    }
    switch (partition) {
    case 0:
        return D_8033B608;
    case 1:
        return D_8033B604 - D_8033B608;
    default:
        return 0;
    }
}

s32 runtime_partition_local_to_global(s32 partition, s32 localIndex)
{
    if (D_80137900 == 0) {
        return 0;
    }
    switch (partition) {
    case 0:
        return localIndex;
    case 1:
        return localIndex + D_8033B608;
    default:
        return 0;
    }
}
