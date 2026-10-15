#include "types.h"

typedef struct ViewSector {
    f32 value00;
    f32 value04;
    f32 value08;
    f32 value0C;
    f32 value10;
    f32 value14;
    u8 disabled;
    u8 pad19[0x13];
} ViewSector;

typedef struct ViewSectorSet {
    u8 pad000[0x584];
    ViewSector sectors[1];
} ViewSectorSet;

typedef struct Viewport {
    s16 scale[4];
    s16 translate[4];
} Viewport;

typedef struct ViewRecord {
    u8 pad000[0x90];
    f32 view[4][4];
    u8 pad0D0[0x28];
    Viewport *viewport;
    u8 pad0FC[0x4];
    f32 projection[4][4];
} ViewRecord;

extern ViewRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern ViewSectorSet *get_spawn_session(void) __asm__("func_800821C0");
extern void matrix_multiply(f32 first[4][4], f32 second[4][4], f32 output[4][4]) __asm__("func_800A7F3C");
extern void transform_point(f32 matrix[4][4], f32 *in, f32 *out) __asm__("func_800A7DBC");

static inline s32 classify_view_sector(f32 x, f32 y, ViewSector *c) {
    f32 dx;
    f32 dy;
    f32 a;
    f32 b;

    if (c->disabled != 0) {
        return 0;
    }
    dy = y + c->value14;
    dx = x + c->value10;
    a = c->value00 * dy + c->value04 * dx;
    b = c->value08 * dx - c->value0C * dy;
    if (a <= 0.0f) {
        return (b > 0.0f) ? 1 : 2;
    }
    if (b > 0.0f) {
        if (b < a) {
            return 0;
        }
    } else {
        if (-b < a) {
            return 0;
        }
    }
    return (b > 0.0f) ? 1 : 2;
}

s32 project_point_to_screen(f32 *point, f32 *screen, s32 index) __asm__("func_8009453C");
s32 project_point_to_screen(f32 *point, f32 *screen, s32 index) {
    ViewRecord *record = get_entity_record(index);
    s32 result;
    f32 matrix[4][4];
    Viewport *viewport;

    if (record->viewport == 0) {
        return -1;
    }
    result = classify_view_sector(point[0], point[2], &get_spawn_session()->sectors[index]);
    if (result != 0) {
        return result;
    }
    matrix_multiply(record->view, record->projection, matrix);
    transform_point(matrix, point, screen);
    viewport = record->viewport;
    screen[0] = (screen[0] * viewport->scale[0] + viewport->translate[0]) / 4.0f;
    viewport = record->viewport;
    screen[1] = (screen[1] * -viewport->scale[1] + viewport->translate[1]) / 4.0f;
    return 0;
}
