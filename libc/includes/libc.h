#ifndef LIBC_H
#define LIBC_H
 
#include <stddef.h>

size_t          strlen(const char*);
int             strcmp(const char *s1, const char *s2);
void            *memset(void *s, int c, size_t n);
void            *memcpy(void *dest, const void *src, size_t n);
unsigned short  *memsetw(unsigned short *dest, unsigned short val, size_t count);

#endif