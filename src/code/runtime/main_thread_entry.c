#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_8007AA70(s32);
s32 func_80111510(s32 *, s32 *, s32);
extern s32 D_8014C090;
extern s32 D_8014C0B0;

void main_thread_entry(void) __asm__("func_80077AD0");

void main_thread_entry(void) {
    func_80111510(&D_8014C0B0, &D_8014C090, 8);
    func_8007AA70(2);
}
