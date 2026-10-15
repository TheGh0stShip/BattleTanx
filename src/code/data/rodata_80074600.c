#include "types.h"

/* Initialized rodata at 0x80074600..0x80074650 (ROM 0x4600..0x4650). */
typedef struct Rodata80074600 {
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
    f32 value28;
    f32 value2C;
    f32 value30;
    f32 value34;
    f32 value38;
    f32 value3C;
    f32 value40;
    f32 value44;
    f32 value48;
    f32 value4C;
} Rodata80074600;

const Rodata80074600 D_80074600 = {
    0x800E36D0,
    0x800E36D0,
    0x800E36D0,
    0x800E36D0,
    0x800E36D0,
    0x800E3698,
    0x800E36BC,
    0x800E36BC,
    0x800E36BC,
    0x800E36D0,
    2.0f,
    5.0f,
    1.00000001e-10f,
    3.9999999e-05f,
    16000.0f,
    0.600000024f,
    0.400000006f,
    1.40740206e+14f,
    -1.09417963f,
    4.04264262e-34f,
};
