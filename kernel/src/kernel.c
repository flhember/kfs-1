#include <../includes/gdt.h>
#include <../includes/idt.h>
#include <../includes/print.h>

void kernel_main(void)
{
	/* INIT */
	init_gdt();
	idt_install();
	terminal_initialize();
	timer_install();
	keyboard_install();

	//SeT Interupt 
    __asm__ __volatile__ ("sti");

	while (1) ;

}