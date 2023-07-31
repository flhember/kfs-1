#include <../includes/idt.h>
#include <../includes/print.h>

int timer_ticks = 0;

void timer_handler(struct regs *r)
{
    (void)r;
    timer_ticks++;

    // 18 clocks, approximately 1 second, we can display it
    if (timer_ticks % 18 == 0) {
        //kprintf("One second has passed\n");
    }
}

/*
    Sets up the system clock by init the timer in IRQ0
*/
void timer_install()
{
    irq_install_handler(0, timer_handler);
}