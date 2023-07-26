#include <../includes/idt.h>
#include <../includes/print.h>
#include "../../libc/includes/libc.h"

/*
    All error message for each interrupt
*/
const char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

/* Function to setup one entry in the IDT */
void idt_set_gate(int num, unsigned long base, unsigned short sel, unsigned char flags)
{
    idt[num].base_lo = (base & 0xFFFF);         //low 16 bits
    idt[num].sel = sel;                         //index of kernel code segment (gdt)
    idt[num].always0 = 0;                       //alawys 0
    idt[num].flags = flags;                     //flag with priority and if is present or not
    idt[num].base_hi = (base >> 16) & 0xFFFF;   //hight 16 bits
}

/* Installs the IDT */
void idt_install()
{
    /* Setup the IDT pointer and limit */
    idtp.limit = (sizeof (struct idt_entry) * 256);
    idtp.base = (uint32_t)&idt;

    /* Clear out the entire IDT, initializing it to zeros */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    /* Each isr for idt */
    idt_set_gate(0,  (unsigned)_isr0,  IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(1,  (unsigned)_isr1,  IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(2,  (unsigned)_isr2,  IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(3,  (unsigned)_isr3,  IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(4,  (unsigned)_isr4,  IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(5,  (unsigned)_isr5,  IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(6,  (unsigned)_isr6,  IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(7,  (unsigned)_isr7,  IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(8,  (unsigned)_isr8,  IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(9,  (unsigned)_isr9,  IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(10, (unsigned)_isr10, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(11, (unsigned)_isr11, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(12, (unsigned)_isr12, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(13, (unsigned)_isr13, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(14, (unsigned)_isr14, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(15, (unsigned)_isr15, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(16, (unsigned)_isr16, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(17, (unsigned)_isr17, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(18, (unsigned)_isr18, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(19, (unsigned)_isr19, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(20, (unsigned)_isr20, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(21, (unsigned)_isr21, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(22, (unsigned)_isr22, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(23, (unsigned)_isr23, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(24, (unsigned)_isr24, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(25, (unsigned)_isr25, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(26, (unsigned)_isr26, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(27, (unsigned)_isr27, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(28, (unsigned)_isr28, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(29, (unsigned)_isr29, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(30, (unsigned)_isr30, IDX_KERNEL_CODE, FLAG_ISR);
    idt_set_gate(31, (unsigned)_isr31, IDX_KERNEL_CODE, FLAG_ISR);

    /* Points the processor's internal register to the new IDT */
    idt_load(&idtp);
}

void fault_handler(struct regs *r)
{
    if (r->int_no < 32)
    {
        kprintf("%s", exception_messages[r->int_no]);
        kprintf(" Exception. System Halted!\n");
        for (;;);
    }
}