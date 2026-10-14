/*
 * GCC 2.7.2 libgcc2 signed double-word to single-float conversion helper,
 * adapted from the BattleTanx: Global Assault decompilation (GPL-2.0-or-later
 * with the GCC Runtime Library Exception).  BattleTanx reproduces it with the
 * repository's default KMC normalizer.
 */
typedef int SItype __attribute__((mode(SI)));
typedef unsigned int USItype __attribute__((mode(SI)));
typedef int DItype __attribute__((mode(DI)));
typedef unsigned int UDItype __attribute__((mode(DI)));
typedef float SFtype __attribute__((mode(SF)));
typedef float DFtype __attribute__((mode(DF)));

#define WORD_SIZE (sizeof(SItype) * 8)
#define HIGH_HALFWORD_COEFF (((UDItype)1) << (WORD_SIZE / 2))
#define HIGH_WORD_COEFF (((UDItype)1) << WORD_SIZE)
#define DI_SIZE (sizeof(DItype) * 8)
#define DF_SIZE 53
#define SF_SIZE 24

SFtype __floatdisf(DItype value) {
    DFtype result;
    SItype negate = 0;

    if (value < 0)
        value = -value, negate = 1;

    if (DF_SIZE < DI_SIZE && DF_SIZE > (DI_SIZE - DF_SIZE + SF_SIZE)) {
#define REP_BIT ((USItype)1 << (DI_SIZE - DF_SIZE))
        if ((UDItype)value >= ((UDItype)1 << DF_SIZE)) {
            if ((USItype)value & (REP_BIT - 1))
                value |= REP_BIT;
        }
    }
    result = (USItype)(value >> WORD_SIZE);
    result *= HIGH_HALFWORD_COEFF;
    result *= HIGH_HALFWORD_COEFF;
    result += (USItype)(value & (HIGH_WORD_COEFF - 1));

    return (SFtype)(negate ? -result : result);
}
