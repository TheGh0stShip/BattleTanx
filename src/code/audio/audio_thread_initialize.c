#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_80079DC8();
s32 func_80079EFC();
s32 func_80079FA4();
s32 func_8007A004();
s32 func_8007A178();
s32 func_8007A26C();
s32 func_8007A36C();
s32 func_8011D1A0(s32 *);
extern s32 D_80125768;
extern s32 D_8012576C;
extern s32 D_80125770;
extern s32 D_80152A38;

void audio_thread_initialize(void) __asm__("func_80079B08");

void audio_thread_initialize(void) {
    D_80125768 = 0;
    D_8012576C = 0;
    D_80125770 = 0;
    func_80079DC8();
    func_8007A004();
    func_8007A178();
    func_8007A26C();
    func_8007A36C();
    func_80079EFC();
    func_80079FA4();
    func_8011D1A0(&D_80152A38);
}
