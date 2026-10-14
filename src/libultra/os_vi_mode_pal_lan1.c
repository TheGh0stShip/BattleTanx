/* libultra 2.0I vimodes/vimodepallan1.c: reconstructed source from decompals/ultralib e24c836
 * (src/vimodes/vimodepallan1.c). Data-only object at 0x80146250. */
/**
 * @file vimodepallan1.c
 *
 * PAL LAN1 Video Mode
 *
 * L = Low Resolution
 * A = Anti-Aliased
 * N = Non-Interlaced
 * 1 = 16-bit Framebuffer
 */
#include "PR/os.h"
#include "PR/rcp.h"
#include "PRinternal/viint.h"

OSViMode osViModePalLan1 = {
    OS_VI_PAL_LAN1, // type
    {
        // comRegs
        VI_CTRL_TYPE_16 | VI_CTRL_GAMMA_DITHER_ON | VI_CTRL_GAMMA_ON | VI_CTRL_DIVOT_ON | VI_CTRL_ANTIALIAS_MODE_1 |
            VI_CTRL_PIXEL_ADV_3, // ctrl
        WIDTH(320),              // width
        BURST(58, 30, 4, 69),    // burst
        VSYNC(625),              // vSync
        HSYNC(3177, 23),         // hSync
        LEAP(3183, 3181),        // leap
        HSTART(128, 768),        // hStart
        SCALE(2, 0),             // xScale
        VCURRENT(0),             // vCurrent
    },
    { // fldRegs
      {
          // [0]
          ORIGIN(640),         // origin
          SCALE(1, 0),         // yScale
          HSTART(95, 569),     // vStart
          BURST(107, 2, 9, 0), // vBurst
          VINTR(2),            // vIntr
      },
      {
          // [1]
          ORIGIN(640),         // origin
          SCALE(1, 0),         // yScale
          HSTART(95, 569),     // vStart
          BURST(107, 2, 9, 0), // vBurst
          VINTR(2),            // vIntr
      } },
};
