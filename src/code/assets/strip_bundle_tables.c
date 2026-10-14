/* Strip bundle ROM tables (.data 0x80134B88-0x80134BD8), consumed by
 * load_strip_bundle (func_800CA8C0).  Each entry is a cartridge PI address
 * (0xB0000000 + ROM offset) of an LZARI-compressed strip bundle; strip i spans
 * [gStripBundleRomStart[i], gStripBundleRomEnd[i]).  Data-only reconstruction
 * verified against the BattleTanx USA Rev 0 ROM. */
#include "types.h"

extern u8 D_B02E2CD0[];
extern u8 D_B02E6210[];
extern u8 D_B02E9B30[];
extern u8 D_B02ED760[];
extern u8 D_B02F14C0[];
extern u8 D_B02F4C20[];
extern u8 D_B02F8990[];
extern u8 D_B02FC650[];
extern u8 D_B0300480[];
extern u8 D_B03044C0[];
extern u8 D_B0308290[];

u8 *gStripBundleRomStart[10] = {
    D_B02FC650,
    D_B02F14C0,
    D_B02E2CD0,
    D_B02F4C20,
    D_B02E6210,
    D_B0300480,
    D_B02E9B30,
    D_B02ED760,
    D_B03044C0,
    D_B02F8990,
};

u8 *gStripBundleRomEnd[10] = {
    D_B0300480,
    D_B02F4C20,
    D_B02E6210,
    D_B02F8990,
    D_B02E9B30,
    D_B03044C0,
    D_B02ED760,
    D_B02F14C0,
    D_B0308290,
    D_B02FC650,
};
