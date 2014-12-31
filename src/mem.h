#define MEMORY_SIZE 4096

void init_mem();
unsigned short get_instruction(unsigned short);
unsigned char get_byte(unsigned short);

unsigned char mem[MEMORY_SIZE];