#include "cpu.h"
#include "fontset.h"

				/* HARDWARE, REGISTERS, etc. */
/* =============================================================*/

unsigned short opcode;
unsigned short instruction;
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
	pc 				= 0x200;
	opcode 			= 0;
	instruction 	= 0;
	I 				= 0;
	sp				= 0;

	// initialize memory
	for (int i = 0; i < 80; i++) {
		memory[i] = fontset[i];
	}	
} 

void fetch() {
	instruction = ((memory[pc]) << 8) + (memory[pc+1]);
	opcode = instruction & 0xF000;
	pc += 2;
}

void execute() {
	function_table[opcode >> 12]();
}

void fdx_cycle() {
	fetch();
	execute();
}

void arithmetic() {
	opcode = instruction & 0x000F;
	arithmetic_table[opcode]();
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

// 0x2NNN
void call_subroutine() {
	stack[sp] = pc;
	sp++;
	pc = instruction & 0x0FFF;
}
