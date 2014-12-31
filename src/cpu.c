#include "cpu.h"
#include "mem.h"
#include "gfx.h"

					/* CPU MANAGEMENT FUNCTIONS */
/* =============================================================*/

void init_cpu() {
	// clear hardware
	pc 				= PC_START_ADDRESS;
	opcode 			= 0;
	instruction 	= 0;
	I 				= 0;
	sp				= 0;
    delay_timer     = 0;
    sound_timer     = 0;	
} 

void fetch() {
	instruction = get_instruction(pc);
	opcode = (instruction & 0xF000) >> 12;
	pc += 2;
}

void execute() {
	function_table[opcode]();
}

void cpu_cycle() {
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

void op_00E0() { init_gfx(); }

void op_00EE() {
    sp--;
    pc = stack[sp];
}

void op_1NNN() {
    pc = instruction & 0x0FFF;
}

void op_2NNN() {
	stack[sp] = pc;
	sp++;
	pc = instruction & 0x0FFF;
}
