#include "types.h"

typedef struct FacingProbe {
    f32 forwardZ;
    f32 forwardX;
    f32 sideX;
    f32 sideZ;
    f32 offsetX;
    f32 offsetZ;
    u8 disabled;
} FacingProbe;

s32 classify_point_relative_to_facing(f32 x, f32 z, FacingProbe *probe)
    __asm__("func_8009412C");

s32 classify_point_relative_to_facing(f32 x, f32 z, FacingProbe *probe)
{
    f32 adjustedZ;
    f32 adjustedX;
    f32 forwardDistance;
    f32 sideDistance;
    s32 result;

    if (probe->disabled != 0) {
        return 0;
    }
    adjustedZ = z + probe->offsetZ;
    adjustedX = x + probe->offsetX;
    forwardDistance = probe->forwardZ * adjustedZ + probe->forwardX * adjustedX;
    sideDistance = probe->sideX * adjustedX - probe->sideZ * adjustedZ;
    if (forwardDistance > 0.0f) {
        if (sideDistance > 0.0f ? sideDistance < forwardDistance
                                : -sideDistance < forwardDistance) {
            return 0;
        }
    }
    result = 2;
    if (sideDistance > 0.0f) {
        result = 1;
    }
    return result;
}
