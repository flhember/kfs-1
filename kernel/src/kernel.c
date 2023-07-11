#include <../includes/tty.h>
#include <../includes/keyboard.h>

void kernel_main(void) 
{
	terminal_initialize();
 	print_42();

	while (1) {
		keyboard_handler();
	}
	// set loop for keyboard
}