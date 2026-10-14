#include "types.h"

/*
 * Primitive marker models (a unit cube and a wedge with their face index
 * lists), marker colours, and the per-wave opponent setup table read by the
 * game-mode and HUD code (0x8007B2xx, 0x800F6Axx).  Each wave carries three
 * groups of four AI skill profiles.  Fields without established meaning keep
 * offset-based names.
 */

typedef struct AiSkillProfile {
    f32 value00;
    f32 value04;
    s32 value08;
    s32 value0C;
    s32 value10;
    s16 (*rangeA)[4];
    s16 (*rangeB)[4];
    u8 value1C[4];
    u8 value20;
    u8 pad21[3];
} AiSkillProfile;

typedef struct OpponentWave {
    s32 header[7];
    AiSkillProfile skills[3][4];
    s32 trailer[18];
    u8 color[4];
    s32 duration;
    f32 value21C;
} OpponentWave;

s32 D_80142B50[4] = { 0, 1024, 0, 1024 };
s32 D_80142B60[4] = { 0, 0, 1024, 1024 };
s16 D_80142B70[8] = { 5, 0, 7, 4, 1, 2, 3, 6 };

f32 gMarkerCubeVertices[8][3] __asm__("D_80142B80") = {
    { -1.0f, -1.0f, -1.0f },
    { -1.0f, -1.0f, 1.0f },
    { 1.0f, -1.0f, 1.0f },
    { 1.0f, -1.0f, -1.0f },
    { -1.0f, 1.0f, -1.0f },
    { -1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, -1.0f },
};
s32 gMarkerCubeFaces[4][4] __asm__("D_80142BE0") = {
    { 0, 1, 5, 4 },
    { 1, 2, 6, 5 },
    { 2, 3, 7, 6 },
    { 3, 0, 4, 7 },
};

f32 gMarkerWedgeVertices[6][3] __asm__("D_80142C20") = {
    { -0.5f, -1.0f, 0.288f },
    { 0.5f, -1.0f, 0.288f },
    { 0.0f, -1.0f, -0.577f },
    { -0.5f, 1.0f, 0.288f },
    { 0.5f, 1.0f, 0.288f },
    { 0.0f, 1.0f, -0.577f },
};
s32 gMarkerWedgeFaces[3][4] __asm__("D_80142C68") = {
    { 0, 1, 4, 3 },
    { 1, 2, 5, 4 },
    { 2, 0, 3, 5 },
};

u8 gMarkerColors[10][4] __asm__("D_80142C98") = {
    { 0xFF, 0xFF, 0x00, 0xFF },
    { 0xFF, 0xFF, 0x40, 0xFF },
    { 0xFF, 0x00, 0x00, 0xFF },
    { 0x80, 0x00, 0x00, 0xFF },
    { 0x80, 0x80, 0x80, 0xFF },
    { 0x40, 0x40, 0x00, 0xFF },
    { 0xFF, 0xFF, 0x00, 0xFF },
    { 0xFF, 0xFF, 0x40, 0xFF },
    { 0xFF, 0x00, 0x00, 0xFF },
    { 0x80, 0x00, 0x00, 0xFF },
};
u32 D_80142CC0[4] = { 0x000000A5, 0xC7B281BB, 0x8B200416, 0x59004900 };
s32 D_80142CD0 = 8;
u8 D_80142CD4[5][4] = {
    { 0x00, 0x00, 0x00, 0xFF },
    { 0xFF, 0xFF, 0x00, 0x80 },
    { 0xFF, 0x60, 0x00, 0x80 },
    { 0xFF, 0x00, 0x00, 0xFF },
    { 0x80, 0x00, 0x00, 0xFF },
};
u16 D_80142CE8[8] = { 0xFF00, 0x4800, 0x5200, 0x4500, 0x0000, 0x0000, 0x0000, 0x0000 };

s16 gAiRangeTable[30][4] __asm__("D_80142CF8") = {
    { 7, 95, 100, 50 },
    { 7, 95, 95, 45 },
    { 7, 90, 90, 40 },
    { 2, 7, 14, 14 },
    { 2, 10, 17, 17 },
    { 3, 13, 20, 20 },
    { 7, 100, 100, 60 },
    { 7, 95, 95, 50 },
    { 7, 100, 100, 50 },
    { 7, 95, 95, 55 },
    { 13, 95, 100, 50 },
    { 11, 95, 95, 45 },
    { 9, 90, 90, 40 },
    { 13, 100, 100, 60 },
    { 10, 95, 95, 50 },
    { 7, 90, 90, 40 },
    { 13, 100, 100, 50 },
    { 10, 95, 95, 55 },
    { 6, 90, 90, 40 },
    { 13, 100, 100, 50 },
    { 10, 95, 95, 45 },
    { 6, 90, 90, 40 },
    { 1, 7, 14, 14 },
    { 1, 10, 17, 17 },
    { 2, 13, 20, 20 },
    { 1, 7, 14, 7 },
    { 1, 10, 17, 15 },
    { 2, 13, 20, 20 },
    { 2, 10, 17, 17 },
    { 3, 13, 20, 20 },
};

OpponentWave gOpponentWaves[17] __asm__("D_80142DE8") = {
    /*  0: 0x80142DE8 */ {
        { 5, 1, 0, 9, 0, 0, 0 },
        {
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[3], &gAiRangeTable[0], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 166, 301, 250, &gAiRangeTable[25], &gAiRangeTable[10], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0x00, 0x00, 0x00, 0x00 }, 0x00 },
                { 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0x00, 0x00, 0x00, 0x00 }, 0x00 },
            },
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 120, 200, 250, &gAiRangeTable[26], &gAiRangeTable[11], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0x00, 0x00, 0x00, 0x00 }, 0x00 },
                { 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0x00, 0x00, 0x00, 0x00 }, 0x00 },
            },
            {
                { 0.4f, 0.4f, 0, 0, 0, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x1E, 0x1E, 0x1E }, 0x5A },
                { 0.4f, 0.4f, 100, 150, 250, &gAiRangeTable[27], &gAiRangeTable[12], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0x00, 0x00, 0x00, 0x00 }, 0x00 },
                { 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0x00, 0x00, 0x00, 0x00 }, 0x00 },
            },
        },
        { 1, 2, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 180, 30.0f,
    },
    /*  1: 0x80143008 */ {
        { 4, 2, 1, 9, 0, 0, 0 },
        {
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[3], &gAiRangeTable[0], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[10], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[10], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0x00, 0x00, 0x00, 0x00 }, 0x00 },
            },
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[11], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[11], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0x00, 0x00, 0x00, 0x00 }, 0x00 },
            },
            {
                { 0.4f, 0.4f, 0, 0, 0, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x1E, 0x1E, 0x1E }, 0x5A },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[12], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[12], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.0f, 0.0f, 0, 0, 0, 0, 0, { 0x00, 0x00, 0x00, 0x00 }, 0x00 },
            },
        },
        { 1, 3, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 180, 30.0f,
    },
    /*  2: 0x80143228 */ {
        { 5, 3, 2, 9, 0, 0, 0 },
        {
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[3], &gAiRangeTable[0], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[10], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[10], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[10], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
            },
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[11], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[11], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[11], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
            },
            {
                { 0.4f, 0.4f, 0, 0, 0, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x1E, 0x1E, 0x1E }, 0x5A },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[12], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[12], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[12], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
            },
        },
        { 1, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 300, 30.0f,
    },
    /*  3: 0x80143448 */ {
        { 4, 4, 3, 9, 0, 0, 0 },
        {
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[3], &gAiRangeTable[0], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[10], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[10], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[10], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
            },
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[11], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[11], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[11], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
            },
            {
                { 0.4f, 0.4f, 0, 0, 0, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x1E, 0x1E, 0x1E }, 0x5A },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[12], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[12], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[12], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
            },
        },
        { 1, 3, 0, 1, 1, 1, 0, 0, 0, 0, 0, -1, 0, 0, 2, 0, 0, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 480, 30.0f,
    },
    /*  4: 0x80143668 */ {
        { 7, 5, 4, 12, 13, 13, 13 },
        {
            {
                { 0.7f, 0.4f, 50, 50, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0E, 0x64, 0x64, 0x64 }, 0xC8 },
                { 0.3f, 0.3f, 180, 300, 250, &gAiRangeTable[3], &gAiRangeTable[0], { 0x08, 0x32, 0x19, 0x19 }, 0x5A },
                { 0.3f, 0.3f, 180, 300, 250, &gAiRangeTable[3], &gAiRangeTable[0], { 0x08, 0x32, 0x19, 0x19 }, 0x5A },
                { 0.3f, 0.3f, 180, 300, 250, &gAiRangeTable[3], &gAiRangeTable[0], { 0x08, 0x32, 0x19, 0x19 }, 0x5A },
            },
            {
                { 0.7f, 0.4f, 50, 50, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0E, 0x64, 0x64, 0x64 }, 0xC8 },
                { 0.4f, 0.4f, 150, 250, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x2D, 0x14, 0x14 }, 0x64 },
                { 0.4f, 0.4f, 150, 250, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x2D, 0x14, 0x14 }, 0x64 },
                { 0.4f, 0.4f, 150, 250, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x2D, 0x14, 0x14 }, 0x64 },
            },
            {
                { 0.7f, 0.4f, 50, 50, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0E, 0x64, 0x64, 0x64 }, 0xC8 },
                { 0.5f, 0.5f, 120, 200, 250, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x28, 0x0F, 0x0F }, 0x64 },
                { 0.5f, 0.5f, 120, 200, 250, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x28, 0x0F, 0x0F }, 0x64 },
                { 0.5f, 0.5f, 120, 200, 250, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x28, 0x0F, 0x0F }, 0x64 },
            },
        },
        { 1, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 0, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 0, 30.0f,
    },
    /*  5: 0x80143888 */ {
        { 4, 6, 5, 9, 8, 8, 8 },
        {
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[3], &gAiRangeTable[6], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[13], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[13], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[13], { 0x08, 0x2D, 0x1E, 0x32 }, 0x5A },
            },
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[4], &gAiRangeTable[7], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[14], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[14], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[14], { 0x0A, 0x23, 0x19, 0x28 }, 0x75 },
            },
            {
                { 0.4f, 0.4f, 0, 0, 0, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x1E, 0x1E, 0x1E }, 0x5A },
                { 0.4f, 0.4f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[15], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[15], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[15], { 0x0E, 0x1E, 0x14, 0x23 }, 0x82 },
            },
        },
        { 1, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, -1, -1, 0, 2, 0, 0, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 720, 30.0f,
    },
    /*  6: 0x80143AA8 */ {
        { 3, 7, 6, 9, 8, 8, 8 },
        {
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[3], &gAiRangeTable[6], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[13], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[13], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[13], { 0x08, 0x2D, 0x1E, 0x32 }, 0x5A },
            },
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[4], &gAiRangeTable[7], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[14], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[14], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[14], { 0x0A, 0x23, 0x19, 0x28 }, 0x75 },
            },
            {
                { 0.4f, 0.4f, 0, 0, 0, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x1E, 0x1E, 0x1E }, 0x5A },
                { 0.4f, 0.4f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[15], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[15], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[15], { 0x0E, 0x1E, 0x14, 0x23 }, 0x82 },
            },
        },
        { 1, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, -1, -1, -1, 2, 0, 7, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 720, 30.0f,
    },
    /*  7: 0x80143CC8 */ {
        { 3, 8, 7, 9, 8, 8, 6 },
        {
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[3], &gAiRangeTable[6], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[13], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[13], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[13], { 0x08, 0x2D, 0x1E, 0x32 }, 0x5A },
            },
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[4], &gAiRangeTable[7], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[14], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[14], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[14], { 0x0A, 0x23, 0x19, 0x28 }, 0x75 },
            },
            {
                { 0.4f, 0.4f, 0, 0, 0, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x1E, 0x1E, 0x1E }, 0x5A },
                { 0.4f, 0.4f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[15], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[15], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[15], { 0x0E, 0x1E, 0x14, 0x23 }, 0x82 },
            },
        },
        { 1, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, -1, -1, -1, 2, 0, 11, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 1200, 30.0f,
    },
    /*  8: 0x80143EE8 */ {
        { 7, 9, 8, 12, 13, 13, 13 },
        {
            {
                { 0.7f, 0.4f, 50, 50, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0E, 0x64, 0x64, 0x64 }, 0xC8 },
                { 0.3f, 0.3f, 180, 300, 250, &gAiRangeTable[3], &gAiRangeTable[0], { 0x08, 0x32, 0x19, 0x19 }, 0x5A },
                { 0.3f, 0.3f, 180, 300, 250, &gAiRangeTable[3], &gAiRangeTable[0], { 0x08, 0x32, 0x19, 0x19 }, 0x5A },
                { 0.3f, 0.3f, 180, 300, 250, &gAiRangeTable[3], &gAiRangeTable[0], { 0x08, 0x32, 0x19, 0x19 }, 0x5A },
            },
            {
                { 0.7f, 0.4f, 50, 50, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0E, 0x64, 0x64, 0x64 }, 0xC8 },
                { 0.4f, 0.4f, 150, 250, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x2D, 0x14, 0x14 }, 0x64 },
                { 0.4f, 0.4f, 150, 250, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x2D, 0x14, 0x14 }, 0x64 },
                { 0.4f, 0.4f, 150, 250, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x2D, 0x14, 0x14 }, 0x64 },
            },
            {
                { 0.7f, 0.4f, 50, 50, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0E, 0x64, 0x64, 0x64 }, 0xC8 },
                { 0.5f, 0.5f, 120, 200, 250, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x28, 0x0F, 0x0F }, 0x64 },
                { 0.5f, 0.5f, 120, 200, 250, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x28, 0x0F, 0x0F }, 0x64 },
                { 0.5f, 0.5f, 120, 200, 250, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x28, 0x0F, 0x0F }, 0x64 },
            },
        },
        { 1, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 0, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 120, 30.0f,
    },
    /*  9: 0x80144108 */ {
        { 4, 10, 9, 9, 5, 3, 1 },
        {
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[3], &gAiRangeTable[8], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[16], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[16], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[16], { 0x08, 0x2D, 0x1E, 0x32 }, 0x5A },
            },
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[4], &gAiRangeTable[9], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[17], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[17], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[17], { 0x0A, 0x23, 0x19, 0x28 }, 0x75 },
            },
            {
                { 0.4f, 0.4f, 0, 0, 0, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x1E, 0x1E, 0x1E }, 0x5A },
                { 0.4f, 0.4f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[18], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[18], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[18], { 0x0E, 0x1E, 0x14, 0x23 }, 0x82 },
            },
        },
        { 1, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, -1, -1, -1, 2, 0, 4, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 720, 30.0f,
    },
    /* 10: 0x80144328 */ {
        { 3, 11, 10, 9, 5, 3, 1 },
        {
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[3], &gAiRangeTable[8], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[16], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[16], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[16], { 0x08, 0x2D, 0x1E, 0x32 }, 0x5A },
            },
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[4], &gAiRangeTable[9], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[17], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[17], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[17], { 0x0A, 0x23, 0x19, 0x28 }, 0x75 },
            },
            {
                { 0.4f, 0.4f, 0, 0, 0, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x1E, 0x1E, 0x1E }, 0x5A },
                { 0.4f, 0.4f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[18], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[18], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[18], { 0x0E, 0x1E, 0x14, 0x23 }, 0x82 },
            },
        },
        { 1, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, -1, -1, -1, 2, 0, 10, 0 },
        { 0xC8, 0xC8, 0xC8, 0x00 }, 1200, 30.0f,
    },
    /* 11: 0x80144548 */ {
        { 3, 12, 11, 9, 5, 3, 1 },
        {
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[3], &gAiRangeTable[8], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[16], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[16], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[16], { 0x08, 0x2D, 0x1E, 0x32 }, 0x5A },
            },
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[4], &gAiRangeTable[9], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[17], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[17], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[17], { 0x0A, 0x23, 0x19, 0x28 }, 0x75 },
            },
            {
                { 0.4f, 0.4f, 0, 0, 0, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x1E, 0x1E, 0x1E }, 0x5A },
                { 0.4f, 0.4f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[18], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[18], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[18], { 0x0E, 0x1E, 0x14, 0x23 }, 0x82 },
            },
        },
        { 1, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, -1, -1, -1, 2, 0, 6, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 1080, 30.0f,
    },
    /* 12: 0x80144768 */ {
        { 7, 13, 12, 12, 13, 13, 13 },
        {
            {
                { 0.7f, 0.4f, 50, 50, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0E, 0x64, 0x64, 0x64 }, 0xC8 },
                { 0.3f, 0.3f, 180, 300, 250, &gAiRangeTable[3], &gAiRangeTable[0], { 0x08, 0x32, 0x19, 0x19 }, 0x5A },
                { 0.3f, 0.3f, 180, 300, 250, &gAiRangeTable[3], &gAiRangeTable[0], { 0x08, 0x32, 0x19, 0x19 }, 0x5A },
                { 0.3f, 0.3f, 180, 300, 250, &gAiRangeTable[3], &gAiRangeTable[0], { 0x08, 0x32, 0x19, 0x19 }, 0x5A },
            },
            {
                { 0.7f, 0.4f, 50, 50, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0E, 0x64, 0x64, 0x64 }, 0xC8 },
                { 0.4f, 0.4f, 150, 250, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x2D, 0x14, 0x14 }, 0x64 },
                { 0.4f, 0.4f, 150, 250, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x2D, 0x14, 0x14 }, 0x64 },
                { 0.4f, 0.4f, 150, 250, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x2D, 0x14, 0x14 }, 0x64 },
            },
            {
                { 0.7f, 0.4f, 50, 50, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0E, 0x64, 0x64, 0x64 }, 0xC8 },
                { 0.5f, 0.5f, 120, 200, 250, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x28, 0x0F, 0x0F }, 0x64 },
                { 0.5f, 0.5f, 120, 200, 250, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x28, 0x0F, 0x0F }, 0x64 },
                { 0.5f, 0.5f, 120, 200, 250, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x28, 0x0F, 0x0F }, 0x64 },
            },
        },
        { 1, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 0, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 120, 30.0f,
    },
    /* 13: 0x80144988 */ {
        { 4, 14, 13, 9, 6, 4, 7 },
        {
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[3], &gAiRangeTable[8], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[19], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[19], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[19], { 0x08, 0x2D, 0x1E, 0x32 }, 0x5A },
            },
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[4], &gAiRangeTable[9], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[20], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[20], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[20], { 0x0A, 0x23, 0x19, 0x28 }, 0x75 },
            },
            {
                { 0.4f, 0.4f, 0, 0, 0, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x1E, 0x1E, 0x1E }, 0x5A },
                { 0.4f, 0.4f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[21], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[21], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[21], { 0x0E, 0x1E, 0x14, 0x23 }, 0x82 },
            },
        },
        { 1, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, -1, -1, -1, 2, 0, 0, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 1500, 30.0f,
    },
    /* 14: 0x80144BA8 */ {
        { 3, 15, 14, 9, 6, 4, 7 },
        {
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[3], &gAiRangeTable[8], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[19], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[19], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[19], { 0x08, 0x2D, 0x1E, 0x32 }, 0x5A },
            },
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[4], &gAiRangeTable[9], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[20], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[20], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[20], { 0x0A, 0x23, 0x19, 0x28 }, 0x75 },
            },
            {
                { 0.4f, 0.4f, 0, 0, 0, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x1E, 0x1E, 0x1E }, 0x5A },
                { 0.4f, 0.4f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[21], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[21], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[21], { 0x0E, 0x1E, 0x14, 0x23 }, 0x82 },
            },
        },
        { 1, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, -1, -1, -1, 2, 0, 6, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 900, 30.0f,
    },
    /* 15: 0x80144DC8 */ {
        { 7, 17, 15, 12, 13, 13, 13 },
        {
            {
                { 0.7f, 0.4f, 50, 50, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0E, 0x64, 0x64, 0x64 }, 0xC8 },
                { 0.3f, 0.3f, 180, 300, 250, &gAiRangeTable[3], &gAiRangeTable[0], { 0x08, 0x32, 0x19, 0x19 }, 0x5A },
                { 0.3f, 0.3f, 180, 300, 250, &gAiRangeTable[3], &gAiRangeTable[0], { 0x08, 0x32, 0x19, 0x19 }, 0x5A },
                { 0.3f, 0.3f, 180, 300, 250, &gAiRangeTable[3], &gAiRangeTable[0], { 0x08, 0x32, 0x19, 0x19 }, 0x5A },
            },
            {
                { 0.7f, 0.4f, 50, 50, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0E, 0x64, 0x64, 0x64 }, 0xC8 },
                { 0.4f, 0.4f, 150, 250, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x2D, 0x14, 0x14 }, 0x64 },
                { 0.4f, 0.4f, 150, 250, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x2D, 0x14, 0x14 }, 0x64 },
                { 0.4f, 0.4f, 150, 250, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0A, 0x2D, 0x14, 0x14 }, 0x64 },
            },
            {
                { 0.7f, 0.4f, 50, 50, 250, &gAiRangeTable[4], &gAiRangeTable[1], { 0x0E, 0x64, 0x64, 0x64 }, 0xC8 },
                { 0.5f, 0.5f, 120, 200, 250, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x28, 0x0F, 0x0F }, 0x64 },
                { 0.5f, 0.5f, 120, 200, 250, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x28, 0x0F, 0x0F }, 0x64 },
                { 0.5f, 0.5f, 120, 200, 250, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x28, 0x0F, 0x0F }, 0x64 },
            },
        },
        { 1, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 0, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 120, 30.0f,
    },
    /* 16: 0x80144FE8 */ {
        { 3, 16, 16, 9, 7, 7, 7 },
        {
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[3], &gAiRangeTable[8], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[19], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[19], { 0x08, 0x32, 0x1E, 0x32 }, 0x46 },
                { 0.3f, 0.8f, 166, 301, 250, &gAiRangeTable[22], &gAiRangeTable[19], { 0x08, 0x2D, 0x1E, 0x32 }, 0x5A },
            },
            {
                { 0.2f, 0.2f, 0, 0, 0, &gAiRangeTable[4], &gAiRangeTable[9], { 0x0A, 0x1E, 0x1E, 0x1E }, 0x50 },
                { 0.2f, 0.2f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[20], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[20], { 0x0A, 0x2D, 0x19, 0x28 }, 0x50 },
                { 0.3f, 0.8f, 120, 200, 250, &gAiRangeTable[23], &gAiRangeTable[20], { 0x0A, 0x23, 0x19, 0x28 }, 0x75 },
            },
            {
                { 0.4f, 0.4f, 0, 0, 0, &gAiRangeTable[5], &gAiRangeTable[2], { 0x0E, 0x1E, 0x1E, 0x1E }, 0x5A },
                { 0.4f, 0.4f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[21], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[21], { 0x0E, 0x28, 0x14, 0x23 }, 0x75 },
                { 0.3f, 0.8f, 100, 150, 250, &gAiRangeTable[24], &gAiRangeTable[21], { 0x0E, 0x1E, 0x14, 0x23 }, 0x82 },
            },
        },
        { 1, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, -1, -1, -1, 2, 0, 6, 0 },
        { 0x33, 0x33, 0x33, 0x00 }, 1800, 30.0f,
    },
};

s32 D_80145208[2] = { 1056964608, 1056964608 };
