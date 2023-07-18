#ifndef GDT_H
#define GDT_H

#include <stdint.h> 

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

/* Our GTD with 3 entry and ptr to gdt */
struct gdt_entry gdt[3];
struct gdt_ptr gp;

/* flush.s */
extern void gdt_flush();

/* gdt.c */
void     init_gdt(void);

#endif