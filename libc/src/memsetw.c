#include <libc.h>

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *cpy;

    cpy = (unsigned short *)dest;
    while (count != 0)
    {
        *cpy++ = val;
        count--;
    }
    return (cpy);
}