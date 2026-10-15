#include "types.h"

typedef struct AiLinkSource {
    u8 pad00[0x4];
    s32 linkedId;
    u8 pad08[0x8];
    f32 value10;
    u8 pad14[0x4];
    f32 value18;
} AiLinkSource;

typedef struct AiMemberLink {
    s32 kind;
    f32 *values;
    f32 value08;
    f32 value0C;
    AiLinkSource *source;
    s32 linkedId;
} AiMemberLink;

extern s32 get_entity_index(s16 id) __asm__("func_800A03B8");
extern AiLinkSource *get_ai_link_source(s32 index) __asm__("func_800E1C00");

void initialize_ai_member_link(AiMemberLink *link, s16 id) __asm__("func_800E3554");

void initialize_ai_member_link(AiMemberLink *link, s16 id)
{
    AiLinkSource *source = get_ai_link_source(get_entity_index(id));

    if (source != 0) {
        link->source = source;
        link->linkedId = source->linkedId;
        link->value0C = source->value10;
        link->value08 = source->value18;
        link->values = &link->value08;
        link->kind = 4;
    } else {
        link->kind = 0;
        link->values = 0;
    }
}
