#include "types.h"

typedef struct AiParameterTimedEntity {
    u8 pad000[0x368];
    s32 timestamp;
} AiParameterTimedEntity;

typedef struct AiParameterContext {
    u8 pad00[0x8];
    AiParameterTimedEntity *entity;
} AiParameterContext;

extern s32 get_frame_time(void) __asm__("func_8007B1DC");
extern f32 D_8007489C;
extern f32 D_800748A0;

f32 ai_parameter_slot8_elapsed_time(AiParameterContext *context) __asm__("func_800E9660");

f32 ai_parameter_slot8_elapsed_time(AiParameterContext *context)
{
    s32 timestamp = context->entity->timestamp;
    s32 elapsed = get_frame_time() - timestamp;
    f32 value;

    if (elapsed < 9000) {
        value = (f32)elapsed / D_8007489C;
    } else {
        value = D_800748A0;
    }
    return value;
}
