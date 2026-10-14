#include "ultra.h"

extern u32 D_80145DC0;
extern OSMesgQueue *D_80145DC8;

OSMesgQueue *osPiGetCmdQueue(void)
{
    if (D_80145DC0 == 0) {
        return 0;
    }
    return D_80145DC8;
}
