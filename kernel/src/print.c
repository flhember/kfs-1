#include "../includes/vga.h"
#include "../includes/print.h"
#include "../../libc/includes/libc.h"


/*
	Function to init terminal, color and fill buffer with ' ' char
*/
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

/*
	Function to set color of terminal
*/
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

/*
	Function to put good char with good color in terminal buffer
*/
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

/*
	Fucntion to print char 
*/
void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

/*
	Function too print string
*/
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

/*
	Function too print string
*/
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

/*
	Print 42 ascii art when start kernel
*/
void print_42(void)
{
	int			align = 27;

	terminal_column = 80 + align;    /* next line */
	terminal_writestring("        :::     :::::::: ");
	terminal_column = 160 + align;    /* next line */
	terminal_writestring("      :+:     :+:    :+: ");
	terminal_column = 240 + align;    /* next line */
	terminal_writestring("    +:+ +:+        +:+   ");
	terminal_column = 320 + align;    /* next line */
	terminal_writestring("  +#+  +:+      +#+      ");
	terminal_column = 400 + align;    /* next line */
	terminal_writestring("+#+#+#+#+#+  +#+         ");
	terminal_column = 480 + align;    /* next line */
	terminal_writestring("     #+#   #+#           ");
	terminal_column = 560 + align;    /* next line */
	terminal_writestring("   ###  ##########       ");
	terminal_column = 720;
}

/*
	Very simple itoa
*/
void	kitoa_base(int n, int base)
{
	char	*ascii = "0123456789abcdef";
	int		div = 1;

	while (div < div * base && div * base < n)
		div *= base;

	while (div > 0) {
		terminal_putchar(ascii[n / div]);
		n = n % div;
		div = div / base;
	}
}


/*
	Printf for kernel
*/
void 		kprintf(const char *str, ...)
{
	uint32_t	i = 0;
	va_list 	args;

	va_start(args, str);
	while(str[i]) {
		if (str[i] != '%')
			terminal_putchar(str[i]);
		if (str[i] == '%') {
			if (str[i + 1] == 's') {
				terminal_writestring(va_arg(args, char *));
				i++;
			}
			else if (str[i + 1] == 'c') {
				terminal_putchar(va_arg(args, int));
				i++;	
			}
			else if (str[i + 1] == 'd') {
				kitoa_base(va_arg(args, int), 10);
				i++;	
			}
			else if (str[i + 1] == 'x') {
				kitoa_base(va_arg(args, int), 16);
				i++;	
			}
			else if (str[i + 1] == 'b') {
				kitoa_base(va_arg(args, int), 2);
				i++;	
			}
			else
				terminal_putchar(str[i]);
		}
		i++;
	}
	va_end(args);
}