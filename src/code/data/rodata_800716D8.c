#include "types.h"

/* Initialized rodata at 0x800716D8..0x800716E0 (ROM 0x16D8..0x16E0). */
typedef struct Rodata800716D8 {
    u32 word0;
    u32 word4;
} Rodata800716D8;

const Rodata800716D8 D_800716D8 = {
    0x00540045,
    0x0000D04F,
};
