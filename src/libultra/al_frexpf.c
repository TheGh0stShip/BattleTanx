#include "types.h"

f64 _frexpf(f64 value, s32 *exponent)
{
    f64 absolute;

    *exponent = 0;
    if (value == 0.0) {
        return value;
    }
    absolute = value > 0.0 ? value : -value;
    while (absolute >= 1.0) {
        absolute *= 0.5;
        ++*exponent;
    }
    while (absolute < 0.5) {
        absolute += absolute;
        --*exponent;
    }
    return value > 0.0 ? absolute : -absolute;
}
