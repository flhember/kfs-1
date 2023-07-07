#include "includes/kernel.h"

unsigned int    vga_index;
unsigned short  *terminal_buffer;

void 			clear_screen(void)
{
    int 		index = 0;

    /* there are 25 lines each of 80 columns;
       each element takes 2 bytes */
    while (index < 80 * 25 * 2) {
            terminal_buffer[index] = ' ';
            index += 2;
    }
}

void 			print_string(char *str, unsigned char color)
{
    int 		index = 0;

    while (str[index]) {
            terminal_buffer[vga_index] = (unsigned short)str[index]
				|(unsigned short)color << 8;
            index++;
            vga_index++;
    }
}

void 			print_42(void)
{
	int			align = 27;
	int			line = 80;

    vga_index = align;
	print_string("        :::     :::::::: ",YELLOW);
	vga_index = 80 + align;    /* next line */
	print_string("      :+:     :+:    :+: ",YELLOW);
	vga_index = 160 + align;    /* next line */
	print_string("    +:+ +:+        +:+   ",YELLOW);
	vga_index = 240 + align;    /* next line */
	print_string("  +#+  +:+      +#+      ",YELLOW);
	vga_index = 320 + align;    /* next line */
	print_string("+#+#+#+#+#+  +#+         ",YELLOW);
	vga_index = 400 + align;    /* next line */
	print_string("     #+#   #+#           ",YELLOW);
	vga_index = 480 + align;    /* next line */
	print_string("   ###  ##########      ",YELLOW);
    vga_index = 560 + align;    /* next line */
}

void 			main(void)
{
    terminal_buffer = (unsigned short *)VGA_ADDRESS;
    vga_index = 0;

    clear_screen();
	print_42();

    return;
}
                         