#ifndef MEM_H
#define MEM_H

#define MEMORY_SIZE 4096

void init_mem();
unsigned short get_instruction(unsigned short);
unsigned char get_byte(unsigned short);
void set_mem(unsigned short addr, unsigned char val);

unsigned char mem[MEMORY_SIZE];

#endif
