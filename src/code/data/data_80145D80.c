#include "types.h"

/* Initialized data at 0x80145D80..0x80145DA0 (ROM 0xD5D80..0xD5DA0). */
typedef struct Data80145D80 {
    u32 word0;
    u32 word4;
    u32 word8;
    u32 wordC;
    u32 word10;
    u32 word14;
    u32 word18;
    u32 word1C;
} Data80145D80;

Data80145D80 D_80145D80 = {
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
};
