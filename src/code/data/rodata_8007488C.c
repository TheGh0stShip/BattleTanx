#include "types.h"

/* Initialized rodata at 0x8007488C..0x800748E4 (ROM 0x488C..0x48E4). */
typedef struct Rodata8007488C {
    f32 value0;
    f32 value4;
    f32 value8;
    f32 valueC;
    f32 value10;
    f32 value14;
    f32 value18;
    f32 value1C;
    char text20[12];
    char text2C[8];
    char text34[8];
    char text3C[12];
    char text48[8];
    char text50[8];
} Rodata8007488C;

const Rodata8007488C D_8007488C = {
    9000.0f,
    1.0f,
    9000.0f,
    1.0f,
    9000.0f,
    1.0f,
    0.5f,
    1.0f,
    "THAT PLAY\000\000\000",
    "RETREAT\000",
    "CHARGE\000\000",
    "EAI TWIST\000\000\000",
    "PANIC\000\000\000",
    "NO PLAY\000",
};
