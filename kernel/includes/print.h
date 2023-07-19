#ifndef PRINT_H
#define PRINT_H
 
#include <stddef.h>     //size_t
#include <stdint.h>     //unsigned int 8/16 
#include <stdarg.h>     //to va_arg printf
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void print_42(void);
void kprintf(const char *str, ...);
void kdump(uint8_t *addr, uint32_t limit);

#endif