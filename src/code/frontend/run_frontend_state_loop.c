#include "types.h"

typedef struct FrontendSession {
    u8 pad00[4];
    s32 value04;
} FrontendSession;

extern void func_80079064(void);
extern void func_800AB690(void);
extern void func_800AB9FC(s32 previous, s32 next);
extern s32 func_800B850C(void);
extern s32 func_800BC214(void);
extern s32 func_800BFDB4(void);
extern s32 func_800C3534(void);
extern s32 func_800C4AE0(void);
extern s32 func_800D11B0(void);
extern s32 func_800C5848(void);
extern s32 func_800CBDBC(void);
extern s32 func_800C7D74(void);
extern s32 func_800CA398(void);
extern s32 func_800CDFFC(void);
extern s32 func_800DC93C(void);
extern s32 func_800CEE2C(void);
extern s32 func_800D6060(void);
extern s32 func_800D89F4(void);
extern s32 func_800DA9B4(void);
extern s32 func_800AC070(void);
extern u8 gFrontendState __asm__("D_801B4AE0");
extern FrontendSession D_801B4AB0;
extern u8 D_801B4BF8;
extern u8 D_801B4BF9;
extern s32 D_80134E58;

s32 run_frontend_state_loop(void) __asm__("func_8007C344");

s32 run_frontend_state_loop(void) {
    FrontendSession *session;
    s32 previous;

    D_801B4BF9 = 0;
    D_801B4BF8 = 1;
    func_80079064();
    func_800AB690();
    session = &D_801B4AB0;
    while (gFrontendState != 11 && gFrontendState != 13) {
        if (gFrontendState == 20) {
            break;
        }
        previous = gFrontendState;
        switch (previous) {
        case 15:
            gFrontendState = func_800B850C();
            break;
        case 16:
            gFrontendState = func_800BC214();
            break;
        case 17:
            gFrontendState = func_800BFDB4();
            break;
        case 18:
            gFrontendState = func_800C3534();
            break;
        case 19:
            gFrontendState = func_800C4AE0();
            break;
        case 0:
            gFrontendState = func_800D11B0();
            break;
        case 1:
            gFrontendState = func_800C5848();
            break;
        case 2:
            gFrontendState = func_800CBDBC();
            break;
        case 3:
            gFrontendState = func_800C7D74();
            break;
        case 4:
            gFrontendState = func_800CA398();
            break;
        case 5:
            gFrontendState = func_800CDFFC();
            break;
        case 9:
            gFrontendState = func_800DC93C();
            break;
        case 10:
            gFrontendState = func_800CEE2C();
            break;
        case 6:
            gFrontendState = func_800D6060();
            break;
        case 7:
            gFrontendState = func_800D89F4();
            break;
        case 8:
            gFrontendState = func_800DA9B4();
            break;
        case 14:
            gFrontendState = func_800AC070();
            break;
        case 11:
        case 13:
            break;
        case 12:
            gFrontendState = 11;
            break;
        }
        func_800AB9FC(previous, gFrontendState);
    }
    func_80079064();
    D_801B4BF8 = 0;
    session->value04 = D_80134E58;
    if (gFrontendState == 11) {
        return 1;
    }
    return (gFrontendState != 20) * 2;
}
