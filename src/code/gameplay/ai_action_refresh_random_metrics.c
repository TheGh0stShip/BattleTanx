#include "types.h"

#ifndef NULL
#define NULL 0
#endif

s32 func_800E7320();
s32 func_800E7340(s32);
s32 func_800E7360(s32);
s32 func_800E7380(s32);

s32 ai_action_refresh_random_metrics(s32 arg0) __asm__("func_800EB2CC");

s32 ai_action_refresh_random_metrics(s32 arg0) {
    func_800E7320();
    func_800E7340(arg0);
    func_800E7360(arg0);
    func_800E7380(arg0);
    return -1;
}
