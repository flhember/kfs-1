.global gdt_flush       /* Allows the C code to link to this */

gdt_flush:
    mov 4(%esp), %eax   /* Get address of new GDT pass in parametre of gdt_flush */
    lgdt (%eax)         /* Load the GDT with our  pointer */
    mov $0x10, %ax      /* 0x10 is the offset in the GDT to our data segment and to all register */
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    jmp $0x08,$flush    /* 0x08 is the offset to our code segment: Far jump! */

flush:
    ret                 /* Returns back to the C code! */
