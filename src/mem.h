#ifndef MEM_H
#define MEM_H

#define MEMORY_SIZE 4096

void init_mem();
unsigned char get_byte(unsigned short loc);
unsigned short get_instruction(unsigned short pc);
void set_mem(unsigned short addr, unsigned char val);
unsigned static char mem[MEMORY_SIZE];

#endif
