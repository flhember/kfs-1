#include <stdint.h>     // For uint32 type

/*
        Flag to isr:
    P 	DPL 	Always 01110
    1   00      01110           = 0x8E
    P - Segment is present? (1 = Yes)
    DPL - Which Ring (0 to 3)
*/
#define FLAG_ISR    0x8E

/*
        Index in gdt to kernel code execute:
        8 -> index just after the null segment.
*/
#define IDX_KERNEL_CODE    0x08

/*
    Defines an IDT entry
*/
struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;        /* Our kernel segment goes here! */
    unsigned char always0;     /* This will ALWAYS be set to 0! */
    unsigned char flags;       /* Set using the above table! */
    unsigned short base_hi;
} __attribute__((packed));      // Don't add padding with gcc

/* 
    Main struct contain the ptr of idt and the size (limit)
*/
struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));      // Don't add padding with gcc

/* Declare an IDT of 256 entries.*/
struct idt_entry idt[256];
struct idt_ptr idtp;

/*
    Struct to get all push asm to c function,
    like this we can have the two info push by the isr function.
    int_no = num of isr
    err_code = error code
*/
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

/*
    All asm function for isr
*/
extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();

/* All asm function to irq */
extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15();

/*
    idt
*/
void idt_install();
extern void idt_load();
void idt_set_gate(int num, unsigned long base, unsigned short sel, unsigned char flags);

/*
    irq 
*/
void irq_install();
void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_handler(struct regs *r);
void timer_install();
void keyboard_install();