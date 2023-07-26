#include <../includes/gdt.h>
#include <../includes/print.h>

/* Set the ptr gdt to address of subject */
struct gdt_entry *gdt = (struct gdt_entry *)GDT_ADDRESS;

struct gdt_ptr gp;

/* Function to setup one segment in the GDT */
void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

/*
    Function to init gdt create with good base (addr) and limit (size)
    Create all segment we need and load it.
*/
void init_gdt(void)
{
    /* Setup the GDT pointer and limit */
    gp.limit = (sizeof(struct gdt_entry) * NB_SEG) - 1 ;
    gp.base = (uint32_t)gdt;

    /* NULL descriptor */
    gdt_set_gate(0, 0, 0, 0, 0);

    /* Kern seg */
    gdt_set_gate(1, 0, 0xFFFF, (uint8_t)KERN_PERM_CODE, GRAN);
    gdt_set_gate(2, 0, 0xFFFF, (uint8_t)KERN_PERM_DATA, GRAN);
    gdt_set_gate(3, 0, 0xFFFF, (uint8_t)KERN_PERM_STACK, GRAN);

    /* User sef */
    gdt_set_gate(4, 0, 0xFFFF, (uint8_t)USER_PERM_CODE, GRAN);
    gdt_set_gate(5, 0, 0xFFFF, (uint8_t)USER_PERM_DATA, GRAN);
    gdt_set_gate(6, 0, 0xFFFF, (uint8_t)USER_PERM_STACK, GRAN);

    /* Flush out the old GDT and install the new changes with addresse of new */
    gdt_flush(&gp);
}

/*
    Function to print all gtd info and dump the stack for see the gdt part
*/
void print_gdt() {
    int i = 1;
    char *tab[NB_SEG];

    tab[0] = "NULL";
    tab[1] = "KERN_CODE";
    tab[2] = "KERN_DATA";
    tab[3] = "KERN_STCK";
    tab[4] = "USER_CODE";
    tab[5] = "USER_DATA";
    tab[6] = "USER_STCK";

    kprintf("---- GDT INFO ----\n");
    kprintf("GDT Base: 0x%8x\n", gp.base);
    kprintf("GDT Limite: %x\n", gp.limit);
    kprintf("\n            BLOW BMID BHGH LMTLOW GRAN ACC\n");
    while (i < NB_SEG) {
        kprintf("%s   ", tab[i]);
        kprintf("%x    ", gdt[i].base_low);
        kprintf("%x    ", gdt[i].base_middle);
        kprintf("%x    ", gdt[i].base_high);
        kprintf("%x   ", gdt[i].limit_low);
        kprintf("%x   ", gdt[i].granularity);
        kprintf("%x\n", gdt[i].access);
        i++;
    }

    kprintf("\n---- Dump Stack ----\n");
    kdump((uint8_t *)gp.base, gp.limit + 9);
}