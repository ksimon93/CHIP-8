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

void zero_functions() {
	opcode = instruction & 0x000F;
	if (opcode == 0) zero_function_table[0]();
	else zero_function_table[1]();
}

void (*function_table[17])() = {
	zero_functions, NOP, NOP, NOP, NOP, NOP, NOP, NOP, 
	NOP, NOP, NOP, NOP, NOP, 
	NOP, NOP, NOP, NOP
};

void (*zero_function_table[2])() = {
	op_00E0, op_00EE
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

void op_3XNN() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	unsigned char NN = (instruction & 0x00FF);
	if (V[X] == NN) pc += 2;
}

void op_4XNN() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	unsigned char NN = (instruction & 0x00FF);
	if (V[X] != NN) pc += 2;
}

void op_5XY0() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	unsigned char Y = (instruction & 0x00F0) >> 4;
	if (V[X] == V[Y]) pc += 2;
}

void op_6XNN() {
	unsigned char NN = (instruction & 0x00FF);
	unsigned char X = (instruction & 0x0F00) >> 8;
	V[X] = NN;
}

void op_7XNN() {
	unsigned char NN = (instruction & 0x00FF);
	unsigned char X = (instruction & 0x0F00) >> 8;
	V[X] += NN;
}
