#include <../includes/gdt.h>

/* Set the ptr gdt to address of subject */
struct gdt_entry *gdt = (struct gdt_entry *)GDT_ADDRESS;

struct gdt_ptr gp;

/* Setup a descriptor in the Global Descriptor Table */
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

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