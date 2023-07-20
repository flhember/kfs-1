#include <../includes/gdt.h>
#include "../includes/print.h"

void kernel_main(void) 
{
	/* INIT */
	init_gdt();
	terminal_initialize();

	/* PRINT INFO */
 	print_42();
	print_gdt();
}