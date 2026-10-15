#include "types.h"

typedef struct YawTransform44 {
    f32 m[12];
    s32 value30;
    s32 value34;
    s32 value38;
    s32 value3C;
    s32 value40;
} YawTransform44;

typedef struct ScaledRecord {
    u8 pad00[0xC];
    u8 value0C;
    u8 pad0D[3];
    s32 value10;
    s32 value14;
    u16 value18;
    u8 pad1A[6];
    s32 value20;
    u8 pad24[8];
    s16 value2C;
    u8 pad2E[4];
    s16 value32;
} ScaledRecord;

typedef struct SessionEntry58 {
    u8 value00;
    u8 pad01[0x57];
} SessionEntry58;

typedef struct SpawnSession {
    u8 pad000[0x568];
    SessionEntry58 *value568;
} SpawnSession;

extern YawTransform44 D_80074C30;
extern f32 D_80074C74;
extern f32 D_80074C78;
extern void set_yaw_transform(YawTransform44 *xf, s32 x, s32 y, s32 z, u16 angle) __asm__("func_800A7744");
extern void scale_transform(YawTransform44 *xf, f32 x, f32 y, f32 z) __asm__("func_800A823C");
extern SpawnSession *get_spawn_session(void) __asm__("func_800821C0");
extern void visit_level_points_in_radius(SpawnSession *level, s32 arg1, YawTransform44 *xf, s32 arg3, s32 arg4, s32 *pos) __asm__("func_80084A74");

void visit_level_points_scaled_record(ScaledRecord *rec) __asm__("func_800F0294");

void visit_level_points_scaled_record(ScaledRecord *rec)
{
    YawTransform44 xf;
    SpawnSession *session;
    SessionEntry58 *entry;

    xf = D_80074C30;
    if (rec->value0C & 4) {
        xf.value40 = 0;
        set_yaw_transform(&xf, rec->value14, 0, rec->value10, rec->value18);
        scale_transform(&xf, D_80074C78, (f32)(0x11 - rec->value32) / D_80074C74, D_80074C78);
        session = get_spawn_session();
        entry = &session->value568[rec->value20];
        visit_level_points_in_radius(session, rec->value2C, &xf, 3, entry->value00 & 0xF, &rec->value10);
    }
}
