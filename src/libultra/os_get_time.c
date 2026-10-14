#include "ultra.h"

extern OSTime D_803C7640;
extern u32 D_803C7648;

extern u32 __osDisableInt(void);
extern void __osRestoreInt(u32);
extern u32 osGetCount(void);

OSTime osGetTime(void)
{
    u32 count;
    u32 elapsed;
    OSTime accumulated;
    register u32 mask;

    mask = __osDisableInt();
    count = osGetCount();
    elapsed = count - D_803C7648;
    accumulated = D_803C7640;
    __osRestoreInt(mask);
    return accumulated + elapsed;
}
