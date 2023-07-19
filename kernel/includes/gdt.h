#ifndef GDT_H
#define GDT_H

#include <stdint.h>     // For uint32 type

/* Address to start gdt asking in subject */
#define GDT_ADDRESS  0x00000800

/* Nb of segment for size total */
#define NB_SEG 7
/* Seg perm to set */
#define SEG_DESCTYPE(x)  ((x) << 0x04)              // Descriptor type (0 for system, 1 for code/data)
#define SEG_PRES(x)      ((x) << 0x07)              // Present
#define SEG_SAVL(x)      ((x) << 0x0C)              // Available for system use
#define SEG_LONG(x)      ((x) << 0x0D)              // Long mode
#define SEG_SIZE(x)      ((x) << 0x0E)              // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN(x)      ((x) << 0x0F)              // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_PRIV(x)      (((x) &  0x03) << 0x05)    // Set privilege level (0 - 3)

/* Type for seg */
#define SEG_DATA_RD        0x00 // Read-Only
#define SEG_DATA_RDA       0x01 // Read-Only, accessed
#define SEG_DATA_RDWR      0x02 // Read/Write
#define SEG_DATA_RDWRA     0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX        0x08 // Execute-Only
#define SEG_CODE_EXA       0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD      0x0A // Execute/Read
#define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed
#define SEG_CODE_EXC       0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed
 
/*

    All seg have default perm just kern have better privilege level (0)

    Code type need to execute and read
    Date type need to read and write
    Stack type need to read / write and expand down

*/

#define KERN_PERM_CODE  SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                        SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                        SEG_PRIV(0)     | SEG_CODE_EXRD

#define KERN_PERM_DATA  SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                        SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                        SEG_PRIV(0)     | SEG_DATA_RDWR

#define KERN_PERM_STACK SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                        SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                        SEG_PRIV(0)     | SEG_DATA_RDWREXPD

#define USER_PERM_CODE  SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                        SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                        SEG_PRIV(3)     | SEG_CODE_EXRD

#define USER_PERM_DATA  SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                        SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                        SEG_PRIV(3)     | SEG_DATA_RDWR

#define USER_PERM_STACK SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                        SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                        SEG_PRIV(3)     | SEG_DATA_RDWREXPD

/*
0xCF = 11001111 
G OS 0 S     
1 1  0 0  1111

G  = Granuality         0 = 1byte 1 = 4kbyte
OS = Operend Size       0 = 16bit 1 = 32bit
0  = always 0 
S  = Available for System (Always set to 0) 

Not use 4 last byte
*/

#define GRAN 0xCF

/* Defines a GDT segment. */
struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));      // Don't add padding with gcc

/* Special pointer which includes the limit: The max bytes
*  taken up by the GDT, minus 1. Again, this NEEDS to be packed */
struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));      // Don't add padding with gcc


/* flush.s */
extern void gdt_flush();

/* gdt.c */
void        init_gdt(void);
void        print_gdt();

#endif