#include <../includes/gdt.h>
#include <../includes/idt.h>
#include <../includes/print.h>


void div0(void){
	int a;

	a = 0/0;
}

void kernel_main(void) 
{
	/* INIT */
	init_gdt();
	idt_install();
	terminal_initialize();

	/* PRINT INFO */
 	print_42();
	//div0();
	print_gdt();
}