#include "types.h"

void __osSpSetStatus(u32 status) {
    *(volatile u32*)0xA4040010 = status;
}
