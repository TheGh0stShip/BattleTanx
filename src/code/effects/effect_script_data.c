#include "types.h"

/*
 * Initialized data for the scripted particle effects driven by
 * func_800EDB20 / func_800EE000 / func_800EE4D4 (0x800ED994-0x800EE75C).
 * Layout is big-endian and every pointer is expressed as a relocatable
 * reference.  Fields whose meaning is not yet established keep offset names.
 */

typedef struct EffectParticleDef {
    u32 value00;
    u32 value04;
    s16 lifetime;
    s16 value0A;
    u8 value0C[8];
} EffectParticleDef;

typedef struct EffectScriptCommand {
    void (*handler)();
    s16 arg0;
    s16 arg1;
    s16 arg2;
    s16 arg3;
} EffectScriptCommand;

#define EFFECT_SCRIPT_LENGTH 16
#define EFFECT_SCRIPT_COUNT 28
#define EFFECT_PARTICLE_DEF_COUNT 60
#define EFFECT_COLOR_COUNT 34

typedef struct EffectSpawnPoint {
    f32 x;
    f32 z;
    s16 heading;
    s16 pad0A;
} EffectSpawnPoint;

extern void sound_duration_elapsed() __asm__("func_800EDA98");
extern void spawn_scripted_particle() __asm__("func_800EDB20");
extern void func_800EE000();
extern void func_800EE4D4();

extern EffectParticleDef gEffectParticleDefs[EFFECT_PARTICLE_DEF_COUNT];
extern u8 gEffectColors[EFFECT_COLOR_COUNT][4];
extern EffectScriptCommand gEffectScripts[EFFECT_SCRIPT_COUNT][EFFECT_SCRIPT_LENGTH];

s32 D_80137900 = 0;
s32 D_80137904 = 0;
s32 D_80137908[14] = { 17, 0, 0, 0, 1, 6, 6, 6, 25, 14, 27, 26, 1, 0 };

EffectParticleDef *gEffectParticleDefTable[63] __asm__("D_80137940") = {
    &gEffectParticleDefs[13], &gEffectParticleDefs[14], &gEffectParticleDefs[15], &gEffectParticleDefs[16],
    &gEffectParticleDefs[17], &gEffectParticleDefs[18], &gEffectParticleDefs[22], &gEffectParticleDefs[23],
    &gEffectParticleDefs[24], &gEffectParticleDefs[25], &gEffectParticleDefs[27], &gEffectParticleDefs[28],
    &gEffectParticleDefs[29], &gEffectParticleDefs[30], &gEffectParticleDefs[31], &gEffectParticleDefs[34],
    &gEffectParticleDefs[35], &gEffectParticleDefs[36], &gEffectParticleDefs[7], &gEffectParticleDefs[8],
    &gEffectParticleDefs[9], &gEffectParticleDefs[10], &gEffectParticleDefs[11], &gEffectParticleDefs[26],
    &gEffectParticleDefs[27], &gEffectParticleDefs[28], &gEffectParticleDefs[29], &gEffectParticleDefs[32],
    &gEffectParticleDefs[33], &gEffectParticleDefs[19], &gEffectParticleDefs[20], &gEffectParticleDefs[21],
    &gEffectParticleDefs[4], &gEffectParticleDefs[5], &gEffectParticleDefs[6], &gEffectParticleDefs[3],
    &gEffectParticleDefs[0], &gEffectParticleDefs[1], &gEffectParticleDefs[2], &gEffectParticleDefs[37],
    &gEffectParticleDefs[38], &gEffectParticleDefs[39], &gEffectParticleDefs[12], &gEffectParticleDefs[40],
    &gEffectParticleDefs[41], &gEffectParticleDefs[42], &gEffectParticleDefs[43], &gEffectParticleDefs[44],
    &gEffectParticleDefs[45], &gEffectParticleDefs[46], &gEffectParticleDefs[47], &gEffectParticleDefs[48],
    &gEffectParticleDefs[49], &gEffectParticleDefs[50], &gEffectParticleDefs[51], &gEffectParticleDefs[52],
    &gEffectParticleDefs[53], &gEffectParticleDefs[54], &gEffectParticleDefs[55], &gEffectParticleDefs[56],
    &gEffectParticleDefs[57], &gEffectParticleDefs[58], &gEffectParticleDefs[59],
};

EffectScriptCommand gEffectScripts[EFFECT_SCRIPT_COUNT][EFFECT_SCRIPT_LENGTH] = {
    /*  0: 0x80137A3C */ {
        { spawn_scripted_particle, 9, 0, 0, 0 },
        { sound_duration_elapsed, 128, 0, 0, 0 },
        { spawn_scripted_particle, 9, -48, 0, -48 },
        { sound_duration_elapsed, 192, 0, 0, 0 },
        { spawn_scripted_particle, 9, 48, 0, -48 },
        { sound_duration_elapsed, 256, 0, 0, 0 },
        { spawn_scripted_particle, 12, 48, 0, 48 },
        { sound_duration_elapsed, 512, 0, 0, 0 },
        { spawn_scripted_particle, 15, 0, 0, 0 },
        { sound_duration_elapsed, 576, 0, 0, 0 },
        { spawn_scripted_particle, 15, -128, 0, -128 },
        { sound_duration_elapsed, 832, 0, 0, 0 },
        { spawn_scripted_particle, 15, 128, 0, -128 },
        { spawn_scripted_particle, 15, 128, 0, 128 },
    },
    /*  1: 0x80137AFC */ {
        { func_800EE000, 18, 0, 0, 0 },
        { spawn_scripted_particle, 15, 0, 64, 0 },
        { sound_duration_elapsed, 96, 0, 0, 0 },
        { spawn_scripted_particle, 15, -128, 64, -128 },
        { sound_duration_elapsed, 192, 0, 0, 0 },
        { spawn_scripted_particle, 15, 128, 64, -128 },
        { sound_duration_elapsed, 288, 0, 0, 0 },
        { spawn_scripted_particle, 15, 128, 64, 128 },
    },
    /*  2: 0x80137BBC */ {
    },
    /*  3: 0x80137C7C */ {
        { func_800EE000, 21, 0, 0, 0 },
        { spawn_scripted_particle, 15, 0, 0, 0 },
    },
    /*  4: 0x80137D3C */ {
        { spawn_scripted_particle, 3, 0, 0, 0 },
    },
    /*  5: 0x80137DFC */ {
        { spawn_scripted_particle, 6, 0, 0, 0 },
    },
    /*  6: 0x80137EBC */ {
        { spawn_scripted_particle, 9, 0, 0, 0 },
    },
    /*  7: 0x80137F7C */ {
        { spawn_scripted_particle, 12, 0, 0, 0 },
    },
    /*  8: 0x8013803C */ {
        { spawn_scripted_particle, 15, 0, 0, 0 },
    },
    /*  9: 0x801380FC */ {
        { spawn_scripted_particle, 23, 0, 0, 0 },
    },
    /* 10: 0x801381BC */ {
        { spawn_scripted_particle, 42, 0, 0, 0 },
    },
    /* 11: 0x8013827C */ {
        { spawn_scripted_particle, 3, 0, 0, 0 },
    },
    /* 12: 0x8013833C */ {
        { spawn_scripted_particle, 29, 0, 0, 0 },
    },
    /* 13: 0x801383FC */ {
        { spawn_scripted_particle, 9, 0, 0, 0 },
        { spawn_scripted_particle, 9, -64, 0, -64 },
    },
    /* 14: 0x801384BC */ {
        { spawn_scripted_particle, 12, 0, 0, 0 },
        { spawn_scripted_particle, 12, -128, 0, -128 },
    },
    /* 15: 0x8013857C */ {
        { spawn_scripted_particle, 26, 0, 0, 0 },
        { spawn_scripted_particle, 26, -128, 0, -128 },
    },
    /* 16: 0x8013863C */ {
        { spawn_scripted_particle, 40, 0, 0, 0 },
        { spawn_scripted_particle, 40, -128, 0, -128 },
    },
    /* 17: 0x801386FC */ {
        { sound_duration_elapsed, 32, 0, 0, 0 },
        { spawn_scripted_particle, 12, 0, 0, 0 },
        { sound_duration_elapsed, 64, 0, 0, 0 },
        { spawn_scripted_particle, 9, 0, 64, 0 },
        { sound_duration_elapsed, 96, 0, 0, 0 },
        { spawn_scripted_particle, 9, 0, 128, 0 },
        { sound_duration_elapsed, 128, 0, 0, 0 },
        { spawn_scripted_particle, 9, 0, 192, 0 },
        { sound_duration_elapsed, 256, 0, 0, 0 },
        { func_800EE000, 18, 0, 0, 0 },
        { spawn_scripted_particle, 15, 0, 256, 0 },
        { spawn_scripted_particle, 15, -128, 256, -128 },
        { spawn_scripted_particle, 15, 128, 256, -128 },
        { spawn_scripted_particle, 15, 128, 256, 128 },
        { sound_duration_elapsed, 288, 0, 0, 0 },
        { func_800EE000, 19, 0, 112, 0 },
    },
    /* 18: 0x801387BC */ {
        { spawn_scripted_particle, 12, 0, 0, 0 },
        { spawn_scripted_particle, 9, 0, 64, 0 },
        { spawn_scripted_particle, 9, 0, 128, 0 },
        { spawn_scripted_particle, 9, 0, 192, 0 },
        { spawn_scripted_particle, 15, 0, 256, 0 },
        { spawn_scripted_particle, 15, -128, 256, -128 },
        { spawn_scripted_particle, 15, 128, 256, -128 },
        { spawn_scripted_particle, 15, 128, 256, 128 },
    },
    /* 19: 0x8013887C */ {
        { sound_duration_elapsed, 128, 0, 0, 0 },
        { func_800EE000, 43, 0, 0, 0 },
    },
    /* 20: 0x8013893C */ {
        { sound_duration_elapsed, 32, 0, 0, 0 },
        { spawn_scripted_particle, 12, 0, 0, 0 },
        { sound_duration_elapsed, 64, 0, 0, 0 },
        { func_800EE000, 44, 0, 10, 0 },
        { sound_duration_elapsed, 96, 0, 0, 0 },
        { spawn_scripted_particle, 9, 0, 64, 0 },
        { spawn_scripted_particle, 9, 0, 128, 0 },
        { spawn_scripted_particle, 9, 0, 192, 0 },
        { sound_duration_elapsed, 128, 0, 0, 0 },
        { spawn_scripted_particle, 15, 0, 256, 0 },
        { spawn_scripted_particle, 15, 128, 256, 128 },
        { spawn_scripted_particle, 15, 128, 256, -128 },
        { spawn_scripted_particle, 15, -128, 256, -128 },
    },
    /* 21: 0x801389FC */ {
        { spawn_scripted_particle, 45, 0, 0, 0 },
    },
    /* 22: 0x80138ABC */ {
        { spawn_scripted_particle, 48, 0, 0, 0 },
    },
    /* 23: 0x80138B7C */ {
        { spawn_scripted_particle, 51, 0, 0, 0 },
    },
    /* 24: 0x80138C3C */ {
        { spawn_scripted_particle, 53, 0, 0, 0 },
        { spawn_scripted_particle, 53, -128, 0, -128 },
    },
    /* 25: 0x80138CFC */ {
        { spawn_scripted_particle, 55, 0, 0, 0 },
    },
    /* 26: 0x80138DBC */ {
        { spawn_scripted_particle, 12, 0, 0, 0 },
        { sound_duration_elapsed, 64, 0, 0, 0 },
        { spawn_scripted_particle, 9, 0, 16, 0 },
        { spawn_scripted_particle, 9, 0, 32, 0 },
        { spawn_scripted_particle, 9, 0, 48, 0 },
    },
    /* 27: 0x80138E7C */ {
        { sound_duration_elapsed, 2048, 0, 0, 0 },
        { func_800EE4D4, 60, 0, 53, 0 },
        { func_800EE4D4, 61, 0, 53, 0 },
        { func_800EE4D4, 62, 0, 53, 0 },
    },
};

EffectScriptCommand *gEffectScriptTable[EFFECT_SCRIPT_COUNT] __asm__("D_80138F3C") = {
    gEffectScripts[17], gEffectScripts[2], gEffectScripts[4], gEffectScripts[5],
    gEffectScripts[6], gEffectScripts[7], gEffectScripts[8], gEffectScripts[9],
    gEffectScripts[17], gEffectScripts[18], gEffectScripts[3], gEffectScripts[13],
    gEffectScripts[14], gEffectScripts[15], gEffectScripts[0], gEffectScripts[11],
    gEffectScripts[12], gEffectScripts[16], gEffectScripts[10], gEffectScripts[19],
    gEffectScripts[20], gEffectScripts[21], gEffectScripts[22], gEffectScripts[23],
    gEffectScripts[24], gEffectScripts[25], gEffectScripts[26], gEffectScripts[27],
};

s32 D_80138FAC[4] = { 0, 0, 0, 0 };
s32 D_80138FBC = 0;

u8 gEffectColors[EFFECT_COLOR_COUNT][4] = {
    { 0x00, 0x00, 0x32, 0xFF }, { 0x5A, 0x5A, 0xFF, 0xFF }, { 0xFC, 0xCA, 0x00, 0xFF }, { 0xE1, 0x1E, 0x1E, 0xFF },
    { 0xFF, 0x14, 0x46, 0xFF }, { 0xE1, 0x1E, 0x1E, 0x00 }, { 0x08, 0x08, 0x08, 0xFF }, { 0x19, 0x19, 0x19, 0xFF },
    { 0x80, 0x80, 0x80, 0xFF }, { 0x40, 0x40, 0x40, 0xFF }, { 0x40, 0x40, 0x40, 0xC4 }, { 0x19, 0x19, 0x19, 0x00 },
    { 0x19, 0x19, 0x19, 0x10 }, { 0x08, 0x08, 0x08, 0xFF }, { 0x08, 0x08, 0x08, 0xC4 }, { 0x00, 0x00, 0x00, 0x00 },
    { 0x50, 0xC4, 0xC4, 0xFF }, { 0x70, 0x70, 0xF1, 0xC4 }, { 0xA0, 0xA0, 0x4B, 0xFF }, { 0xF9, 0x7E, 0x9B, 0xFF },
    { 0xFD, 0x70, 0x70, 0xFF }, { 0x70, 0xF7, 0xC9, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xFC, 0xCA, 0x80, 0xFF },
    { 0x19, 0x19, 0x19, 0x40 }, { 0x0A, 0x0A, 0x5C, 0xC4 }, { 0x3C, 0x3C, 0x1C, 0xFF }, { 0x80, 0xDD, 0x05, 0xFF },
    { 0x03, 0x62, 0x0E, 0xFF }, { 0x00, 0x31, 0x07, 0xFF }, { 0x6C, 0x65, 0x59, 0xFF }, { 0xDC, 0xC8, 0x0F, 0xFF },
    { 0x78, 0x64, 0x0F, 0xFF }, { 0x5A, 0x00, 0x1E, 0xFF },
};

u8 *gEffectColorTable[33] __asm__("D_80139048") = {
    gEffectColors[2], gEffectColors[3], gEffectColors[7], gEffectColors[11],
    gEffectColors[13], gEffectColors[14], gEffectColors[15], gEffectColors[1],
    gEffectColors[0], gEffectColors[16], gEffectColors[17], gEffectColors[18],
    gEffectColors[19], gEffectColors[20], gEffectColors[21], gEffectColors[12],
    gEffectColors[5], gEffectColors[22], gEffectColors[4], gEffectColors[9],
    gEffectColors[23], gEffectColors[10], gEffectColors[8], gEffectColors[24],
    gEffectColors[6], gEffectColors[25], gEffectColors[26], gEffectColors[27],
    gEffectColors[28], gEffectColors[29], gEffectColors[30], gEffectColors[31],
    gEffectColors[32],
};

EffectParticleDef gEffectParticleDefs[EFFECT_PARTICLE_DEF_COUNT] = {
    { 0x08000000, 0x00600000, 10, 75, { 0x01, 0x82, 0x14, 0x02, 0x01, 0x04, 0x00, 0x00 } },
    { 0x08000000, 0x00400000, 75, 115, { 0x01, 0x02, 0x02, 0x02, 0x04, 0x05, 0x00, 0x00 } },
    { 0x08000000, 0x00400000, 115, 115, { 0x00, 0x02, 0x02, 0x02, 0x05, 0x06, 0x00, 0x00 } },
    { 0x00000000, 0x06000000, 8, 8, { 0x00, 0x0B, 0x13, 0x13, 0x02, 0x02, 0x00, 0x00 } },
    { 0x06000000, 0x01800000, 1, 4, { 0x01, 0x0B, 0x11, 0x00, 0x00, 0x12, 0x00, 0x00 } },
    { 0x06000000, 0x00800000, 4, 2, { 0x01, 0x0B, 0x12, 0x01, 0x00, 0x02, 0x00, 0x00 } },
    { 0x06000000, 0x00800000, 2, 2, { 0x00, 0x0B, 0x12, 0x12, 0x01, 0x01, 0x00, 0x00 } },
    { 0x07000000, 0x0C000000, 50, 8000, { 0x00, 0x10, 0x00, 0x02, 0x01, 0x04, 0x00, 0x00 } },
    { 0x05000000, 0x0C000000, 50, 8000, { 0x00, 0x00, 0x00, 0x02, 0x01, 0x04, 0x00, 0x00 } },
    { 0x07000000, 0x0C000000, 50, 8000, { 0x00, 0x00, 0x09, 0x09, 0x0A, 0x0A, 0x00, 0x00 } },
    { 0x07000000, 0x0C000000, 50, 8000, { 0x00, 0x00, 0x0B, 0x0B, 0x0D, 0x0D, 0x00, 0x00 } },
    { 0x07000000, 0x0C000000, 50, 8000, { 0x00, 0x00, 0x09, 0x09, 0x0E, 0x0E, 0x00, 0x00 } },
    { 0x00000000, 0x01C00000, 20, 150, { 0x00, 0x0A, 0x07, 0x02, 0x08, 0x04, 0x00, 0x00 } },
    { 0x00000000, 0x00800000, 20, 80, { 0x01, 0x0A, 0x00, 0x18, 0x01, 0x04, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 80, 250, { 0x01, 0x0A, 0x18, 0x18, 0x04, 0x04, 0x00, 0x00 } },
    { 0x00000000, 0x03000000, 250, 75, { 0x00, 0x0A, 0x18, 0x18, 0x04, 0x06, 0x00, 0x00 } },
    { 0x00000000, 0x00C00000, 50, 25, { 0x01, 0x0A, 0x00, 0x02, 0x01, 0x04, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 25, 45, { 0x01, 0x0A, 0x02, 0x02, 0x04, 0x05, 0x00, 0x00 } },
    { 0x00000000, 0x00800000, 45, 45, { 0x00, 0x0A, 0x02, 0x02, 0x05, 0x06, 0x00, 0x00 } },
    { 0x00000000, 0x00C00000, 10, 25, { 0x01, 0x0A, 0x00, 0x02, 0x01, 0x07, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 25, 37, { 0x01, 0x0A, 0x0B, 0x0B, 0x0A, 0x0A, 0x00, 0x00 } },
    { 0x00000000, 0x00800000, 37, 37, { 0x00, 0x0A, 0x0B, 0x0B, 0x0A, 0x03, 0x00, 0x00 } },
    { 0x00000000, 0x00C00000, 10, 50, { 0x01, 0x0A, 0x00, 0x02, 0x01, 0x04, 0x00, 0x00 } },
    { 0x00000000, 0x10000000, 50, 75, { 0x01, 0x0A, 0x02, 0x02, 0x04, 0x05, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 75, 75, { 0x00, 0x0A, 0x02, 0x02, 0x05, 0x06, 0x00, 0x00 } },
    { 0x00000000, 0x00C00000, 50, 150, { 0x01, 0x0A, 0x00, 0x02, 0x01, 0x04, 0x00, 0x00 } },
    { 0x00000000, 0x00C00000, 50, 150, { 0x01, 0x0A, 0x02, 0x02, 0x04, 0x04, 0x00, 0x00 } },
    { 0x00000000, 0x02000000, 150, 150, { 0x01, 0x0A, 0x02, 0x02, 0x04, 0x05, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 150, 150, { 0x00, 0x0A, 0x02, 0x02, 0x05, 0x06, 0x00, 0x00 } },
    { 0x00000000, 0x01800000, 50, 300, { 0x01, 0x0A, 0x00, 0x02, 0x01, 0x04, 0x00, 0x00 } },
    { 0x00000000, 0x04000000, 300, 450, { 0x01, 0x0A, 0x02, 0x02, 0x04, 0x05, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 450, 450, { 0x00, 0x0A, 0x02, 0x02, 0x05, 0x06, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 300, 450, { 0x01, 0x0A, 0x02, 0x02, 0x05, 0x05, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 450, 450, { 0x00, 0x0A, 0x02, 0x02, 0x05, 0x06, 0x00, 0x00 } },
    { 0x00000000, 0x01800000, 50, 600, { 0x01, 0x0A, 0x00, 0x02, 0x01, 0x04, 0x00, 0x00 } },
    { 0x00000000, 0x04000000, 600, 900, { 0x01, 0x0A, 0x02, 0x02, 0x04, 0x05, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 900, 900, { 0x00, 0x0A, 0x02, 0x02, 0x05, 0x06, 0x00, 0x00 } },
    { 0x00000000, 0x00C00000, 50, 300, { 0x01, 0x0A, 0x16, 0x16, 0x17, 0x17, 0x00, 0x00 } },
    { 0x00000000, 0x06000000, 300, 525, { 0x01, 0x0A, 0x16, 0x16, 0x0F, 0x17, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 525, 525, { 0x00, 0x0A, 0x16, 0x16, 0x17, 0x03, 0x00, 0x00 } },
    { 0x07000000, 0x06000000, 50, 2000, { 0x00, 0x00, 0x07, 0x02, 0x08, 0x04, 0x00, 0x00 } },
    { 0x07000000, 0x00F00000, 50, 600, { 0x00, 0x10, 0x00, 0x02, 0x01, 0x04, 0x00, 0x00 } },
    { 0x00000000, 0x00C00000, 10, 25, { 0x01, 0x0A, 0x00, 0x18, 0x01, 0x07, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 25, 37, { 0x01, 0x0A, 0x1A, 0x1A, 0x19, 0x19, 0x00, 0x00 } },
    { 0x00000000, 0x00800000, 37, 37, { 0x00, 0x0A, 0x1A, 0x1A, 0x19, 0x03, 0x00, 0x00 } },
    { 0x00000000, 0x01800000, 50, 300, { 0x01, 0x0A, 0x1B, 0x1D, 0x1B, 0x04, 0x00, 0x00 } },
    { 0x00000000, 0x04000000, 300, 450, { 0x01, 0x0A, 0x1D, 0x1D, 0x04, 0x05, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 450, 450, { 0x00, 0x0A, 0x1D, 0x1D, 0x05, 0x06, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 10, 18, { 0x01, 0x0A, 0x0B, 0x0B, 0x0A, 0x0A, 0x00, 0x00 } },
    { 0x00000000, 0x00800000, 18, 18, { 0x00, 0x0A, 0x0B, 0x0B, 0x0A, 0x03, 0x00, 0x00 } },
    { 0x00000000, 0x06000000, 300, 525, { 0x01, 0x0A, 0x1E, 0x1E, 0x0F, 0x17, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 525, 525, { 0x00, 0x0A, 0x1E, 0x1E, 0x17, 0x03, 0x00, 0x00 } },
    { 0x00000000, 0x00C00000, 5, 10, { 0x01, 0x0A, 0x00, 0x18, 0x01, 0x13, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 10, 15, { 0x01, 0x0A, 0x18, 0x18, 0x13, 0x13, 0x00, 0x00 } },
    { 0x00000000, 0x00800000, 15, 15, { 0x00, 0x0A, 0x18, 0x05, 0x13, 0x17, 0x00, 0x00 } },
    { 0x00000000, 0x0B000000, 15, 270, { 0x01, 0x02, 0x1F, 0x1F, 0x20, 0x20, 0x00, 0x00 } },
    { 0x00000000, 0x01000000, 270, 270, { 0x00, 0x0A, 0x1F, 0x1F, 0x20, 0x06, 0x00, 0x00 } },
    { 0x07000000, 0x00000258, 95, 250, { 0x00, 0x08, 0x1F, 0x1F, 0x01, 0x04, 0x00, 0x00 } },
    { 0x07000000, 0x00000258, 200, 100, { 0x00, 0x08, 0x07, 0x01, 0x04, 0x00, 0x00, 0x00 } },
    { 0x07000000, 0x00000258, 150, 150, { 0x00, 0x08, 0x12, 0x12, 0x01, 0x04, 0x00, 0x00 } },
};

EffectSpawnPoint gEffectSpawnPointsA[5] __asm__("D_8013957C") = {
    { 1079.0f, 2740.0f, -729, 0 },
    { 1257.0f, 2854.0f, 6553, 0 },
    { 1395.0f, 2639.0f, 17476, 0 },
    { 616.0f, 2700.0f, -9467, 0 },
    { 870.0f, 2765.0f, -729, 0 },
};

EffectSpawnPoint gEffectSpawnPointsB[5] __asm__("D_801395B8") = {
    { 565.0f, -3603.0f, -16020, 0 },
    { 165.0f, -3603.0f, -16385, 0 },
    { 200.0f, -3829.0f, -23120, 0 },
    { 192.0f, -3365.0f, -15838, 0 },
    { 370.0f, -4097.0f, -16020, 0 },
};

u32 D_801395F4[3] = { 0x310000D0, 0x5F400C02, 0x330000D0 };
