#include "types.h"

/* Initialized rodata at 0x80071C04..0x80071C58 (ROM 0x1C04..0x1C58). */
typedef struct Rodata80071C04 {
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
    u32 word48;
    f32 value4C;
    f32 value50;
} Rodata80071C04;

const Rodata80071C04 D_80071C04 = {
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
    0x3FF00000,
    0x00000000,
    9.0f,
    1.0f,
};
