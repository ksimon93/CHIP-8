#include "cpu.h"
#include "fontset.h"

					/* CPU MANAGEMENT FUNCTIONS */
/* =============================================================*/

void initialize() {
	// clear hardware
	pc 				= PC_START_ADDRESS;
	opcode 			= 0;
	instruction 	= 0;
	I 				= 0;
	sp				= 0;
    delay_timer     = 0;
    sound_timer     = 0;

	// initialize memory
	for (int i = 0; i < FONTSET_SIZE; i++) {
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
