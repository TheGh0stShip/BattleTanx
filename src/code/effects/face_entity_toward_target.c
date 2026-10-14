#include "types.h"

typedef struct TurnEntity {
    u8 pad00[0xC];
    s32 valueC;
    s32 value10;
    u8 pad14[0x8];
    u8 value1C;
    u8 value1D;
    s16 heading;
} TurnEntity;

extern float sqrtf(float);
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern void func_8008B89C(TurnEntity *entity);

void face_entity_toward_target(TurnEntity *entity, s32 unused, f32 *target) __asm__("func_800908F0");

void face_entity_toward_target(TurnEntity *entity, s32 unused, f32 *target) {
    f32 dx = target[1] - (f32)entity->valueC;
    f32 dz = target[0] - (f32)entity->value10;

    if ((dx != 0.0f) | (dz != 0.0f)) {
        entity->value1C = 1;
        if (-dx < 0.0f) {
            entity->heading = -radians_to_angle(-dz / sqrtf(dx * dx + dz * dz));
        } else {
            entity->heading = radians_to_angle(-dz / sqrtf(dx * dx + dz * dz));
        }
    }
    entity->value1D |= 8;
    func_8008B89C(entity);
}
