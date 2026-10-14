#include "types.h"

typedef struct InterpolatedRenderRecord {
    s16 x;
    s16 y;
    s16 z;
    u8 pad06[6];
    u8 red;
    u8 green;
    u8 blue;
    u8 pad0F;
} InterpolatedRenderRecord;

void interpolate_render_records(s32 fraction, s32 count, void *from, void *to, void *out)
    __asm__("func_8009196C");

void interpolate_render_records(s32 fraction, s32 count, void *from, void *to, void *out)
{
    s16 fromComponent;
    s16 fromComponent2;
    s16 fromComponent3;
    s32 difference;
    s32 i;
    u8 fromChannel;
    u8 fromChannel2;
    u8 fromChannel3;
    u8 stackPadding[8];
    void *fromBytes;
    void *toBytes;
    void *outBytes;

    fromBytes = from;
    toBytes = to;
    i = 0;
    if (count <= 0) {
        goto done;
    }
    outBytes = out;
loop:
        fromComponent = *(s16 *)((s8 *)fromBytes + 0);
        *(s16 *)((s8 *)outBytes + 0) =
            fromComponent + ((*(s16 *)((s8 *)toBytes + 0) - fromComponent) * fraction >> 8);
        fromComponent2 = *(s16 *)((s8 *)fromBytes + 2);
        *(s16 *)((s8 *)outBytes + 2) =
            fromComponent2 + ((*(s16 *)((s8 *)toBytes + 2) - fromComponent2) * fraction >> 8);
        fromComponent3 = *(s16 *)((s8 *)fromBytes + 4);
        *(s16 *)((s8 *)outBytes + 4) =
            fromComponent3 + ((*(s16 *)((s8 *)toBytes + 4) - fromComponent3) * fraction >> 8);
        difference = (*(u8 *)((s8 *)toBytes + 0xC) -
                      (fromChannel = *(u8 *)((s8 *)fromBytes + 0xC))) * fraction;
        *(s8 *)((s8 *)outBytes + 0xC) =
            fromChannel + (difference >> 8);
        difference = (*(u8 *)((s8 *)toBytes + 0xD) -
                      (fromChannel2 = *(u8 *)((s8 *)fromBytes + 0xD))) * fraction;
        *(s8 *)((s8 *)outBytes + 0xD) =
            fromChannel2 + (difference >> 8);
        difference = (*(u8 *)((s8 *)toBytes + 0xE) -
                      (fromChannel3 = *(u8 *)((s8 *)fromBytes + 0xE))) * fraction;
        i++;
        fromBytes += 0x10;
        toBytes += 0x10;
        *(s8 *)((s8 *)outBytes + 0xE) = fromChannel3 + (difference >> 8);
        outBytes += 0x10;
    if (i < count) {
        goto loop;
    }
done:
    return;
}
