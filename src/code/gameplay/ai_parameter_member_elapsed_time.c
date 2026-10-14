#include "types.h"
#include "ai_play_stack.h"

typedef struct AiTimedMember {
    u8 pad00[0x364];
    s32 value364;
} AiTimedMember;

extern s32 get_frame_time(void) __asm__("func_8007B1DC");
extern f32 D_80074894;
extern f32 D_80074898;

f32 ai_parameter_member_elapsed_time(AiActionContext *context) __asm__("func_800E9600");

f32 ai_parameter_member_elapsed_time(AiActionContext *context)
{
    s32 start = ((AiTimedMember *)context->member)->value364;
    s32 elapsed = get_frame_time() - start;

    if (elapsed >= 9000) {
        return D_80074898;
    }
    return (f32)elapsed / D_80074894;
}
