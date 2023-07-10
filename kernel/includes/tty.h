#ifndef TTY_H
#define TTY_H
 
#include <stddef.h>     //size_t
#include <stdint.h>     //unsigned int 8/16 
 
void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void print_42(void);

#endif