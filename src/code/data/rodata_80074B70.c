#include "types.h"

/* Initialized rodata at 0x80074B70..0x80074BB8 (ROM 0x4B70..0x4BB8). */
typedef struct Rodata80074B70 {
    u32 word0;
    u32 word4;
    u32 word8;
    u32 wordC;
    u32 word10;
    u32 word14;
    u32 word18;
    u32 word1C;
    u32 word20;
    u32 word24;
    u32 word28;
    u32 word2C;
    u32 word30;
    u32 word34;
    u32 word38;
    u32 word3C;
    u32 word40;
    u32 word44;
} Rodata80074B70;

const Rodata80074B70 D_80074B70 = {
    0x3F800000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x3F800000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x3F800000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x3F800000,
    0x00000000,
    0x00000000,
};
