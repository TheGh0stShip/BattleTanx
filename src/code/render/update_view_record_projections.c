#include "types.h"

typedef struct PerspectiveMtx {
    s32 m[4][4];
} PerspectiveMtx;

typedef struct ViewRecord {
    u8 pad000[0x16];
    u16 value16;
    u8 pad018[0xDC];
    u8 *valueF4;
    u8 pad0F8[4];
    u16 perspNorm;
    u8 pad0FE[2];
    PerspectiveMtx projection;
} ViewRecord;

typedef struct GameModeState {
    u8 pad000[0x1CC];
    s32 value1CC;
} GameModeState;

extern u8 D_010001E0[];
extern GameModeState *get_game_mode(void) __asm__("func_8007AAF4");
extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern ViewRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern void guPerspective(PerspectiveMtx *m, u16 *perspNorm, f32 fovy, f32 aspect, f32 near, f32 far,
                          f32 scale) __asm__("func_80114970");

void update_view_record_projections(s32 far) __asm__("func_800A5EB0");

void update_view_record_projections(s32 far)
{
    GameModeState *mode;
    ViewRecord *rec;
    s32 i;
    f32 aspect;

    mode = get_game_mode();
    for (i = 0; i < get_difficulty_level(); i++) {
        rec = get_entity_record(i);
        if (rec->valueF4 == 0) {
            continue;
        }
        if (rec->valueF4 == D_010001E0) {
            aspect = 2.1913044f;
        } else if (mode->value1CC == 2 || (mode->value1CC == 3 && rec->value16 == 0)) {
            aspect = 2.6666667f;
        } else {
            aspect = 1.3333334f;
        }
        guPerspective(&rec->projection, &rec->perspNorm, 37.0f, aspect, 16.0f, (f32)far, 1.0f);
    }
}
