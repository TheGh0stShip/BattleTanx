/* BattleTanx AI play scripts, action policies and parameter terms
 * (.data 0x80135D30-0x80137900).
 *
 * scripts (0x80137888) is the play table read by ai_play_stack_* through
 * D_80137888; each script is an array of 16-byte AiPlayStep records.
 * Options are the weighted action policies consumed by
 * ai_select_weighted_action (func_800EA93C); terms are {parameter key, f32}
 * pairs read through ai_get_parameter (func_800E9720), zero-key terminated.
 * Members named words_* hold values whose record type is not yet proven.
 * Data-only reconstruction verified byte-for-byte against the BattleTanx USA
 * Rev 0 ROM after relocation. */
#include "types.h"

typedef struct AiParameterTerm {
    s32 key;
    f32 value;
} AiParameterTerm;

typedef struct AiActionOption {
    s32 action;
    AiParameterTerm *requirements;
    AiParameterTerm *weights;
} AiActionOption;

typedef struct AiPlayStep {
    s32 (*run)(void *context);
    s32 (*monitor)(void *context);
    s32 play;
    s32 state;
} AiPlayStep;

extern s32 func_800EABB0(void *context);
extern s32 func_800EABFC(void *context);
extern s32 func_800EAC48(void *context);
extern s32 func_800EAC80(void *context);
extern s32 func_800EACB4(void *context);
extern s32 func_800EACEC(void *context);
extern s32 func_800EAD2C(void *context);
extern s32 func_800EAD4C(void *context);
extern s32 func_800EAD74(void *context);
extern s32 func_800EAD9C(void *context);
extern s32 func_800EAE30(void *context);
extern s32 func_800EAEA8(void *context);
extern s32 func_800EAF14(void *context);
extern s32 func_800EAF6C(void *context);
extern s32 func_800EAFC4(void *context);
extern s32 func_800EAFE4(void *context);
extern s32 func_800EB00C(void *context);
extern s32 func_800EB02C(void *context);
extern s32 func_800EB054(void *context);
extern s32 func_800EB07C(void *context);
extern s32 func_800EB0E8(void *context);
extern s32 func_800EB110(void *context);
extern s32 func_800EB130(void *context);
extern s32 func_800EB158(void *context);
extern s32 func_800EB178(void *context);
extern s32 func_800EB1A0(void *context);
extern s32 func_800EB1C0(void *context);
extern s32 func_800EB1E8(void *context);
extern s32 func_800EB228(void *context);
extern s32 func_800EB248(void *context);
extern s32 func_800EB2A4(void *context);
extern s32 func_800EB2CC(void *context);
extern s32 func_800EB310(void *context);
extern s32 func_800EB338(void *context);
extern s32 func_800EB360(void *context);
extern s32 func_800EB394(void *context);
extern s32 func_800EB3BC(void *context);
extern s32 func_800EB3F0(void *context);
extern s32 func_800EB418(void *context);
extern s32 func_800EB440(void *context);
extern s32 func_800EB47C(void *context);
extern s32 func_800EB4A4(void *context);
extern s32 func_800EB4E4(void *context);
extern s32 func_800EB504(void *context);
extern s32 func_800EB554(void *context);
extern s32 func_800EB5A0(void *context);
extern s32 func_800EB5C0(void *context);
extern s32 func_800EB5E8(void *context);
extern s32 func_800EB640(void *context);
extern s32 func_800EB668(void *context);
extern s32 func_800EB69C(void *context);
extern s32 func_800EB6D4(void *context);
extern s32 func_800EB71C(void *context);
extern s32 func_800EB764(void *context);
extern s32 func_800EB7AC(void *context);
extern s32 func_800EB818(void *context);
extern s32 func_800EB840(void *context);
extern s32 func_800EB888(void *context);
extern s32 func_800EB8B0(void *context);
extern s32 func_800EB8F8(void *context);
extern s32 func_800EB920(void *context);
extern s32 func_800EB968(void *context);
extern s32 func_800EB990(void *context);
extern s32 func_800EB9D8(void *context);
extern s32 func_800EBA00(void *context);
extern s32 func_800EBA48(void *context);
extern s32 func_800EBA70(void *context);
extern s32 func_800EBAB8(void *context);
extern s32 func_800EBAE0(void *context);
extern s32 func_800EBB58(void *context);
extern s32 func_800EBB80(void *context);
extern s32 func_800EBBB4(void *context);
extern s32 func_800EBBBC(void *context);
extern s32 func_800EBBFC(void *context);
extern s32 func_800EBC1C(void *context);
extern s32 func_800EBC44(void *context);
extern s32 func_800EBC6C(void *context);
extern s32 func_800EBC94(void *context);
extern s32 func_800EBCBC(void *context);
extern s32 func_800EBCE4(void *context);
extern s32 func_800EBD04(void *context);
extern s32 func_800EBD2C(void *context);
extern s32 func_800EBD4C(void *context);
extern s32 func_800EBD74(void *context);
extern s32 func_800EBDB4(void *context);
extern s32 func_800EBDDC(void *context);
extern s32 func_800EBDFC(void *context);
extern s32 func_800EBE24(void *context);
extern s32 func_800EBE44(void *context);
extern s32 func_800EBE6C(void *context);
extern s32 func_800EBEAC(void *context);
extern s32 func_800EBED4(void *context);
extern s32 func_800EBF28(void *context);
extern s32 func_800EBF50(void *context);
extern s32 func_800EBFA4(void *context);
extern s32 func_800EBFCC(void *context);
extern s32 func_800EBFF4(void *context);
extern s32 func_800EC014(void *context);
extern s32 func_800EC03C(void *context);
extern s32 func_800EC05C(void *context);
extern s32 func_800EC084(void *context);
extern s32 func_800EC0D4(void *context);
extern s32 func_800EC128(void *context);
extern s32 func_800EC17C(void *context);
extern s32 func_800EC1D0(void *context);
extern s32 func_800EC218(void *context);
extern s32 func_800EC26C(void *context);
extern s32 func_800EC2C0(void *context);
extern s32 func_800EC314(void *context);
extern s32 func_800EC35C(void *context);

typedef struct AiScriptData {
    AiPlayStep steps_80135D30[4];
    AiParameterTerm terms_80135D70[7];
    s32 words_80135DA8[1];
    AiParameterTerm terms_80135DAC[9];
    AiPlayStep steps_80135DF4[3];
    AiPlayStep steps_80135E24[3];
    AiParameterTerm terms_80135E54[5];
    AiPlayStep steps_80135E7C[7];
    AiParameterTerm terms_80135EEC[3];
    s32 words_80135F04[2];
    AiParameterTerm terms_80135F0C[16];
    s32 words_80135F8C[1];
    AiParameterTerm terms_80135F90[4];
    s32 words_80135FB0[1];
    AiParameterTerm terms_80135FB4[1];
    s32 words_80135FBC[1];
    AiParameterTerm terms_80135FC0[1];
    s32 words_80135FC8[1];
    AiParameterTerm terms_80135FCC[1];
    s32 words_80135FD4[1];
    AiPlayStep steps_80135FD8[7];
    AiParameterTerm terms_80136048[6];
    AiActionOption options_80136078[4];
    AiParameterTerm terms_801360A8[8];
    AiActionOption options_801360E8[5];
    AiParameterTerm terms_80136124[8];
    AiActionOption options_80136164[4];
    AiParameterTerm terms_80136194[7];
    AiActionOption options_801361CC[4];
    AiPlayStep steps_801361FC[4];
    AiParameterTerm terms_8013623C[2];
    AiActionOption options_8013624C[3];
    AiParameterTerm terms_80136270[2];
    s32 words_80136280[2];
    AiParameterTerm terms_80136288[4];
    s32 words_801362A8[2];
    AiParameterTerm terms_801362B0[2];
    AiPlayStep steps_801362C0[3];
    AiPlayStep steps_801362F0[8];
    AiParameterTerm terms_80136370[4];
    AiActionOption options_80136390[4];
    AiParameterTerm terms_801363C0[4];
    AiActionOption options_801363E0[3];
    AiParameterTerm terms_80136404[4];
    AiActionOption options_80136424[3];
    AiParameterTerm terms_80136448[2];
    AiActionOption options_80136458[2];
    AiParameterTerm terms_80136470[2];
    AiActionOption options_80136480[2];
    AiPlayStep steps_80136498[3];
    AiParameterTerm terms_801364C8[4];
    AiActionOption options_801364E8[1];
    s32 words_801364F4[2];
    AiParameterTerm terms_801364FC[6];
    AiActionOption options_8013652C[1];
    s32 words_80136538[2];
    AiParameterTerm terms_80136540[4];
    s32 words_80136560[2];
    AiParameterTerm terms_80136568[2];
    AiPlayStep steps_80136578[3];
    AiPlayStep steps_801365A8[2];
    AiPlayStep steps_801365C8[2];
    AiPlayStep steps_801365E8[5];
    AiParameterTerm terms_80136638[4];
    AiActionOption options_80136658[4];
    AiParameterTerm terms_80136688[4];
    AiActionOption options_801366A8[3];
    AiParameterTerm terms_801366CC[2];
    AiActionOption options_801366DC[2];
    AiPlayStep steps_801366F4[5];
    AiParameterTerm terms_80136744[6];
    AiActionOption options_80136774[5];
    AiPlayStep steps_801367B0[8];
    AiParameterTerm terms_80136830[26];
    s32 words_80136900[2];
    AiParameterTerm terms_80136908[1];
    s32 words_80136910[2];
    AiParameterTerm terms_80136918[1];
    s32 words_80136920[2];
    AiParameterTerm terms_80136928[1];
    AiActionOption options_80136930[5];
    AiParameterTerm terms_8013696C[1];
    s32 words_80136974[1];
    AiParameterTerm terms_80136978[29];
    s32 words_80136A60[2];
    AiParameterTerm terms_80136A68[1];
    s32 words_80136A70[2];
    AiParameterTerm terms_80136A78[1];
    s32 words_80136A80[2];
    AiParameterTerm terms_80136A88[1];
    AiActionOption options_80136A90[5];
    AiParameterTerm terms_80136ACC[1];
    s32 words_80136AD4[1];
    AiParameterTerm terms_80136AD8[5];
    AiActionOption options_80136B00[2];
    AiParameterTerm terms_80136B18[26];
    s32 words_80136BE8[2];
    AiParameterTerm terms_80136BF0[1];
    s32 words_80136BF8[2];
    AiParameterTerm terms_80136C00[1];
    s32 words_80136C08[2];
    AiParameterTerm terms_80136C10[1];
    AiActionOption options_80136C18[5];
    AiParameterTerm terms_80136C54[1];
    s32 words_80136C5C[1];
    AiParameterTerm terms_80136C60[29];
    s32 words_80136D48[2];
    AiParameterTerm terms_80136D50[1];
    s32 words_80136D58[2];
    AiParameterTerm terms_80136D60[1];
    s32 words_80136D68[2];
    AiParameterTerm terms_80136D70[1];
    AiActionOption options_80136D78[5];
    AiParameterTerm terms_80136DB4[1];
    s32 words_80136DBC[1];
    AiParameterTerm terms_80136DC0[29];
    s32 words_80136EA8[2];
    AiParameterTerm terms_80136EB0[1];
    s32 words_80136EB8[2];
    AiParameterTerm terms_80136EC0[1];
    s32 words_80136EC8[2];
    AiParameterTerm terms_80136ED0[1];
    AiActionOption options_80136ED8[5];
    AiParameterTerm terms_80136F14[1];
    s32 words_80136F1C[1];
    AiParameterTerm terms_80136F20[29];
    s32 words_80137008[2];
    AiParameterTerm terms_80137010[1];
    s32 words_80137018[2];
    AiParameterTerm terms_80137020[1];
    s32 words_80137028[2];
    AiParameterTerm terms_80137030[1];
    AiActionOption options_80137038[5];
    AiParameterTerm terms_80137074[1];
    s32 words_8013707C[1];
    AiParameterTerm terms_80137080[3];
    AiPlayStep steps_80137098[4];
    AiParameterTerm terms_801370D8[2];
    AiActionOption options_801370E8[2];
    AiPlayStep steps_80137100[3];
    AiPlayStep steps_80137130[3];
    AiPlayStep steps_80137160[5];
    AiParameterTerm terms_801371B0[4];
    AiActionOption options_801371D0[4];
    AiParameterTerm terms_80137200[2];
    AiActionOption options_80137210[2];
    AiParameterTerm terms_80137228[4];
    AiActionOption options_80137248[3];
    AiParameterTerm terms_8013726C[4];
    AiActionOption options_8013728C[3];
    AiPlayStep steps_801372B0[5];
    AiParameterTerm terms_80137300[2];
    AiActionOption options_80137310[3];
    AiParameterTerm terms_80137334[4];
    AiActionOption options_80137354[3];
    AiParameterTerm terms_80137378[4];
    AiActionOption options_80137398[3];
    AiPlayStep steps_801373BC[5];
    AiParameterTerm terms_8013740C[2];
    AiActionOption options_8013741C[3];
    AiParameterTerm terms_80137440[4];
    AiActionOption options_80137460[3];
    AiParameterTerm terms_80137484[4];
    AiActionOption options_801374A4[3];
    AiPlayStep steps_801374C8[4];
    AiParameterTerm terms_80137508[2];
    AiActionOption options_80137518[3];
    AiParameterTerm terms_8013753C[4];
    AiActionOption options_8013755C[3];
    AiParameterTerm terms_80137580[4];
    AiActionOption options_801375A0[3];
    AiPlayStep steps_801375C4[4];
    AiParameterTerm terms_80137604[2];
    AiActionOption options_80137614[3];
    AiParameterTerm terms_80137638[2];
    s32 words_80137648[2];
    AiParameterTerm terms_80137650[4];
    s32 words_80137670[2];
    AiParameterTerm terms_80137678[2];
    AiPlayStep steps_80137688[2];
    AiPlayStep steps_801376A8[5];
    AiParameterTerm terms_801376F8[2];
    AiActionOption options_80137708[2];
    AiParameterTerm terms_80137720[2];
    AiActionOption options_80137730[2];
    AiParameterTerm terms_80137748[2];
    AiActionOption options_80137758[2];
    AiPlayStep steps_80137770[5];
    AiParameterTerm terms_801377C0[2];
    AiActionOption options_801377D0[2];
    AiParameterTerm terms_801377E8[2];
    AiActionOption options_801377F8[2];
    AiParameterTerm terms_80137810[2];
    AiActionOption options_80137820[2];
    AiPlayStep steps_80137838[3];
    AiPlayStep steps_80137868[2];
    AiPlayStep *scripts[29];
    s32 tail_801378FC[1];
} AiScriptData;

AiScriptData gAiScriptData = {
    { { 0, 0, 1, 1 }, { func_800EABB0, 0, 0, -1 }, { func_800EABFC, func_800EAC48, 19, -1 }, { func_800EAC80, func_800EACB4, 19, -1 } },
    { { 0x1002, 0.0001f }, { 0x0, 0.0f }, { 0x3, -1.778393e-39f }, { 0x0, 2.8026e-45f }, { 0x0, 0.0f }, { 0x0, 0.0f }, { 0x0, 5.74252e-42f } },
    { 0x38D1B717 },
    { { 0x0, 0.0f }, { 0x3, -1.778466e-39f }, { 0x0, 0.0f }, { 0x0, 0.0f }, { 0x1007, 0.9f }, { 0x0, 0.0f }, { 0x2, -1.778522e-39f }, { 0x0, 0.0f }, { 0x0, 0.0f } },
    { { 0, 0, 2, 1 }, { func_800EACEC, 0, 0, 2 }, { func_800EAD2C, 0, 0, -1 } },
    { { 0, 0, 3, 1 }, { func_800EAD4C, 0, 0, -1 }, { 0, 0, 5, -1 } },
    { { 0x1002, 0.0001f }, { 0x0, 0.0f }, { 0x2, -1.778713e-39f }, { 0x0, 0.0f }, { 0x0, 0.0f } },
    { { 0, 0, 4, 1 }, { func_800EAD74, 0, 0, -1 }, { func_800EAD9C, 0, 0, -2 }, { func_800EAE30, 0, 0, -2 }, { func_800EAEA8, 0, 0, -2 }, { func_800EAF14, 0, 0, -2 }, { func_800EAF6C, 0, 0, -2 } },
    { { 0x1000, 0.25f }, { 0x110A, 0.25f }, { 0x0, 0.0f } },
    { 0x8103, 0x3F800000 },
    { { 0x0, 0.0f }, { 0x1001, 1.0f }, { 0x0, 0.0f }, { 0x1000, 0.9f }, { 0x110B, 0.25f }, { 0x0, 0.0f }, { 0x1000, 0.9f }, { 0x110B, 0.9f }, { 0x0, 0.0f }, { 0x110A, 0.9f }, { 0x110B, 0.25f }, { 0x0, 0.0f }, { 0x110A, 0.9f }, { 0x110B, 0.9f }, { 0x0, 0.0f }, { 0x2, -1.778926e-39f } },
    { 0x80135F04 },
    { { 0x2, -1.778982e-39f }, { 0x0, 4.2039e-45f }, { 0x0, -1.779004e-39f }, { 0x4, 0.0f } },
    { 0x80135F3C },
    { { 0x5, 0.0f } },
    { 0x80135F54 },
    { { 0x6, 0.0f } },
    { 0x80135F6C },
    { { 0x0, 0.0f } },
    { 0x0 },
    { { 0, 0, 5, 1 }, { func_800EAFC4, 0, 4, 2 }, { 0, func_800EAFE4, 6, 1 }, { func_800EB00C, func_800EB02C, 6, 1 }, { 0, func_800EB054, 6, 1 }, { func_800EB07C, func_800EB0E8, 6, 1 }, { func_800EB110, 0, 0, 1 } },
    { { 0x1002, 0.0001f }, { 0x0, 0.0f }, { 0x1005, 0.9f }, { 0x0, 0.0f }, { 0x2111, 0.0001f }, { 0x0, 0.0f } },
    { { 3, &gAiScriptData.terms_80136048[0], 0 }, { 1, &gAiScriptData.terms_80136048[2], 0 }, { 1, &gAiScriptData.terms_80136048[4], 0 }, { 0, 0, 0 } },
    { { 0x1007, 0.9f }, { 0x0, 0.0f }, { 0x1117, 0.0001f }, { 0x0, 0.0f }, { 0x1005, 0.9f }, { 0x0, 0.0f }, { 0x2111, 0.0001f }, { 0x0, 0.0f } },
    { { 2, &gAiScriptData.terms_801360A8[0], 0 }, { 4, &gAiScriptData.terms_801360A8[2], 0 }, { 1, &gAiScriptData.terms_801360A8[4], 0 }, { 1, &gAiScriptData.terms_801360A8[6], 0 }, { 0, 0, 0 } },
    { { 0x1007, 0.9f }, { 0x0, 0.0f }, { 0x110D, 1.0f }, { 0x110E, 0.0001f }, { 0x1116, 0.015999999f }, { 0x0, 0.0f }, { 0x2111, 0.0001f }, { 0x0, 0.0f } },
    { { 1, &gAiScriptData.terms_80136124[0], 0 }, { 5, &gAiScriptData.terms_80136124[2], 0 }, { 1, &gAiScriptData.terms_80136124[6], 0 }, { 0, 0, 0 } },
    { { 0x1007, 0.9f }, { 0x1100, 0.0001f }, { 0x0, 0.0f }, { 0x1117, 0.0001f }, { 0x0, 0.0f }, { 0x2111, 0.0001f }, { 0x0, 0.0f } },
    { { 6, &gAiScriptData.terms_80136194[0], 0 }, { 1, &gAiScriptData.terms_80136194[3], 0 }, { 1, &gAiScriptData.terms_80136194[5], 0 }, { 0, 0, 0 } },
    { { 0, 0, 6, 1 }, { func_800EB130, 0, 0, -1 }, { func_800EB158, func_800EB178, 9, -2 }, { func_800EB1A0, func_800EB1C0, 9, -2 } },
    { { 0x1002, 0.0001f }, { 0x0, 0.0f } },
    { { 3, &gAiScriptData.terms_8013623C[0], 0 }, { 2, 0, 0 }, { 0, 0, 0 } },
    { { 0x1002, 0.0001f }, { 0x0, 0.0f } },
    { 0xFFFFFFFE, 0x80136270 },
    { { 0x0, 0.0f }, { 0x0, 0.0f }, { 0x1007, 0.9f }, { 0x0, 0.0f } },
    { 0xFFFFFFFE, 0x80136298 },
    { { 0x0, 0.0f }, { 0x0, 0.0f } },
    { { 0, 0, 7, 1 }, { func_800EB1E8, 0, 0, 2 }, { func_800EB228, 0, 0, -1 } },
    { { 0, 0, 8, 1 }, { func_800EB248, 0, 0, -1 }, { 0, func_800EB2A4, 6, 1 }, { func_800EB2CC, 0, 0, 4 }, { 0, func_800EB310, 6, 1 }, { func_800EB338, 0, 0, 6 }, { func_800EB360, func_800EB394, 6, 1 }, { func_800EB3BC, 0, 5, -1 } },
    { { 0x1110, 0.0001f }, { 0x0, 0.0f }, { 0x1113, 0.0001f }, { 0x0, 0.0f } },
    { { 5, &gAiScriptData.terms_80136370[0], 0 }, { 4, &gAiScriptData.terms_80136370[2], 0 }, { 2, 0, 0 }, { 0, 0, 0 } },
    { { 0x1110, 0.0001f }, { 0x0, 0.0f }, { 0x1113, 0.0001f }, { 0x0, 0.0f } },
    { { 5, &gAiScriptData.terms_801363C0[0], 0 }, { 3, &gAiScriptData.terms_801363C0[2], 0 }, { 0, 0, 0 } },
    { { 0x1110, 0.0001f }, { 0x0, 0.0f }, { 0x2117, 1.0f }, { 0x0, 0.0f } },
    { { 5, &gAiScriptData.terms_80136404[0], 0 }, { 7, &gAiScriptData.terms_80136404[2], 0 }, { 0, 0, 0 } },
    { { 0x2116, 0.0001f }, { 0x0, 0.0f } },
    { { 1, &gAiScriptData.terms_80136448[0], 0 }, { 0, 0, 0 } },
    { { 0x1111, 1.0f }, { 0x0, 0.0f } },
    { { 7, &gAiScriptData.terms_80136470[0], 0 }, { 0, 0, 0 } },
    { { 0, 0, 9, 1 }, { func_800EB3F0, func_800EB418, 12, -2 }, { func_800EB440, func_800EB47C, 12, -1 } },
    { { 0x1003, 0.0001f }, { 0x0, 0.0f }, { 0x1005, 0.9f }, { 0x0, 0.0f } },
    { { 2, &gAiScriptData.terms_801364C8[0], 0 } },
    { 0xFFFFFFFE, 0x801364D8 },
    { { 0x0, 0.0f }, { 0x0, 0.0f }, { 0x1003, 0.0001f }, { 0x0, 0.0f }, { 0x1005, 0.9f }, { 0x0, 0.0f } },
    { { 2, &gAiScriptData.terms_801364FC[2], 0 } },
    { 0xFFFFFFFE, 0x8013651C },
    { { 0x0, 0.0f }, { 0x0, 0.0f }, { 0x1007, 0.9f }, { 0x0, 0.0f } },
    { 0xFFFFFFFE, 0x80136550 },
    { { 0x0, 0.0f }, { 0x0, 0.0f } },
    { { 0, 0, 10, 1 }, { func_800EB4A4, 0, 0, 2 }, { func_800EB4E4, 0, 0, -1 } },
    { { 0, 0, 11, 1 }, { func_800EB504, 0, 23, -1 } },
    { { 0, 0, 12, 1 }, { 0, 0, 0, 1 } },
    { { 0, 0, 13, 1 }, { func_800EB554, 0, 0, -1 }, { func_800EB5A0, func_800EB5C0, 6, 1 }, { func_800EB5E8, func_800EB640, 12, 1 }, { func_800EB668, 0, 5, -1 } },
    { { 0x2113, 1.0f }, { 0x0, 0.0f }, { 0x1113, 0.0001f }, { 0x0, 0.0f } },
    { { 4, &gAiScriptData.terms_80136638[0], 0 }, { 3, &gAiScriptData.terms_80136638[2], 0 }, { 2, 0, 0 }, { 0, 0, 0 } },
    { { 0x2113, 1.0f }, { 0x0, 0.0f }, { 0x1113, 0.0001f }, { 0x0, 0.0f } },
    { { 4, &gAiScriptData.terms_80136688[0], 0 }, { 3, &gAiScriptData.terms_80136688[2], 0 }, { 0, 0, 0 } },
    { { 0x2113, 1.0f }, { 0x0, 0.0f } },
    { { 4, &gAiScriptData.terms_801366CC[0], 0 }, { 0, 0, 0 } },
    { { 0, 0, 14, 1 }, { func_800EB69C, 0, 0, -1 }, { func_800EB6D4, 0, 0, -2 }, { func_800EB71C, 0, 0, -2 }, { func_800EB764, 0, 0, -2 } },
    { { 0x210F, 0.0001f }, { 0x0, 0.0f }, { 0x2117, 1.0f }, { 0x0, 0.0f }, { 0x2113, 1.0f }, { 0x0, 0.0f } },
    { { 3, &gAiScriptData.terms_80136744[0], 0 }, { 4, &gAiScriptData.terms_80136744[2], 0 }, { 3, &gAiScriptData.terms_80136744[4], 0 }, { 2, 0, 0 }, { 0, 0, 0 } },
    { { 0, 0, 15, 1 }, { func_800EB7AC, func_800EB818, 12, -1 }, { func_800EB840, func_800EB888, 12, -1 }, { func_800EB8B0, func_800EB8F8, 12, -1 }, { func_800EB920, func_800EB968, 14, -1 }, { func_800EB990, func_800EB9D8, 14, -1 }, { func_800EBA00, func_800EBA48, 14, -1 }, { func_800EBA70, func_800EBAB8, 14, -1 } },
    { { 0x210F, 0.0001f }, { 0x0, 0.0f }, { 0x2111, 0.0001f }, { 0x0, 0.0f }, { 0x2104, 0.0001f }, { 0x810C, 0.0001f }, { 0x0, 0.0f }, { 0x8110, 0.9f }, { 0x2108, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2105, 0.0001f }, { 0x810D, 0.0001f }, { 0x0, 0.0f }, { 0x8111, 0.9f }, { 0x2109, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2106, 0.0001f }, { 0x810E, 0.0001f }, { 0x0, 0.0f }, { 0x8112, 0.9f }, { 0x210A, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2107, 0.0001f } },
    { 0x810F, 0x38D1B717 },
    { { 0x0, 0.0f } },
    { 0x8113, 0x3F666666 },
    { { 0x210B, 0.5f } },
    { 0x8100, 0x3DCCCCCD },
    { { 0x0, 0.0f } },
    { { 3, &gAiScriptData.terms_80136830[0], 0 }, { 2, &gAiScriptData.terms_80136830[2], 0 }, { 4, &gAiScriptData.terms_80136830[4], &gAiScriptData.terms_80136830[7] }, { 5, &gAiScriptData.terms_80136830[11], &gAiScriptData.terms_80136830[14] }, { 6, &gAiScriptData.terms_80136830[18], &gAiScriptData.terms_80136830[21] } },
    { { 0x7, -1.78253e-39f } },
    { 0x80136910 },
    { { 0x1, 0.0f }, { 0x0, 0.0f }, { 0x0, 0.0f }, { 0x210F, 0.0001f }, { 0x0, 0.0f }, { 0x2111, 0.0001f }, { 0x0, 0.0f }, { 0x2104, 0.0001f }, { 0x810C, 0.0001f }, { 0x0, 0.0f }, { 0x8110, 0.9f }, { 0x2108, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2105, 0.0001f }, { 0x810D, 0.0001f }, { 0x0, 0.0f }, { 0x8111, 0.9f }, { 0x2109, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2106, 0.0001f }, { 0x810E, 0.0001f }, { 0x0, 0.0f }, { 0x8112, 0.9f }, { 0x210A, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2107, 0.0001f } },
    { 0x810F, 0x38D1B717 },
    { { 0x0, 0.0f } },
    { 0x8113, 0x3F666666 },
    { { 0x210B, 0.5f } },
    { 0x8100, 0x3DCCCCCD },
    { { 0x0, 0.0f } },
    { { 3, &gAiScriptData.terms_80136978[3], 0 }, { 2, &gAiScriptData.terms_80136978[5], 0 }, { 4, &gAiScriptData.terms_80136978[7], &gAiScriptData.terms_80136978[10] }, { 5, &gAiScriptData.terms_80136978[14], &gAiScriptData.terms_80136978[17] }, { 6, &gAiScriptData.terms_80136978[21], &gAiScriptData.terms_80136978[24] } },
    { { 0x7, -1.783023e-39f } },
    { 0x80136A70 },
    { { 0x1, 0.0f }, { 0x0, 0.0f }, { 0x0, 0.0f }, { 0x2110, 0.0001f }, { 0x0, 0.0f } },
    { { 1, &gAiScriptData.terms_80136AD8[3], 0 }, { 0, 0, 0 } },
    { { 0x210F, 0.0001f }, { 0x0, 0.0f }, { 0x2111, 0.0001f }, { 0x0, 0.0f }, { 0x2104, 0.0001f }, { 0x810C, 0.0001f }, { 0x0, 0.0f }, { 0x8110, 0.9f }, { 0x2108, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2105, 0.0001f }, { 0x810D, 0.0001f }, { 0x0, 0.0f }, { 0x8111, 0.9f }, { 0x2109, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2106, 0.0001f }, { 0x810E, 0.0001f }, { 0x0, 0.0f }, { 0x8112, 0.9f }, { 0x210A, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2107, 0.0001f } },
    { 0x810F, 0x38D1B717 },
    { { 0x0, 0.0f } },
    { 0x8113, 0x3F666666 },
    { { 0x210B, 0.5f } },
    { 0x8100, 0x3DCCCCCD },
    { { 0x0, 0.0f } },
    { { 3, &gAiScriptData.terms_80136B18[0], 0 }, { 2, &gAiScriptData.terms_80136B18[2], 0 }, { 4, &gAiScriptData.terms_80136B18[4], &gAiScriptData.terms_80136B18[7] }, { 5, &gAiScriptData.terms_80136B18[11], &gAiScriptData.terms_80136B18[14] }, { 6, &gAiScriptData.terms_80136B18[18], &gAiScriptData.terms_80136B18[21] } },
    { { 0x7, -1.783573e-39f } },
    { 0x80136BF8 },
    { { 0x1, 0.0f }, { 0x0, 0.0f }, { 0x0, 0.0f }, { 0x210F, 0.0001f }, { 0x0, 0.0f }, { 0x2111, 0.0001f }, { 0x0, 0.0f }, { 0x2104, 0.0001f }, { 0x810C, 0.0001f }, { 0x0, 0.0f }, { 0x8110, 0.9f }, { 0x2108, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2105, 0.0001f }, { 0x810D, 0.0001f }, { 0x0, 0.0f }, { 0x8111, 0.9f }, { 0x2109, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2106, 0.0001f }, { 0x810E, 0.0001f }, { 0x0, 0.0f }, { 0x8112, 0.9f }, { 0x210A, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2107, 0.0001f } },
    { 0x810F, 0x38D1B717 },
    { { 0x0, 0.0f } },
    { 0x8113, 0x3F666666 },
    { { 0x210B, 0.5f } },
    { 0x8100, 0x3DCCCCCD },
    { { 0x0, 0.0f } },
    { { 3, &gAiScriptData.terms_80136C60[3], 0 }, { 2, &gAiScriptData.terms_80136C60[5], 0 }, { 4, &gAiScriptData.terms_80136C60[7], &gAiScriptData.terms_80136C60[10] }, { 5, &gAiScriptData.terms_80136C60[14], &gAiScriptData.terms_80136C60[17] }, { 6, &gAiScriptData.terms_80136C60[21], &gAiScriptData.terms_80136C60[24] } },
    { { 0x7, -1.784066e-39f } },
    { 0x80136D58 },
    { { 0x1, 0.0f }, { 0x0, 0.0f }, { 0x0, 0.0f }, { 0x210F, 0.0001f }, { 0x0, 0.0f }, { 0x2111, 0.0001f }, { 0x0, 0.0f }, { 0x2104, 0.0001f }, { 0x810C, 0.0001f }, { 0x0, 0.0f }, { 0x8110, 0.9f }, { 0x2108, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2105, 0.0001f }, { 0x810D, 0.0001f }, { 0x0, 0.0f }, { 0x8111, 0.9f }, { 0x2109, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2106, 0.0001f }, { 0x810E, 0.0001f }, { 0x0, 0.0f }, { 0x8112, 0.9f }, { 0x210A, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2107, 0.0001f } },
    { 0x810F, 0x38D1B717 },
    { { 0x0, 0.0f } },
    { 0x8113, 0x3F666666 },
    { { 0x210B, 0.5f } },
    { 0x8100, 0x3DCCCCCD },
    { { 0x0, 0.0f } },
    { { 3, &gAiScriptData.terms_80136DC0[3], 0 }, { 2, &gAiScriptData.terms_80136DC0[5], 0 }, { 4, &gAiScriptData.terms_80136DC0[7], &gAiScriptData.terms_80136DC0[10] }, { 5, &gAiScriptData.terms_80136DC0[14], &gAiScriptData.terms_80136DC0[17] }, { 6, &gAiScriptData.terms_80136DC0[21], &gAiScriptData.terms_80136DC0[24] } },
    { { 0x7, -1.784559e-39f } },
    { 0x80136EB8 },
    { { 0x1, 0.0f }, { 0x0, 0.0f }, { 0x0, 0.0f }, { 0x210F, 0.0001f }, { 0x0, 0.0f }, { 0x2111, 0.0001f }, { 0x0, 0.0f }, { 0x2104, 0.0001f }, { 0x810C, 0.0001f }, { 0x0, 0.0f }, { 0x8110, 0.9f }, { 0x2108, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2105, 0.0001f }, { 0x810D, 0.0001f }, { 0x0, 0.0f }, { 0x8111, 0.9f }, { 0x2109, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2106, 0.0001f }, { 0x810E, 0.0001f }, { 0x0, 0.0f }, { 0x8112, 0.9f }, { 0x210A, 0.5f }, { 0x8100, 0.1f }, { 0x0, 0.0f }, { 0x2107, 0.0001f } },
    { 0x810F, 0x38D1B717 },
    { { 0x0, 0.0f } },
    { 0x8113, 0x3F666666 },
    { { 0x210B, 0.5f } },
    { 0x8100, 0x3DCCCCCD },
    { { 0x0, 0.0f } },
    { { 3, &gAiScriptData.terms_80136F20[3], 0 }, { 2, &gAiScriptData.terms_80136F20[5], 0 }, { 4, &gAiScriptData.terms_80136F20[7], &gAiScriptData.terms_80136F20[10] }, { 5, &gAiScriptData.terms_80136F20[14], &gAiScriptData.terms_80136F20[17] }, { 6, &gAiScriptData.terms_80136F20[21], &gAiScriptData.terms_80136F20[24] } },
    { { 0x7, -1.785052e-39f } },
    { 0x80137018 },
    { { 0x1, 0.0f }, { 0x0, 0.0f }, { 0x0, 0.0f } },
    { { 0, 0, 16, 1 }, { func_800EBAE0, 0, 0, 2 }, { 0, func_800EBB58, 27, -1 }, { func_800EBB80, 0, 0, -1 } },
    { { 0x111B, 1.0f }, { 0x0, 0.0f } },
    { { 3, &gAiScriptData.terms_801370D8[0], 0 }, { 0, 0, 0 } },
    { { 0, 0, 17, 1 }, { func_800EBBB4, 0, 0, 2 }, { 0, 0, 5, -1 } },
    { { 0, 0, 18, 1 }, { func_800EBBBC, 0, 0, 2 }, { func_800EBBFC, 0, 0, -1 } },
    { { 0, 0, 19, 1 }, { func_800EBC1C, 0, 0, -1 }, { 0, func_800EBC44, 22, -1 }, { 0, func_800EBC6C, 20, -2 }, { 0, func_800EBC94, 21, -2 } },
    { { 0x1105, 0.0001f }, { 0x0, 0.0f }, { 0x1106, 0.0001f }, { 0x0, 0.0f } },
    { { 2, &gAiScriptData.terms_801371B0[0], 0 }, { 3, &gAiScriptData.terms_801371B0[2], 0 }, { 4, 0, 0 }, { 0, 0, 0 } },
    { { 0x1104, 0.0001f }, { 0x0, 0.0f } },
    { { 1, &gAiScriptData.terms_80137200[0], 0 }, { 0, 0, 0 } },
    { { 0x1105, 0.0001f }, { 0x0, 0.0f }, { 0x1107, 0.0001f }, { 0x0, 0.0f } },
    { { 1, &gAiScriptData.terms_80137228[0], 0 }, { 1, &gAiScriptData.terms_80137228[2], 0 }, { 0, 0, 0 } },
    { { 0x1105, 0.0001f }, { 0x0, 0.0f }, { 0x1106, 0.0001f }, { 0x0, 0.0f } },
    { { 1, &gAiScriptData.terms_8013726C[0], 0 }, { 1, &gAiScriptData.terms_8013726C[2], 0 }, { 0, 0, 0 } },
    { { 0, 0, 20, 1 }, { func_800EBCBC, 0, 0, -1 }, { func_800EBCE4, func_800EBD04, 12, -1 }, { func_800EBD2C, func_800EBD4C, 12, -1 }, { func_800EBD74, 0, 0, -2 } },
    { { 0x1109, 0.0001f }, { 0x0, 0.0f } },
    { { 2, &gAiScriptData.terms_80137300[0], 0 }, { 3, 0, 0 }, { 0, 0, 0 } },
    { { 0x1102, 0.9f }, { 0x0, 0.0f }, { 0x1108, 0.0001f }, { 0x0, 0.0f } },
    { { 4, &gAiScriptData.terms_80137334[0], 0 }, { 3, &gAiScriptData.terms_80137334[2], 0 }, { 0, 0, 0 } },
    { { 0x1103, 0.9f }, { 0x0, 0.0f }, { 0x1109, 0.0001f }, { 0x0, 0.0f } },
    { { 4, &gAiScriptData.terms_80137378[0], 0 }, { 2, &gAiScriptData.terms_80137378[2], 0 }, { 0, 0, 0 } },
    { { 0, 0, 21, 1 }, { func_800EBDB4, 0, 0, -1 }, { func_800EBDDC, func_800EBDFC, 12, -1 }, { func_800EBE24, func_800EBE44, 12, -1 }, { func_800EBE6C, 0, 0, -2 } },
    { { 0x1108, 0.0001f }, { 0x0, 0.0f } },
    { { 2, &gAiScriptData.terms_8013740C[0], 0 }, { 3, 0, 0 }, { 0, 0, 0 } },
    { { 0x1102, 0.9f }, { 0x0, 0.0f }, { 0x1109, 0.0001f }, { 0x0, 0.0f } },
    { { 4, &gAiScriptData.terms_80137440[0], 0 }, { 3, &gAiScriptData.terms_80137440[2], 0 }, { 0, 0, 0 } },
    { { 0x1103, 0.9f }, { 0x0, 0.0f }, { 0x1108, 0.0001f }, { 0x0, 0.0f } },
    { { 4, &gAiScriptData.terms_80137484[0], 0 }, { 2, &gAiScriptData.terms_80137484[2], 0 }, { 0, 0, 0 } },
    { { 0, 0, 22, 1 }, { func_800EBEAC, 0, 0, -1 }, { func_800EBED4, func_800EBF28, 12, -1 }, { func_800EBF50, func_800EBFA4, 12, -1 } },
    { { 0x8100, 0.5f }, { 0x0, 0.0f } },
    { { 2, &gAiScriptData.terms_80137508[0], 0 }, { 3, 0, 0 }, { 0, 0, 0 } },
    { { 0x1102, 0.9f }, { 0x0, 0.0f }, { 0x210E, 1.0f }, { 0x0, 0.0f } },
    { { 3, &gAiScriptData.terms_8013753C[0], 0 }, { 3, &gAiScriptData.terms_8013753C[2], 0 }, { 0, 0, 0 } },
    { { 0x1103, 0.9f }, { 0x0, 0.0f }, { 0x210E, 1.0f }, { 0x0, 0.0f } },
    { { 2, &gAiScriptData.terms_80137580[0], 0 }, { 2, &gAiScriptData.terms_80137580[2], 0 }, { 0, 0, 0 } },
    { { 0, 0, 23, 1 }, { func_800EBFCC, 0, 0, -1 }, { func_800EBFF4, func_800EC014, 12, -2 }, { func_800EC03C, func_800EC05C, 12, -2 } },
    { { 0x1002, 0.0001f }, { 0x0, 0.0f } },
    { { 3, &gAiScriptData.terms_80137604[0], 0 }, { 2, 0, 0 }, { 0, 0, 0 } },
    { { 0x1002, 0.0001f }, { 0x0, 0.0f } },
    { 0xFFFFFFFE, 0x80137638 },
    { { 0x0, 0.0f }, { 0x0, 0.0f }, { 0x1007, 0.9f }, { 0x0, 0.0f } },
    { 0xFFFFFFFE, 0x80137660 },
    { { 0x0, 0.0f }, { 0x0, 0.0f } },
    { { 0, 0, 24, 1 }, { func_800EC084, 0, 23, -1 } },
    { { 0, 0, 25, 1 }, { func_800EC0D4, 0, 0, -1 }, { func_800EC128, 0, 0, -1 }, { func_800EC17C, 0, 0, -1 }, { func_800EC1D0, 0, 0, -1 } },
    { { 0x8101, 0.03333f }, { 0x0, 0.0f } },
    { { 2, &gAiScriptData.terms_801376F8[0], 0 }, { 0, 0, 0 } },
    { { 0x8101, 0.06666f }, { 0x0, 0.0f } },
    { { 3, &gAiScriptData.terms_80137720[0], 0 }, { 0, 0, 0 } },
    { { 0x8101, 0.09999f }, { 0x0, 0.0f } },
    { { 4, &gAiScriptData.terms_80137748[0], 0 }, { 0, 0, 0 } },
    { { 0, 0, 26, 1 }, { func_800EC218, 0, 0, -1 }, { func_800EC26C, 0, 0, -1 }, { func_800EC2C0, 0, 0, -1 }, { func_800EC314, 0, 0, -1 } },
    { { 0x8101, 0.016665f }, { 0x0, 0.0f } },
    { { 2, &gAiScriptData.terms_801377C0[0], 0 }, { 0, 0, 0 } },
    { { 0x8101, 0.049995f }, { 0x0, 0.0f } },
    { { 3, &gAiScriptData.terms_801377E8[0], 0 }, { 0, 0, 0 } },
    { { 0x8101, 0.083325f }, { 0x0, 0.0f } },
    { { 4, &gAiScriptData.terms_80137810[0], 0 }, { 0, 0, 0 } },
    { { 0, 0, 27, 1 }, { func_800EC35C, 0, 0, 2 }, { 0, 0, 6, 1 } },
    { { 0, 0, 28, 1 }, { 0, 0, 12, -1 } },
    { 0, &gAiScriptData.steps_80135D30[0], &gAiScriptData.steps_80135DF4[0], &gAiScriptData.steps_80135E24[0], &gAiScriptData.steps_80135E7C[0], &gAiScriptData.steps_80135FD8[0], &gAiScriptData.steps_801361FC[0], &gAiScriptData.steps_801362C0[0], &gAiScriptData.steps_801362F0[0], &gAiScriptData.steps_80136498[0], &gAiScriptData.steps_80136578[0], &gAiScriptData.steps_801365A8[0], &gAiScriptData.steps_801365C8[0], &gAiScriptData.steps_801365E8[0], &gAiScriptData.steps_801366F4[0], &gAiScriptData.steps_801367B0[0], &gAiScriptData.steps_80137098[0], &gAiScriptData.steps_80137100[0], &gAiScriptData.steps_80137130[0], &gAiScriptData.steps_80137160[0], &gAiScriptData.steps_801372B0[0], &gAiScriptData.steps_801373BC[0], &gAiScriptData.steps_801374C8[0], &gAiScriptData.steps_801375C4[0], &gAiScriptData.steps_80137688[0], &gAiScriptData.steps_801376A8[0], &gAiScriptData.steps_80137770[0], &gAiScriptData.steps_80137838[0], &gAiScriptData.steps_80137868[0] },
    { 0x45004E00 },
};
