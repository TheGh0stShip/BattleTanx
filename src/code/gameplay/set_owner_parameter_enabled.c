#include "types.h"

typedef struct OwnerParameterState {
    u8 pad000[0x364];
    s32 enabledTime;
} OwnerParameterState;

extern void func_800E986C(OwnerParameterState *owner, s32 key, u32 value);
extern s32 get_frame_time(void) __asm__("func_8007B1DC");

void set_owner_parameter_enabled(OwnerParameterState *owner, s32 enabled) __asm__("func_800E5A70");

void set_owner_parameter_enabled(OwnerParameterState *owner, s32 enabled)
{
    if (enabled != 0) {
        register u32 value __asm__("$6") = 0x3F800000;
        register s32 key __asm__("$5");

        __asm__ volatile("" : "=r"(value) : "0"(value));
        key = 0x1002;
        func_800E986C(owner, key, value);
        owner->enabledTime = get_frame_time();
    }
}
