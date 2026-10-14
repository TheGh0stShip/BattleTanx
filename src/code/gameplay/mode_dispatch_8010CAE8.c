#include "types.h"

typedef struct ModeObject {
    u8 pad00[0xC];
    u32 value0C;
} ModeObject;

extern s32 func_8007DBC4(void) __asm__("func_8007DBC4");
extern void func_8010BFDC(ModeObject *obj) __asm__("func_8010BFDC");
extern void func_8010C450(void *obj) __asm__("func_8010C450");

void mode_object_dispatch(ModeObject *obj) __asm__("func_8010CAE8");

void mode_object_dispatch(ModeObject *obj) {
    void *other = obj;

    if (func_8007DBC4() == 0) {
        if (obj->value0C < 2) {
            func_8010BFDC(obj);
        } else {
            func_8010C450(other);
        }
    }
}
