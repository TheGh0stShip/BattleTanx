#include "types.h"

/* Initialized rodata at 0x80075948..0x80075950 (ROM 0x5948..0x5950). */
typedef struct Rodata80075948 {
    u32 word0;
    u32 word4;
} Rodata80075948;

const Rodata80075948 D_80075948 = {
    0x00470000,
    0xD2470008,
};
