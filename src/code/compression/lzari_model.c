#include "lzari_state.h"

/* Adaptive symbol/position model, arithmetic decoder and bit reader. */

void lzari_start_model(void)
{
    s32 ch;
    s32 sym;
    s32 i;

    gLzariSymCum[LZARI_N_CHAR] = 0;
    for (sym = LZARI_N_CHAR; sym >= 1; sym--) {
        ch = sym - 1;
        gLzariCharToSym[ch] = sym;
        gLzariSymToChar[sym] = ch;
        gLzariSymFreq[sym] = 1;
        gLzariSymCum[sym - 1] = gLzariSymCum[sym] + gLzariSymFreq[sym];
    }
    gLzariSymFreq[0] = 0;
    gLzariPositionCum[LZARI_N] = 0;
    for (i = LZARI_N; i >= 1; i--) {
        gLzariPositionCum[i - 1] = gLzariPositionCum[i] + 10000 / (i + 200);
    }
}

void lzari_update_model(s32 sym)
{
    s32 i;
    s32 c;
    s32 ch_i;
    s32 ch_sym;

    if (gLzariSymCum[0] >= LZARI_MAX_CUM) {
        c = 0;
        for (i = LZARI_N_CHAR; i > 0; i--) {
            gLzariSymCum[i] = c;
            c += (gLzariSymFreq[i] = (gLzariSymFreq[i] + 1) >> 1);
        }
        gLzariSymCum[0] = c;
    }
    for (i = sym; gLzariSymFreq[i] == gLzariSymFreq[i - 1]; i--) {
    }
    if (i < sym) {
        ch_i = gLzariSymToChar[i];
        ch_sym = gLzariSymToChar[sym];
        gLzariSymToChar[i] = ch_sym;
        gLzariSymToChar[sym] = ch_i;
        gLzariCharToSym[ch_i] = sym;
        gLzariCharToSym[ch_sym] = i;
    }
    gLzariSymFreq[i]++;
    while (--i >= 0) {
        gLzariSymCum[i]++;
    }
}

s32 lzari_decode_char(void)
{
    s32 sym;
    s32 ch;
    u32 range;

    range = gLzariHigh - gLzariLow;
    sym = lzari_search_sym(((gLzariValue - gLzariLow + 1) * gLzariSymCum[0] - 1) / range);
    gLzariHigh = gLzariLow + (range * gLzariSymCum[sym - 1]) / gLzariSymCum[0];
    gLzariLow += (range * gLzariSymCum[sym]) / gLzariSymCum[0];
    for (;;) {
        if (gLzariLow >= LZARI_Q2) {
            gLzariValue -= LZARI_Q2;
            gLzariLow -= LZARI_Q2;
            gLzariHigh -= LZARI_Q2;
        } else if (gLzariLow >= LZARI_Q1 && gLzariHigh <= LZARI_Q3) {
            gLzariValue -= LZARI_Q1;
            gLzariLow -= LZARI_Q1;
            gLzariHigh -= LZARI_Q1;
        } else if (gLzariHigh > LZARI_Q2) {
            break;
        }
        gLzariLow += gLzariLow;
        gLzariHigh += gLzariHigh;
        gLzariValue = 2 * gLzariValue + lzari_get_bit();
    }
    ch = gLzariSymToChar[sym];
    lzari_update_model(sym);
    return ch;
}

s32 lzari_decode_position(void)
{
    s32 position;
    u32 range;

    range = gLzariHigh - gLzariLow;
    position = lzari_search_position(((gLzariValue - gLzariLow + 1) * gLzariPositionCum[0] - 1) / range);
    gLzariHigh = gLzariLow + (range * gLzariPositionCum[position]) / gLzariPositionCum[0];
    gLzariLow += (range * gLzariPositionCum[position + 1]) / gLzariPositionCum[0];
    for (;;) {
        if (gLzariLow >= LZARI_Q2) {
            gLzariValue -= LZARI_Q2;
            gLzariLow -= LZARI_Q2;
            gLzariHigh -= LZARI_Q2;
        } else if (gLzariLow >= LZARI_Q1 && gLzariHigh <= LZARI_Q3) {
            gLzariValue -= LZARI_Q1;
            gLzariLow -= LZARI_Q1;
            gLzariHigh -= LZARI_Q1;
        } else if (gLzariHigh > LZARI_Q2) {
            break;
        }
        gLzariLow += gLzariLow;
        gLzariHigh += gLzariHigh;
        gLzariValue = 2 * gLzariValue + lzari_get_bit();
    }
    return position;
}

s32 lzari_search_sym(u32 x)
{
    s32 i;
    s32 j;
    s32 k;

    i = 1;
    j = LZARI_N_CHAR;
    while (i < j) {
        k = (i + j) / 2;
        if (gLzariSymCum[k] > x) {
            i = k + 1;
        } else {
            j = k;
        }
    }
    return i;
}

s32 lzari_search_position(u32 x)
{
    s32 i;
    s32 j;
    s32 k;

    i = 1;
    j = LZARI_N;
    while (i < j) {
        k = (i + j) / 2;
        if (gLzariPositionCum[k] > x) {
            i = k + 1;
        } else {
            j = k;
        }
    }
    return i - 1;
}

s32 lzari_get_bit(void)
{
    if ((gLzariBitMask >>= 1) == 0) {
        gLzariBitBuffer = *gLzariSource++;
        gLzariBitMask = 128;
    }
    return (gLzariBitBuffer & gLzariBitMask) != 0;
}
