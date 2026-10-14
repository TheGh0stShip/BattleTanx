#include "types.h"

typedef struct AiUnitTypeContext {
    u16 *unitTypes;
} AiUnitTypeContext;

f32 ai_has_unit_type_0(AiUnitTypeContext *context) __asm__("func_800E83A4");
f32 ai_has_unit_type_1(AiUnitTypeContext *context) __asm__("func_800E83F8");
f32 ai_has_unit_type_2(AiUnitTypeContext *context) __asm__("func_800E8450");
f32 ai_has_unit_type_3(AiUnitTypeContext *context) __asm__("func_800E84A8");
f32 ai_lacks_unit_type_0(AiUnitTypeContext *context) __asm__("func_800E8500");
f32 ai_lacks_unit_type_1(AiUnitTypeContext *context) __asm__("func_800E855C");
f32 ai_lacks_unit_type_2(AiUnitTypeContext *context) __asm__("func_800E85BC");
f32 ai_lacks_unit_type_3(AiUnitTypeContext *context) __asm__("func_800E861C");

#define DEFINE_HAS_UNIT_TYPE(name, type)          \
f32 name(AiUnitTypeContext *context)              \
{                                                  \
    u16 *types;                                    \
    u16 count;                                     \
    s32 i;                                         \
    f32 found;                                     \
                                                   \
    types = context->unitTypes;                    \
    count = types[3];                              \
    i = 0;                                         \
    if (count != 0) {                              \
        found = 1.0f;                              \
        do {                                       \
            if (types[(u16)i] == (type)) {         \
                goto found_type;                   \
            }                                      \
            i++;                                   \
        } while ((u16)i < count);                  \
    }                                              \
    found = 0.0f;                                  \
found_type:                                        \
    return found;                                  \
}

#define DEFINE_LACKS_UNIT_TYPE(name, type)        \
f32 name(AiUnitTypeContext *context)              \
{                                                  \
    u16 *types;                                    \
    u16 count;                                     \
    s32 i;                                         \
    f32 found;                                     \
                                                   \
    types = context->unitTypes;                    \
    count = types[3];                              \
    i = 0;                                         \
    if (count != 0) {                              \
        found = 1.0f;                              \
        do {                                       \
            if (types[(u16)i] == (type)) {         \
                goto found_type;                   \
            }                                      \
            i++;                                   \
        } while ((u16)i < count);                  \
    }                                              \
    found = 0.0f;                                  \
found_type:                                        \
    return 1.0f - found;                           \
}

#define DEFINE_HAS_NONZERO_UNIT_TYPE(name, type)  \
f32 name(AiUnitTypeContext *context)              \
{                                                  \
    u16 *types;                                    \
    u16 count;                                     \
    register u16 desired __asm__("$6");           \
    s32 i;                                         \
    f32 found;                                     \
                                                   \
    types = context->unitTypes;                    \
    count = types[3];                              \
    i = 0;                                         \
    if (count != 0) {                              \
        desired = (type);                          \
        found = 1.0f;                              \
        do {                                       \
            if (types[(u16)i] == desired) {        \
                goto found_type;                   \
            }                                      \
            i++;                                   \
        } while ((u16)i < count);                  \
    }                                              \
    found = 0.0f;                                  \
found_type:                                        \
    return found;                                  \
}

#define DEFINE_LACKS_NONZERO_UNIT_TYPE(name, type) \
f32 name(AiUnitTypeContext *context)               \
{                                                   \
    u16 *types;                                     \
    u16 count;                                      \
    register u16 desired __asm__("$6");            \
    s32 i;                                          \
    f32 found;                                      \
                                                    \
    types = context->unitTypes;                     \
    count = types[3];                               \
    i = 0;                                          \
    if (count != 0) {                               \
        desired = (type);                           \
        found = 1.0f;                               \
        do {                                        \
            if (types[(u16)i] == desired) {         \
                goto found_type;                    \
            }                                       \
            i++;                                    \
        } while ((u16)i < count);                   \
    }                                               \
    found = 0.0f;                                   \
found_type:                                         \
    return 1.0f - found;                            \
}

DEFINE_HAS_UNIT_TYPE(ai_has_unit_type_0, 0)
DEFINE_HAS_NONZERO_UNIT_TYPE(ai_has_unit_type_1, 1)
DEFINE_HAS_NONZERO_UNIT_TYPE(ai_has_unit_type_2, 2)
DEFINE_HAS_NONZERO_UNIT_TYPE(ai_has_unit_type_3, 3)
DEFINE_LACKS_UNIT_TYPE(ai_lacks_unit_type_0, 0)
DEFINE_LACKS_NONZERO_UNIT_TYPE(ai_lacks_unit_type_1, 1)
DEFINE_LACKS_NONZERO_UNIT_TYPE(ai_lacks_unit_type_2, 2)
DEFINE_LACKS_NONZERO_UNIT_TYPE(ai_lacks_unit_type_3, 3)
