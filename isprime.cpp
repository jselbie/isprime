
#define arraysize(s) (sizeof(s)/sizeof(*s))
#define is_divisible_by(x,y)  (!((x) % (y)))



// this function lifted from: http://www.codecodex.com/wiki/Calculate_an_integer_square_root
long long intSqrt(long long remainder)
{
    if (remainder < 0) // if type is unsigned this will be ignored = no runtime  
    {
        return 0; // negative number ERROR  
    }

    long long place = (long long)1 << (sizeof(remainder) * 8 - 2); // calculated by precompiler = same runtime as: place = 0x40000000  

    if (remainder >= place)
    {
        return 0; // would cause overflow, code below will handle
    }

    while (place > remainder)
        place /= 4; // optimized by complier as place >>= 2  

    long long root = 0;
    while (place)
    {
        if (remainder >= root + place)
        {
            remainder -= root + place;
            root += place * 2;
        }
        root /= 2;
        place /= 4;
    }

    return root;
}

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

 /*
    Using the table below as a reference, we can see that the pattern of divisibility by 3 or 5 repeats every 30 sequential values
    Any column with an "x" is already a value divisible by 3 or 5. So we can skip several sequences
    Net result is that only 26% of all sequential numbers get tested
    So instead of testing against every odd number, we can test against numbers that are not divisible by 2,3,or5
          003,005,007,009,011,013,015,017,019,021,023,025,027,029,031,033,035,037,039,041,043,045,047,049,051,53,55,57
 +                  0       4   6      10  12      16          22  24         *30
 3          x           x           x           x           x           x           x           x           x
 5              x                   x                   x                   x                   x
*/



    long long d = 7;  // ASSERT: d should be in the seed table above, but chances are high that d > sqrt(n) 
    long long root = intSqrt(n);
    if (root == 0)
    {
        root = (intSqrt(n / 2) * 142) / 100;   // 142/100 == sqrt(2)
    }
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
