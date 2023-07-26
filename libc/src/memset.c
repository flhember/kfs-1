
#include <libc.h>

void    *memset(void *s, int c, size_t n)
{
        size_t  i;
        char    *cpy;

        cpy = s;
        i = 0;
        while (i < n)
        {
                cpy[i] = (unsigned char)c;
                i++;
        }
        return (cpy);
}