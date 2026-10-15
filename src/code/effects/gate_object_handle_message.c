#include "types.h"

typedef struct SpawnEntity {
    u8 flags;
    u8 pad01[0x57];
} SpawnEntity;

typedef struct SpawnSession {
    u8 pad000[0x568];
    SpawnEntity *entities;
} SpawnSession;

typedef struct HitUnit {
    u8 pad000[0x3D0];
    f32 value3D0;
    f32 value3D4;
} HitUnit;

typedef struct Message {
    u8 pad00[8];
    u32 type;
    HitUnit *unit;
    s32 now;
} Message;

typedef struct GateObject {
    u8 pad00[0xC];
    u8 flags;
    u8 pad0D[0xF];
    s32 area;
    s32 entity;
    s32 hits;
    s32 lastTime;
    u8 pad2C[6];
    s16 value32;
} GateObject;

extern SpawnSession *get_spawn_session(void) __asm__("func_800821C0");
extern void func_8008B89C(GateObject *object);
extern void clear_record_halfword_flags(s32 index, s32 flags) __asm__("func_80106CCC");
extern s32 gGameTicks __asm__("D_801B4AA8");

static inline void release_gate_entity(GateObject *object) {
    SpawnEntity *entity = &get_spawn_session()->entities[object->entity];

    if ((entity->flags & 0xF) == 0xF) {
        entity->flags &= 0xF0;
    }
    func_8008B89C(object);
}

void gate_object_handle_message(GateObject *object, Message *message, s32 arg2, s32 *result) __asm__("func_800F0738");

void gate_object_handle_message(GateObject *object, Message *message, s32 arg2, s32 *result) {
    HitUnit *unit;
    s32 now;

    switch (message->type) {
    case 2:
    case 12:
    case 22:
    case 34:
        if (object->flags & 4) {
            break;
        }
        object->flags |= 2;
        release_gate_entity(object);
        *result = 0;
        break;
    case 0:
        if (object->hits != 0) {
            unit = message->unit;
            unit->value3D0 -= 6.0;
            if (object->hits & 1) {
                unit->value3D4 -= 2.0f;
            } else {
                unit->value3D4 += 2.0f;
            }
            object->hits--;
            if (object->hits == 0) {
                clear_record_halfword_flags(object->area, 0x10);
            }
            *result = 0;
            break;
        }
        if (object->value32 == 0) {
            release_gate_entity(object);
            object->flags |= 4;
            get_spawn_session()->entities[object->entity].flags &= 0xF;
            now = gGameTicks;
            if (object->lastTime + 10 < now) {
                *result = 5;
                object->lastTime = now;
                break;
            }
        } else {
            now = gGameTicks;
            if (object->lastTime + 10 < now) {
                *result = 4;
                object->lastTime = now;
                break;
            }
        }
        *result = 1;
        break;
    default:
        *result = 1;
        break;
    }
}
