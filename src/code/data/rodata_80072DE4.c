#include "types.h"

/* Initialized rodata at 0x80072DE4..0x80072E20 (ROM 0x2DE4..0x2E20). */
typedef struct Rodata80072DE4 {
    f32 value0;
    u32 word4;
    f32 value8;
    f32 valueC;
    f32 value10;
    f32 value14;
    char text18[12];
    char text24[12];
    char text30[12];
} Rodata80072DE4;

const Rodata80072DE4 D_80072DE4 = {
    30.0f,
    0x25730000,
    30.0f,
    1.0f,
    1.0f,
    1.0f,
    "%d KILL%c\000\000\000",
    "%d POINTS\000\000\000",
    "BONUS TANK\000\000",
};
