#ifndef BATTLETANX_GA_TYPES_H
#define BATTLETANX_GA_TYPES_H

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

typedef char static_assert_s8[sizeof(s8) == 1 ? 1 : -1];
typedef char static_assert_s16[sizeof(s16) == 2 ? 1 : -1];
typedef char static_assert_s32[sizeof(s32) == 4 ? 1 : -1];
typedef char static_assert_s64[sizeof(s64) == 8 ? 1 : -1];

#endif
