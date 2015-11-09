
#include "bmlib.h"

#ifdef BMLIB_HAS_DIV10

/* divide by ten 10, from Hacker's Delight chapter 10 */
uint32_t divu10(uint32_t n)
{
    uint32_t q, r;
    q = (n >> 1) + (n >> 2);
    q = q + (q >> 4);
    q = q + (q >> 8);
    q = q + (q >> 16);
    q = q >> 3;
    r = n - q*10;
    return q + ((r + 6) >> 4);
}

#endif /* BMLIB_HAS_DIV10 */
