unsigned long long __ull_rshift(unsigned long long a0, unsigned long long a1)
{
    return a0 >> a1;
}

unsigned long long __ull_rem(unsigned long long a0, unsigned long long a1)
{
    return a0 % a1;
}

unsigned long long __ull_div(unsigned long long a0, unsigned long long a1)
{
    return a0 / a1;
}

long long __ll_lshift(long long a0, long long a1)
{
    return a0 << a1;
}

long long __ll_rem(long long a0, unsigned long long a1)
{
    return a0 % a1;
}

long long __ll_div(long long a0, long long a1)
{
    return a0 / a1;
}

long long __ll_mul(long long a0, long long a1)
{
    return a0 * a1;
}

void __ull_divremi(unsigned long long *quotient, unsigned long long *remainder,
                   unsigned long long dividend, unsigned short divisor)
{
    *quotient = dividend / divisor;
    *remainder = dividend % divisor;
}

long long __ll_mod(long long a0, long long a1)
{
    long long tmp = a0 % a1;

    if ((tmp < 0 && a1 > 0) || (tmp > 0 && a1 < 0))
        tmp += a1;
    return tmp;
}

long long __ll_rshift(long long a0, long long a1)
{
    return a0 >> a1;
}
