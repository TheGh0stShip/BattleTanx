#include "types.h"

typedef struct DemoHeader {
    s32 frameCount;
    s32 objectCount;
    s32 value08;
    s32 trailerCount;
    s32 value10;
    s32 value14;
} DemoHeader;

typedef struct DemoEvent {
    s16 frame;
    u8 type;
    u8 arg;
    s32 x;
    s32 z;
} DemoEvent;

typedef struct DemoPoint {
    f32 x;
    s32 y;
    f32 z;
} DemoPoint;

extern void set_screen_fade(s32 red, s32 green, s32 blue, u8 alpha, s32 arg4) __asm__("func_8008054C");
extern void func_800ED8C0(DemoPoint *point, s32 kind);
extern void func_80085B4C(s32 kind, f32 x, f32 z);

extern s32 gDemoActive __asm__("D_80137900");
extern s32 D_80137908;
extern DemoHeader gDemoHeader __asm__("D_8033B600");
extern s32 gDemoFrame __asm__("D_8033B5F0");
extern s32 gDemoFrameSize __asm__("D_8033B5F4");
extern u8 *gDemoData __asm__("D_8033B618");
extern u8 *gDemoCursor __asm__("D_8033B61C");
extern DemoEvent *gDemoTrailer __asm__("D_8033B620");
extern s32 gDemoTrailerIndex __asm__("D_8033B624");
extern s32 gDemoTrailerTarget __asm__("D_8033B628");
extern s32 gDemoFadeRate __asm__("D_8033B62C");

s32 advance_demo_frame(void) __asm__("func_800EC8C4");

s32 advance_demo_frame(void) {
    DemoPoint point;
    s32 alpha;

    if (gDemoActive == 0) {
        return 0;
    }
    if (gDemoFrame == gDemoHeader.frameCount - 1) {
        gDemoActive = 0;
        return -1;
    }
    gDemoFrame++;
    if (gDemoFrame == gDemoHeader.frameCount - 20) {
        gDemoTrailerTarget = gDemoFrame;
        gDemoFadeRate = 16;
    }
    if (gDemoTrailerTarget >= 0) {
        alpha = (gDemoFrame - gDemoTrailerTarget) * gDemoFadeRate;
        if (gDemoFadeRate * 3 + 255 < alpha) {
            set_screen_fade(0, 0, 0, 255, 0);
            gDemoActive = 0;
            return -1;
        }
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
        set_screen_fade(0, 0, 0, alpha, 0);
    }
    if (gDemoTrailerIndex >= 0) {
        if (gDemoTrailer[gDemoTrailerIndex].frame == gDemoFrame - 1) {
            gDemoTrailerIndex++;
            if (gDemoTrailerIndex == gDemoHeader.trailerCount) {
                gDemoTrailerIndex = -1;
            }
        }
        if (gDemoTrailerIndex >= 0 && gDemoTrailer[gDemoTrailerIndex].frame == gDemoFrame) {
            if (gDemoTrailer[gDemoTrailerIndex].type == 1) {
                point.x = gDemoTrailer[gDemoTrailerIndex].x;
                point.y = 0;
                point.z = gDemoTrailer[gDemoTrailerIndex].z;
                func_800ED8C0(&point, gDemoTrailer[gDemoTrailerIndex].arg);
                if (gDemoTrailer[gDemoTrailerIndex].arg == 13) {
                    func_80085B4C(6, point.x, point.z);
                }
            }
            if (gDemoTrailer[gDemoTrailerIndex].type == 3) {
                D_80137908 = gDemoTrailer[gDemoTrailerIndex].arg;
            }
        }
    }
    gDemoCursor = gDemoData + gDemoFrame * gDemoFrameSize;
    return 0;
}
