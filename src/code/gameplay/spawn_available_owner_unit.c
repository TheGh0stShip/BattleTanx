#include "types.h"
typedef struct { s16 v[12]; } AreaBox;
typedef struct { u8 pad00[8]; s32 kind; } AreaObject;
typedef struct { u8 pad00[4]; s32 value04; u8 pad08[6]; u8 value0E; } Linked;
typedef struct { s16 units[5]; u8 pad0A[0x19]; u8 flags23; } Owner;
typedef struct { u8 pad00[1]; u8 value01; } Unit;
typedef struct {
    u8 pad00[0xD]; u8 ownerId; u8 pad0E[2]; s32 mode; s16 interval; u8 pad16[2]; s32 lastTick;
    f32 x; f32 y; u16 angle; u8 pad26[2]; Linked *linked; s32 value2C; u8 value30; u8 value31;
} Spawner;
extern Owner *get_entity_record(u16 index) __asm__("func_800A6688");
extern void start_cooldown_timed_event(void *owner, s32 event, f32 duration) __asm__("func_800A51E8");
extern u32 next_random_u32(void) __asm__("func_800F38F4");
extern s32 func_800A4D10(void *);
extern void decrement_countdown(void *) __asm__("func_800A4D1C");
extern void build_area_box_by_shape(f32 x, f32 y, u16 flags, u32 shape, AreaBox *box, f32 scale) __asm__("func_80096E80");
extern u8 func_80107A14(AreaBox *box, s32 capacity, AreaObject **results, s32 *count);
extern Unit *get_unit(s16 id) __asm__("func_800A03B8");
extern void func_8009FA70(s16, u8, f32 *, s32, s32, s32, s32);
extern void (*D_802C393C)(AreaObject *, Spawner *, s32, s32, s32);
extern void (*D_802C393C_again)(AreaObject *, Spawner *, s32, s32, s32)
    __asm__("D_802C393C");
extern f32 D_800755B0;
extern s32 D_801B4AA8;
void spawn_available_owner_unit(Spawner *sp, s32 *out) __asm__("func_8010D59C");
void spawn_available_owner_unit(Spawner *sp, s32 *out) {
    Owner *owner = get_entity_record(sp->ownerId);
    Linked *linked = sp->linked;
    s32 shape;
    AreaObject *results[16];
    AreaBox box;
    s32 count;
    s32 i;
    s16 *unit;

    if (linked != 0) {
        if (linked->value04 != sp->value2C) {
            *out = 2;
            return;
        }
        if (linked->value0E != 0) {
            start_cooldown_timed_event(get_entity_record(0), 0x22, 3.0f);
            *out = 2;
            return;
        }
    }
    if ((sp->value30 == 0x45 || sp->value31 == 1) && !(owner->flags23 & 1)) return;
    if (sp->lastTick + sp->interval >= D_801B4AA8) return;
    if (next_random_u32() & 0xF) return;
    shape = 0;
    if (!(func_800A4D10(owner) & 0xFF)) return;
    switch ((u32)sp->mode) {
    case 1:
        shape = 1;
        break;
    case 0:
        break;
    case 2:
        shape = 2;
        break;
    case 3:
        shape = (next_random_u32() & 1) ? 2 : 2;
        break;
    }
    build_area_box_by_shape(sp->x, sp->y, sp->angle + 0x200, shape, &box, D_800755B0);
    if (func_80107A14(&box, 16, results, &count) & 0xFF) {
        for (i = 0; i < count; i++) {
            AreaObject *o = results[i];
            if ((u32)o < 4) continue;
            if (o->kind == 5) {
                goto check_linked;
            }
            if (o->kind != 0x1A) {
                return;
            }
            if (D_802C393C != 0) {
                D_802C393C_again(results[i], sp, 4, 0, 0);
            }
            goto next_result;
check_linked:
            if (o != (AreaObject *)sp->linked) {
                return;
            }
next_result:
            ;
        }
    }
    unit = owner->units;
    for (i = 0; i < 5; i++, unit++) {
        if (get_unit(*unit)->value01 == 0) {
            func_8009FA70(*unit, sp->ownerId, &sp->x, shape, sp->value30, 0, 1);
            sp->lastTick = D_801B4AA8;
            decrement_countdown(owner);
            return;
        }
    }
}
