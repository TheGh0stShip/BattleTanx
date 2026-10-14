#include "types.h"

typedef struct AsyncOperation {
    u8 pad00[0xC];
    s32 complete;
} AsyncOperation;

void publish_async_completion(AsyncOperation *operation, s32 *result) __asm__("func_800DD9E8");

void publish_async_completion(AsyncOperation *operation, s32 *result)
{
    if (operation->complete != 0) {
        *result = 2;
    }
}
