#include "types.h"

/* Initialized rodata at 0x80072018..0x80072030 (ROM 0x2018..0x2030). */
typedef struct Rodata80072018 {
    u32 word0;
    u32 word4;
    f64 value8;
    f64 value10;
} Rodata80072018;

const Rodata80072018 D_80072018 = {
    0x00D308E0,
    0x0266E454,
    1.5,
    1.5,
};
