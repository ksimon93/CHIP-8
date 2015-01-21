#include "cpu.h"
#include "mem.h"
#include "gfx.h"
#include "input.h"
#include <stdlib.h>

		/* CPU MANAGEMENT FUNCTIONS */
/*=============================================================*/

void init_cpu() {
	// clear hardware
	pc			= PC_START_ADDRESS;
	opcode			= 0;
	instruction		= 0;
	I			= 0;
	sp			= 0;
	delay_timer		= 0;
	sound_timer		= 0;
	seed 			= 0;	
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
	seed++;
}

void zero_functions() {
	opcode = instruction & 0x000F;
	if (opcode == 0) 
		op_00E0();
	else 
		op_00EE();
}

void eight_functions() {
	opcode = instruction & 0x000F;
	eight_function_table[opcode];
}

void (*function_table[17])() = {
	zero_functions, op_1NNN, op_2NNN, op_3XNN, op_4XNN, op_5XY0, op_6XNN, 
	op_7XNN, eight_functions, op_9XY0, op_ANNN, op_BNNN, op_CXNN, op_DXYN, 	
};

void (*eight_function_table[15])() = {
	op_8XY0, op_8XY1, op_8XY2, op_8XY3, op_8XY4, op_8XY5, op_8XY6, op_8XY7,
	NOP, NOP, NOP, NOP, NOP, NOP, op_8XYE
};

			/* OPCODES */
/*=============================================================*/
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
	if (V[X] == NN) 
		pc += 2;
}

void op_4XNN() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	unsigned char NN = (instruction & 0x00FF);
	if (V[X] != NN) 
		pc += 2;
}

void op_5XY0() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	unsigned char Y = (instruction & 0x00F0) >> 4;
	if (V[X] == V[Y]) 
		pc += 2;
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

void op_8XY0() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	unsigned char Y = (instruction & 0x00F0) >> 4;
	V[X] = V[Y];
}

void op_8XY1() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	unsigned char Y = (instruction & 0x00F0) >> 4;
	V[X] = V[X] | V[Y];
}

void op_8XY2() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	unsigned char Y = (instruction & 0x00F0) >> 4;
	V[X] = V[X] & V[Y];
}

void op_8XY3() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	unsigned char Y = (instruction & 0x00F0) >> 4;
	V[X] = V[X] ^ V[Y];
}

void op_8XY4() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	unsigned char Y = (instruction & 0x00F0) >> 4;
	if (V[Y] > 0xFF - V[X]) 
		V[0xF] = 1; // 1 if is a carry
	else
		V[0xF] = 0;
	V[X] += V[Y];
}

void op_8XY5() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	unsigned char Y = (instruction & 0x00F0) >> 4;
	if (V[Y] > V[X])
		V[0xF] = 0; // 0 if is a borrow
	else
		V[0xF] = 1;
	V[X] -= V[Y];
}

void op_8XY6() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	V[0xF] = V[X] & 0x1;
	V[X] = V[X] >> 1;
}

void op_8XY7() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	unsigned char Y = (instruction & 0x00F0) >> 4;
	if (V[X] > V[Y])
		V[0xF] = 0; // 0 if is a borrow
	else
		V[0xF] = 1;
	V[X] = V[Y] - V[X];
}

void op_8XYE() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	V[0xF] = V[X] & 0x80;
	V[X] = V[X] << 1;
}

void op_9XY0() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	unsigned char Y = (instruction & 0x00F0) >> 4;
	if (V[X] != V[Y])
		pc += 2;
}

void op_ANNN() {
	I = instruction & 0x0FFF;
}

void op_BNNN() {
	pc = (instruction & 0x0FFF) + V[0];
}

void op_CXNN() {
	srand(seed);
	unsigned char X = (instruction & 0x0F00) >> 8;
	V[X] = rand() + (instruction & 0x00FF);
}

void op_DXYN() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	unsigned char Y = (instruction & 0x00F0) >> 4;
	unsigned char height = instruction & 0x000F;

}

void op_EX9E() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	if (is_key_pressed(V[X]))
		pc += 2;
}

void op_EXA1() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	if (!is_key_pressed(V[X]))
		pc += 2;
}

void op_FX07() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	V[X] = delay_timer;
}

void op_FX0A() {

}

void op_FX15() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	delay_timer = V[X];
}

void op_FX18() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	sound_timer = V[X];
}

void op_FX1E() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	I += V[X];
}

void op_FX29() {

}

void op_FX33() {

}

void op_FX55() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	for (int i = 0; i <= X; i++) {
		set_mem(I + i, V[i]);
	}
}

void op_FX65() {
	unsigned char X = (instruction & 0x0F00) >> 8;
	for (int i = 0; i <= X; i++) {
		V[i] = get_byte(I + i);
	}
}
