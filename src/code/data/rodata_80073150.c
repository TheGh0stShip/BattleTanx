#include "types.h"

/* Initialized rodata at 0x80073150..0x80073210 (ROM 0x3150..0x3210). */
typedef struct Rodata80073150 {
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
    f32 value44;
    u32 word48;
    u32 word4C;
    u32 word50;
    u32 word54;
    u32 word58;
    u32 word5C;
    char text60[14];
    u8 pad6E[2];
    char text70[12];
    char text7C[12];
    f32 value88;
    f32 value8C;
    f32 value90;
    f32 value94;
    f32 value98;
    f32 value9C;
    f32 valueA0;
    f32 valueA4;
    f32 valueA8;
    f32 valueAC;
    f32 valueB0;
    f32 valueB4;
    f32 valueB8;
    f32 valueBC;
} Rodata80073150;

const Rodata80073150 D_80073150 = {
    0x800ABB28,
    0x800ABB48,
    0x800ABB58,
    0x800ABB68,
    0x800ABB78,
    0x00000000,
    0x800ABBCC,
    0x800ABBEC,
    0x800ABBFC,
    0x800ABC0C,
    0x800ABC1C,
    0x00000000,
    0x800ABD04,
    0x800ABD1C,
    0x800ABD34,
    0x800ABD4C,
    0x800ABD64,
    1.0f,
    0x800ABDC8,
    0x800ABDE0,
    0x800ABDF8,
    0x800ABE10,
    0x800ABE28,
    0x00A2F8FF,
    "No Controller\000",
    { 0xBE, 0x73 },
    "\"THE FALL\"\000\000",
    "\"AFTERMATH\"\000",
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
};
