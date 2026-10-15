#include "types.h"

/* Initialized data at 0x80140014..0x80140018 (ROM 0xD0014..0xD0018). */
typedef struct Data80140014 {
    u32 word0;
} Data80140014;

Data80140014 D_80140014 = {
    0x49CF51CD,
};
