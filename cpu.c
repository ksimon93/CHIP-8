#include "cpu.h"
#include "fontset.h"

				/* HARDWARE, REGISTERS, etc. */
/* =============================================================*/

unsigned short opcode;
unsigned char memory[4096];

// general purpose registers
unsigned char V[16];

// index register
unsigned short I;

// program counter
unsigned short pc;

unsigned char gfx[2048];

// timers
unsigned char delay_timer;
unsigned char sound_timer;

unsigned short stack[16];
unsigned short sp;

// keys pressed
unsigned char key[16];

// function pointers for opcode tables
void (*function_table[17])();
void (*arithmetic_table[16])();


					/* CPU MANAGEMENT FUNCTIONS */
/* =============================================================*/

void initialize() {
	// clear hardware
	pc 		= 0x200;
	opcode 	= 0;
	I 		= 0;
	sp		= 0;

	// initialize memory
	for (int i = 0; i < 80; i++) {
		memory[i] = fontset[i];
	}	
} 

void fetch() {
	opcode = ((memory[pc]) << 8) + (memory[pc+1]);
	pc += 2;
}

void execute() {
	function_table[ (opcode & 0xF000) >> 12 ]();
}

void fdx_cycle() {
	fetch();
	execute();
}

void arithmetic() {
	arithmetic_table[ (opcode & 0x000F) ]();
}

void (*function_table[17])() = {
	NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, 
	arithmetic, NOP, NOP, NOP, NOP, 
	NOP, NOP, NOP, NOP
};

void (*arithmetic_table[16])() = {
	NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, 
	NOP, NOP, NOP, NOP, 
	NOP, NOP, NOP, NOP
};

							/* OPCODES */
/* =============================================================*/
void NOP() {}