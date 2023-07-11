#ifndef TTY_H
#define TTY_H
 
#include <stddef.h>     //size_t
#include <stdint.h>     //unsigned int 8/16 

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void print_42(void);

#endif