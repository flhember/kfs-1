#include <../includes/gdt.h>
#include "../includes/print.h"
#include <../includes/keyboard.h>


void kernel_main(void) 
{
	init_gdt();

	terminal_initialize();

 	print_42();

	kprintf("Salut ouai ouai %s et la juste un % pour test et la un char %c pour voir un int %d en hex %x et en binaire %b ", "testvar", 'a', 42, 42, 42);
}