#include "types.h"

/* Initialized rodata at 0x80075624..0x80075630 (ROM 0x5624..0x5630). */
typedef struct Rodata80075624 {
    u32 word0;
    u32 word4;
    u32 word8;
} Rodata80075624;

const Rodata80075624 D_80075624 = {
    0xF6620F4E,
    0x34E64200,
    0x4F005900,
};
