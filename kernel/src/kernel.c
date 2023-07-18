#include <../includes/tty.h>
#include <../includes/keyboard.h>
#include <../includes/gdt.h>


void kernel_main(void) 
{
	init_gdt();

	terminal_initialize();

 	print_42();

}