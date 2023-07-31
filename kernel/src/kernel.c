#include <../includes/gdt.h>
#include <../includes/idt.h>
#include <../includes/print.h>

void div0(){
	int a = 0/0;
}

void kernel_main(void)
{
	/* INIT */
	init_gdt();
	idt_install();
	terminal_initialize();

	/* PRINT INFO */
 	print_42();
	timer_install();
	keyboard_install();

	div0();
	// sti = SeT Interupt 
    __asm__ __volatile__ ("sti");
	while (1) ;
}