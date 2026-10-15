#include "types.h"

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct SpawnEntity {
    u8 flags;
    u8 pad01[3];
    s32 state;
    u8 pad08[0x40];
    f32 value48;
    f32 value4C;
    u8 pad50[2];
    s16 value52;
    u16 value54;
    u8 pad56[2];
} SpawnEntity;

typedef struct SpawnSession {
    u8 pad000[0x568];
    SpawnEntity *entities;
} SpawnSession;

typedef struct GateObject {
    u8 pad00[0xC];
    u8 flags;
    u8 pad0D[3];
    f32 value10;
    f32 value14;
    u16 value18;
    u8 pad1A[2];
    s32 area;
    s32 entity;
    u8 pad24[0xA];
    s16 value2E;
    u16 value30;
    s16 value32;
    u16 value34;
} GateObject;

extern SpawnSession *get_spawn_session(void) __asm__("func_800821C0");
extern void func_80090428(s16 id, Vec3 *position, s32 arg2, u16 arg3, s32 arg4, s32 arg5, s32 arg6);
extern void func_800905D8(s16 id, Vec3 *position, s32 arg2, u16 arg3, s32 arg4, s32 arg5, s32 arg6);
extern void func_80107170(s32 area);
extern void func_80085B4C(s32 kind, f32 x, f32 z);
extern void func_800ED8C0(Vec3 *position, s32 kind);
extern void clear_record_halfword_flags(s32 index, s32 flags) __asm__("func_80106CCC");

void update_gate_object(GateObject *object, s32 *result) __asm__("func_800F03B4");

void update_gate_object(GateObject *object, s32 *result) {
    GateObject *self = object;
    SpawnSession *session;
    SpawnEntity *entity;
    Vec3 position;
    Vec3 effect;

    if (object->flags & 2) {
        entity = &get_spawn_session()->entities[object->entity];
        position.x = entity->value4C;
        position.y = 0;
        position.z = entity->value48;
        if (object->flags & 8) {
            func_80090428(object->value2E, &position, 0, object->value18, 0, object->value34, entity->flags & 0xF);
        } else {
            func_800905D8(object->value2E, &position, 0, object->value18, 0, entity->flags & 0xF, 0);
        }
        entity->flags &= 0xF;
        func_80107170(self->area);
        *result = 2;
        return;
    }
    if (object->value32 == 0) {
        func_80085B4C(2, object->value14, object->value10);
        effect.x = object->value14;
        effect.y = 0;
        effect.z = object->value10;
        func_800ED8C0(&effect, 7);
    }
    if (++object->value32 >= 15) {
        SpawnEntity *target;
        SpawnEntity *slot;

        session = get_spawn_session();
        target = &session->entities[object->entity];

        if (target->value52 != -1) {
            u16 value = object->value30;

            target->state = 0x1C;
            target->value54 = value;
        }
        session = get_spawn_session();
        session->entities[object->entity].flags |= 0xF0;
        if ((session->entities[object->entity].flags & 0xF) == 0xF) {
            session->entities[object->entity].flags &= 0xF0;
        }
        clear_record_halfword_flags(object->area, 4);
        object->flags &= ~4;
        *result = 1;
    }
}
