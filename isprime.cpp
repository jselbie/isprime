#include <math.h>

#define arraysize(s) (sizeof(s)/sizeof(*s))
#define is_divisible_by(x,y)  (!((x) % (y)))

long long sqrt_helper(long long val);

bool isPrime(long long n)
{
    long long seed[] = { 2, 3, 5, 7 };

    if (n <= 1)
    {
        return false;
    }

    for (size_t i = 0; i < arraysize(seed); i++)
    {
        if (seed[i] == n)
        {
            return true;
        }

        if (is_divisible_by(n, seed[i]))
        {
            return false;
        }
    }

    /* ============================================
        Using the table below as a reference, we can see that the pattern of divisibility by 3 or 5 repeats every 30 sequential values
        Any column with an "x" is already a value divisible by 3 or 5. So we can skip several sequences
        Net result is that only 26% of all sequential numbers get tested
        So instead of testing against every odd number, we can test against numbers that are not divisible by 2,3,or5
              003,005,007,009,011,013,015,017,019,021,023,025,027,029,031,033,035,037,039,041,043,045,047,049,051,53,55,57
     +                  0       4   6      10  12      16          22  24         *30
     3          x           x           x           x           x           x           x           x           x
     5              x                   x                   x                   x                   x
       ============================================
    */

    long long d = 7;  // ASSERT: d should be in the seed table above, but chances are high that d > sqrt(n)
    long long root = sqrt_helper(n);
    const long long stop = root + 1; // +1 to deal with rounding errors from computing the floored square root
    while (d <= stop)
    {
        bool result = (is_divisible_by(n, d) || is_divisible_by(n, d + 4) || is_divisible_by(n, d + 6) || is_divisible_by(n, d + 10) || is_divisible_by(n, d + 12) || is_divisible_by(n, d + 16) || is_divisible_by(n, d + 22) || is_divisible_by(n, d + 24));
        if (result)
        {
            return false;
        }
        d += 30;
    }

    return true;
}



long long sqrt_helper(long long val)
{
    const long long SQRT_CAP = 1LL << 53;
    const unsigned long long TWO_POW_32 = 1ULL << 32;

    if (val < 0) // if type is unsigned this will be ignored = no runtime  
    {
        return 0; // negative number ERROR  
    }

    // We really want to use sqrt whenever possible. It gets performed in hardware on most platforms and is much, much faster than the loop below.
    // But... anything bigger than 2**53 will have some issues inside a double. http://stackoverflow.com/questions/1848700/biggest-integer-that-can-be-stored-in-a-double
    // So we can only use sqrt reliably when val is less than or equal 2**53

    if (val <= SQRT_CAP)
    {
        double d = sqrt((double)val);
        return (long long)d;
    }

    // return an approximate square root that is greather than or equal to the actual square root
    // any 64 bit number, N,  can be expressed in terms of x and y as

    // Therefore sqrt(N) = sqrt(x) * sqrt(2^32) + , where z is some value to account for the "y" portion of the equation
    // but we know that (x+1)<< 32 is always greater than (x<<32)|y, thus we can live with just getting sqrt(x+1) and multiplying the result by 2^16
    // that will return a slightly greater sqrt, but for computing the stop point below, it will suffice
    unsigned long long uval = (unsigned long long)val;
    size_t shift = 0;

    while (uval >= TWO_POW_32)
    {
        uval = uval >> 32;
        shift += 32;
    }

    double d2 = sqrt((double)(uval + 1));
    long long result = (long long)ceil(d2);
    result = result << (shift / 2);
    return result;
}

