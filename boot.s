/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

/* Declare a multiboot header */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Set size for stack */
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

/*Set entry point to the kernel at _start */
.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp    /* set stack pointer */
	call kernel_main        /* Call main ft */
	cli                     /* block interrupts */
1:	hlt                     /* halt the cpu */
	jmp 1b                  /* jump to halt the cpu */

.size _start, . - _start
