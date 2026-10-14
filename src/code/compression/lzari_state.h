#ifndef LZARI_STATE_H
#define LZARI_STATE_H

#include "types.h"

/* LZSS with adaptive arithmetic coding (Haruhiko Okumura's LZARI) as used
 * for BattleTanx compressed resources.  Streams start with a big-endian u32
 * expanded size followed by the arithmetic-coded bit stream. */
#define LZARI_N 4096
#define LZARI_F 60
#define LZARI_THRESHOLD 2
#define LZARI_N_CHAR (256 - LZARI_THRESHOLD + LZARI_F)
#define LZARI_Q1 (1 << 15)
#define LZARI_Q2 (2 * LZARI_Q1)
#define LZARI_Q3 (3 * LZARI_Q1)
#define LZARI_Q4 (4 * LZARI_Q1)
#define LZARI_MAX_CUM (LZARI_Q1 - 1)

extern u32 gLzariLow __asm__("D_8035CD1C");
extern u32 gLzariHigh __asm__("D_8035CD20");
extern u32 gLzariValue __asm__("D_8035CD24");
extern u32 gLzariBitBuffer __asm__("D_80362104");
extern u32 gLzariBitMask __asm__("D_80362108");
extern u32 gLzariSourceSize __asm__("D_803620F4");
extern u32 gLzariDestinationSize __asm__("D_803620F8");
extern u8 *gLzariSource __asm__("D_803620FC");
extern u8 *gLzariDestination __asm__("D_80362100");
extern u32 gLzariTextSize __asm__("D_8035BCD0");
extern u8 gLzariTextBuffer[LZARI_N + LZARI_F - 1] __asm__("D_8035BCE0");
extern s32 gLzariCharToSym[LZARI_N_CHAR] __asm__("D_8035CD30");
extern s32 gLzariSymToChar[LZARI_N_CHAR + 1] __asm__("D_8035D220");
extern u32 gLzariSymFreq[LZARI_N_CHAR + 1] __asm__("D_8035D710");
extern u32 gLzariSymCum[LZARI_N_CHAR + 1] __asm__("D_8035DC00");
extern s32 gLzariPositionCum[LZARI_N + 1] __asm__("D_8035E0F0");

extern void lzari_start_decode(void) __asm__("func_800F5128");
extern void lzari_start_model(void) __asm__("func_800F5178");
extern void lzari_update_model(s32 sym) __asm__("func_800F5264");
extern s32 lzari_decode_char(void) __asm__("func_800F53B8");
extern s32 lzari_decode_position(void) __asm__("func_800F5610");
extern s32 lzari_search_sym(u32 x) __asm__("func_800F5850");
extern s32 lzari_search_position(u32 x) __asm__("func_800F58A0");
extern s32 lzari_get_bit(void) __asm__("func_800F58F0");

#endif
