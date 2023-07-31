#include <../includes/idt.h>
#include <../includes/print.h>

/*  Array of function pointers */
void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

/* install new irq function in table */
void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = handler;
}

/*
    Remappe irq 8 to 15 (normally) to 32 to 47 to follows the idt 
    We need 2 PIC (programmables interruption controle).
    One for 0 to 7 and One to 8 to 15
*/
void irq_remap(void)
{
    //0x11 to prepare to configure the two PIC
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);

    // 0x20 - 0x28, set the adress to 32 at 40 (follow the idt)
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);

    //Configure the first pic to master and the seconde to slave
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);

    //0x01 to set the Master/slave mode
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);

    //Done configure
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

/* 
    Start by remap PIC and set the irq function to idt.
*/
void irq_install()
{
    irq_remap();

    idt_set_gate(32, (unsigned)_irq0,  IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(33, (unsigned)_irq1,  IDX_KERNEL_CODE, FLAG_ISR);
}

void irq_handler(struct regs *r)
{
    void (*handler)(struct regs *r);

    handler = irq_routines[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }

    // Tell to PIC, interupt is done go next ->
    outportb(0x20, 0x20);
}