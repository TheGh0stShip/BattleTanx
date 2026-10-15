#include "types.h"

/* Initialized rodata at 0x800744DC..0x800744E8 (ROM 0x44DC..0x44E8). */
typedef struct Rodata800744DC {
    u32 word0;
    f32 value4;
    f32 value8;
} Rodata800744DC;

const Rodata800744DC D_800744DC = {
    0x00D11480,
    40.0f,
    40.0f,
};
