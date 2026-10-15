#include "types.h"

/* Initialized rodata at 0x800710D4..0x800710E0 (ROM 0x10D4..0x10E0). */
typedef struct Rodata800710D4 {
    u32 word0;
    u32 word4;
    u32 word8;
} Rodata800710D4;

const Rodata800710D4 D_800710D4 = {
    0x470000D1,
    0x13E03F10,
    0xE8550047,
};
