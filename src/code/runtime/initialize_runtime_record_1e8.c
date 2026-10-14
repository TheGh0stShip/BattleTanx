#include "types.h"

typedef struct RuntimeRecord1E8 {
    u8 pad000[0x1E8];
    s32 field1E8;
    u8 pad1EC[2];
    u16 field1EE;
    u16 field1F0;
    u16 field1F2;
    u16 field1F4;
    u8 pad1F6[2];
    s32 field1F8;
    s32 field1FC;
    s32 field200;
    s32 field204;
} RuntimeRecord1E8;

extern s32 D_801502E0;

void initialize_runtime_record_1e8(RuntimeRecord1E8 *record) __asm__("func_8007902C");

void initialize_runtime_record_1e8(RuntimeRecord1E8 *record)
{
    record->field1E8 = 0;
    record->field1EE = 0;
    record->field1F0 = 0;
    record->field1F2 = 1;
    record->field1F4 = 0;
    record->field1F8 = 0;
    record->field1FC = 0;
    record->field200 = 0;
    record->field204 = 0;
    D_801502E0 = 0;
}
