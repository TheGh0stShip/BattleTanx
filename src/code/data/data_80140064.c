#include "types.h"

/* Initialized data at 0x80140064..0x80140098 (ROM 0xD0064..0xD0098). */
typedef struct Data80140064 {
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
} Data80140064;

Data80140064 D_80140064 = {
    0x6A4F620F,
    0x51CF51CD,
    0x49CD498D,
    0x418D49CD,
    0x498F49CD,
    0x498F41CD,
    0x49CD498D,
    0x498D51CD,
    0x498F520D,
    0x51CF5A11,
    0x6251620F,
    0x624F620F,
    0x720F720F,
};
