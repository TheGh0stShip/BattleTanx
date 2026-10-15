#include "types.h"

typedef struct SessionState {
    s32 value00;
    s32 value04;
    s8 value08;
    u8 pad09[0x3];
    s32 value0C;
    s32 value10;
    s16 value14;
    s8 value16;
} SessionState;

extern s32 func_800DD544(u8 *code, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, s32 *arg5);
extern SessionState *D_80134E78;
extern u8 D_80328430[];
extern u8 D_8032843A;
extern s32 D_80328440;
extern u8 D_80135698[14][10];
extern u8 D_80135760;
extern u8 D_80135761;
extern u8 D_80135763;
extern u8 D_80135765;
extern u8 D_80135767;
extern u8 D_8013576A;
extern u8 D_8013576B;
extern u8 D_80135770;
extern u8 D_80135771;
extern u8 D_80135772;
extern u8 D_80135773;
extern u8 D_80135774;
extern u8 D_80135775;
extern u8 D_80135776;
extern u8 D_8012579A;

void check_entered_password(void) __asm__("func_800DCA7C");

void check_entered_password(void) {
    s32 value0;
    s32 value1;
    s32 value2;
    s32 value3;
    s32 value4;
    s32 i;
    s32 j;

    if (func_800DD544(D_80328430, &value0, &value1, &value2, &value3, &value4)) {
        D_8032843A = 1;
        D_80328440 = 14;
        D_80134E78->value08 = value0;
        D_80134E78->value0C = value2;
        D_80134E78->value16 = value4;
        D_80135774 = 1;
        D_80134E78->value14 = value1;
        D_80134E78->value10 = value3;
        return;
    }
    for (i = 0; i < 14; i++) {
        for (j = 0; j < 10; j++) {
            if (D_80135698[i][j] != D_80328430[j]) {
                break;
            }
            if (j == 9) {
                D_8032843A = 1;
                switch (i) {
                case 0:
                    D_80135760 = 1;
                    break;
                case 1:
                    D_80135765 = 1;
                    break;
                case 2:
                    D_80135763 = 1;
                    break;
                case 3:
                    D_80135760 = 1;
                    D_80135763 = 1;
                    D_80135767 = 1;
                    D_80135761 = 1;
                    break;
                case 4:
                    D_8013576A = 1;
                    break;
                case 5:
                    D_8013576B = 1;
                    break;
                case 6:
                    D_8012579A = 1;
                    D_80135773 = 1;
                    break;
                case 7:
                    D_80135770 = 1;
                    break;
                case 8:
                    D_80135771 = 1;
                    break;
                case 9:
                    D_80135772 = 1;
                    break;
                case 10:
                    D_8012579A = 1;
                    break;
                case 11:
                    D_80135775 = 1;
                    break;
                case 12:
                    D_80135776 = 1;
                    break;
                default:
                    D_8032843A = 0;
                    break;
                }
                D_80328440 = i + 1;
                return;
            }
        }
    }
    D_80328440 = 0;
}
