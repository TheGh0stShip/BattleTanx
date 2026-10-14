#include "types.h"
extern s16 get_proximity_radius_limit(void) __asm__("func_80086AE8");
extern s32 gProximityRadius __asm__("D_80125858");
extern s32 gProximityRadiusSq __asm__("D_801C9174");
void grow_proximity_radius(void) __asm__("func_800862E8");
void grow_proximity_radius(void) {
    if (gProximityRadius < get_proximity_radius_limit()) {
        gProximityRadius += 50;
        gProximityRadiusSq = gProximityRadius * gProximityRadius;
    }
}
