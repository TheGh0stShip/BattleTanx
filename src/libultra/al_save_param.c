#include "types.h"

typedef struct {
    void *source;
    u8 pad04[0x10];
    void *dma;
} ALSave;

s32 alSaveParam(ALSave *filter, s32 paramID, void *param)
{
    switch (paramID) {
    case 1:
        filter->source = param;
        break;
    case 6:
        filter->dma = param;
        break;
    }
    return 0;
}
