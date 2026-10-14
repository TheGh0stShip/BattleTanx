/* BattleTanx AI parameter-provider and squad play tables (.data 0x801358C0-0x80135D30).
 * Consumers: ai_get_parameter (func_800E9720), ai_assign_member_play_slots
 * (func_800E9E5C).  Data-only reconstruction; every word is verified against the
 * BattleTanx USA Rev 0 ROM after relocation. */
#include "types.h"

typedef f32 (*AiParameterProvider)(void *context);
typedef f32 (*AiPlayScorer)(void *context);

typedef struct AiPlayName {
    s32 (*callback)(void *context);
    const char *name;
    s32 enabled;
    s32 reserved;
} AiPlayName;

typedef struct AiPlaySlot {
    s32 play;
    AiPlayScorer scorer;
} AiPlaySlot;

extern f32 func_800E7718(void *context);
extern f32 func_800E7724(void *context);
extern f32 func_800E7734(void *context);
extern f32 func_800E775C(void *context);
extern f32 func_800E78D4(void *context);
extern f32 func_800E78E0(void *context);
extern f32 func_800E78EC(void *context);
extern f32 func_800E78F8(void *context);
extern f32 func_800E7904(void *context);
extern f32 func_800E7910(void *context);
extern f32 func_800E791C(void *context);
extern f32 func_800E7928(void *context);
extern f32 func_800E7934(void *context);
extern f32 func_800E7A50(void *context);
extern f32 func_800E7B7C(void *context);
extern f32 func_800E7CA8(void *context);
extern f32 func_800E7DD4(void *context);
extern f32 func_800E7E50(void *context);
extern f32 func_800E7ED4(void *context);
extern f32 func_800E808C(void *context);
extern f32 func_800E8148(void *context);
extern f32 func_800E8204(void *context);
extern f32 func_800E83A4(void *context);
extern f32 func_800E83F8(void *context);
extern f32 func_800E8450(void *context);
extern f32 func_800E84A8(void *context);
extern f32 func_800E8500(void *context);
extern f32 func_800E855C(void *context);
extern f32 func_800E85BC(void *context);
extern f32 func_800E861C(void *context);
extern f32 func_800E867C(void *context);
extern f32 func_800E86A0(void *context);
extern f32 func_800E86C8(void *context);
extern f32 func_800E86F0(void *context);
extern f32 func_800E8718(void *context);
extern f32 func_800E8740(void *context);
extern f32 func_800E8768(void *context);
extern f32 func_800E87A0(void *context);
extern f32 func_800E885C(void *context);
extern f32 func_800E8934(void *context);
extern f32 func_800E89B8(void *context);
extern f32 func_800E8A48(void *context);
extern f32 func_800E8AE4(void *context);
extern f32 func_800E8B6C(void *context);
extern f32 func_800E8BFC(void *context);
extern f32 func_800E8C84(void *context);
extern f32 func_800E8D14(void *context);
extern f32 func_800E8D3C(void *context);
extern f32 func_800E8D64(void *context);
extern f32 func_800E8DAC(void *context);
extern f32 func_800E8E5C(void *context);
extern f32 func_800E8E84(void *context);
extern f32 func_800E8EB4(void *context);
extern f32 func_800E8F1C(void *context);
extern f32 func_800E8F84(void *context);
extern f32 func_800E9008(void *context);
extern f32 func_800E9098(void *context);
extern f32 func_800E90C0(void *context);
extern f32 func_800E90E8(void *context);
extern f32 func_800E9148(void *context);
extern f32 func_800E91AC(void *context);
extern f32 func_800E9200(void *context);
extern f32 func_800E9288(void *context);
extern f32 func_800E92B8(void *context);
extern f32 func_800E92F0(void *context);
extern f32 func_800E9318(void *context);
extern f32 func_800E9458(void *context);
extern f32 func_800E9480(void *context);
extern f32 func_800E94D8(void *context);
extern f32 func_800E9538(void *context);
extern f32 func_800E9570(void *context);
extern f32 func_800E9600(void *context);
extern f32 func_800E9660(void *context);
extern f32 func_800E96C0(void *context);
extern f32 func_800E9A28(void *context);
extern f32 func_800E9A30(void *context);
extern f32 func_800E9A54(void *context);
extern f32 func_800E9A9C(void *context);
extern f32 func_800E9C24(void *context);
extern f32 func_800E9D30(void *context);
extern f32 func_800E9D80(void *context);
extern f32 func_800E9DA4(void *context);
extern const char D_800748AC[];
extern const char D_800748B8[];
extern const char D_800748C0[];
extern const char D_800748C8[];
extern const char D_800748D4[];
extern const char D_800748DC[];

/* Parameters whose key has neither the 0x1000 nor 0x2000 bit; zero entries are unused slots. */
AiParameterProvider gAiFixedParameterProviders[24] = {
    func_800E7734, func_800E775C, func_800E7718, func_800E7724,
    func_800E78D4, func_800E78E0, func_800E78EC, func_800E78F8,
    func_800E7904, func_800E7910, func_800E791C, func_800E7928,
    func_800E7934, func_800E7A50, func_800E7B7C, func_800E7CA8,
    func_800E7DD4, func_800E7E50, func_800E7ED4, func_800E808C,
    func_800E8148, func_800E8204, 0, 0,
};

/* Parameters selected by owner keys (0x2000 | 0x100 | index). */
AiParameterProvider gAiOwnerParameterProviders[24] = {
    func_800E83A4, func_800E83F8, func_800E8450, func_800E84A8,
    func_800E8500, func_800E855C, func_800E85BC, func_800E861C,
    func_800E867C, func_800E86A0, func_800E86C8, func_800E86F0,
    func_800E8718, func_800E8740, func_800E8768, func_800E87A0,
    func_800E885C, func_800E8934, func_800E8AE4, func_800E8B6C,
    func_800E8BFC, func_800E8C84, func_800E89B8, func_800E8A48,
};

/* Parameters selected by member keys (0x1000 | 0x100 | index). */
AiParameterProvider gAiMemberParameterProviders[28] = {
    func_800E8D14, func_800E8D3C, func_800E8D64, func_800E8DAC,
    func_800E8E5C, func_800E8E84, func_800E8EB4, func_800E8F1C,
    func_800E8F84, func_800E9008, func_800E9098, func_800E90C0,
    func_800E90E8, func_800E9148, func_800E91AC, func_800E9200,
    func_800E9288, func_800E92B8, func_800E92F0, func_800E9318,
    func_800E9458, func_800E94D8, func_800E9480, func_800E9538,
    func_800E9570, func_800E9600, func_800E9660, func_800E96C0,
};

/* Play-name records: optional entry callback, name, enable flag, reserved. */
AiPlayName gAiPlayNames[6] = {
    { 0, D_800748DC, 1, 0 },
    { 0, D_800748D4, 1, 0 },
    { func_800E9A28, D_800748C8, 1, 0 },
    { 0, D_800748C0, 1, 0 },
    { 0, D_800748B8, 1, 0 },
    { 0, D_800748AC, 1, 0 },
};

/* Squad play-slot tables: {play, scorer} runs, then {play, NULL} for the
 * remaining members, then a {0, NULL} terminator. */
AiPlaySlot gAiPlaySlots_80135A50[7] = {
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x1, func_800E9A54 },
    { 0x5, 0 },
    { 0x0, 0 },
};

AiPlaySlot gAiPlaySlots_80135A88[7] = {
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x1, func_800E9A54 },
    { 0xD, 0 },
    { 0x0, 0 },
};

AiPlaySlot gAiPlaySlots_80135AC0[9] = {
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x1, func_800E9A54 },
    { 0x8, func_800E9C24 },
    { 0x5, func_800E9A9C },
    { 0x8, 0 },
    { 0x0, 0 },
};

AiPlaySlot gAiPlaySlots_80135B08[12] = {
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x1, func_800E9A54 },
    { 0x5, func_800E9A9C },
    { 0x3, func_800E9A30 },
    { 0x3, func_800E9A30 },
    { 0x3, func_800E9A30 },
    { 0x3, func_800E9A30 },
    { 0x5, 0 },
    { 0x0, 0 },
};

AiPlaySlot gAiPlaySlots_80135B68[9] = {
    { 0x1C, func_800E9D30 },
    { 0xB, func_800E9D30 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x1, func_800E9A54 },
    { 0x5, 0 },
    { 0x0, 0 },
};

AiPlaySlot gAiPlaySlots_80135BB0[11] = {
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x1, func_800E9A54 },
    { 0x11, 0 },
    { 0x0, 0 },
};

AiPlaySlot gAiPlaySlots_80135C08[6] = {
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x3, 0 },
    { 0x0, 0 },
};

AiPlaySlot gAiPlaySlots_80135C38[7] = {
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x5, func_800E9DA4 },
    { 0x3, 0 },
    { 0x0, 0 },
};

AiPlaySlot gAiPlaySlots_80135C70[8] = {
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x5, func_800E9DA4 },
    { 0x5, func_800E9DA4 },
    { 0x3, 0 },
    { 0x0, 0 },
};

AiPlaySlot gAiPlaySlots_80135CB0[8] = {
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x10, func_800E9D80 },
    { 0x5, func_800E9DA4 },
    { 0x5, func_800E9DA4 },
    { 0x5, func_800E9DA4 },
    { 0x3, 0 },
};

s32 gAiPlaySlotPad[2] = { 0, 0 };

/* Slot table for each owner role (owner + 0x14C); role 0 has none. */
AiPlaySlot *gAiPlaySlotTables[11] = {
    0,
    gAiPlaySlots_80135A50,
    gAiPlaySlots_80135A88,
    gAiPlaySlots_80135AC0,
    gAiPlaySlots_80135B08,
    gAiPlaySlots_80135B68,
    gAiPlaySlots_80135BB0,
    gAiPlaySlots_80135C08,
    gAiPlaySlots_80135C38,
    gAiPlaySlots_80135C70,
    gAiPlaySlots_80135CB0,
};

/* Halfword pairs that precede the next AI table (0x80135D24).  The values are
 * unit-class letters ('F','F','I','C','I','E'); their consumer is not yet
 * identified. */
s16 gAiUnitClassPairs[6] = { 0x46, 0x46, 0x49, 0x43, 0x49, 0x45 };
