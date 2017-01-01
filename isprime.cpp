#include <math.h>

#define arraysize(s) (sizeof(s)/sizeof(*s))
#define is_divisible_by(x,y)  (!((x) % (y)))

bool isPrime(long long n)
{
    long long seed[] = { 2,3,5 };

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

    /*
    Using the table below as a reference, we can see that the pattern of divisibility by 3 or 5 repeats every 30 values
    Any column with an "x" is already a value divisible by 3 or 5. So we can skip several sequences
    So instead of testing against every odd number, we can test against numbers that are not divisible by 2,3,or5
    003,005,007,009,011,013,015,017,019,021,023,025,027,029,031,033,035,037,039,041,043,045,047,049,051
    0             2   4   6   8  10  12  14  16  18  20  22  24         *30
    3     x           x           x           x           x           x           x           x           x
    5         x                   x                   x                   x                   x
    */


    long long d = 7;  // ASSERT: d must be in the seed table above
    long long stop = sqrt(n) + 1;  // +1 to account for all rounding errors especially in the really large numbers where sqrt can't be precise
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
