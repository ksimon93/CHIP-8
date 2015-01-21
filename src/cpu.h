#define NUM_REGISTERS 16
#define STACK_SIZE 16
#define PC_START_ADDRESS 0x200

void init_cpu(); 		// initialize hardware in CPU
void arithmetic();
void cpu_cycle(); 		// fetch_decode_execute cycle
void fetch();			// get current instruction from memory, inc pc
void execute();			// index into function table with opcode

/* function pointers for opcode tables */
void (*function_table[17])();
void (*eight_function_table[15])();

/* OPCODES */
void NOP();
void op_00E0(); 		// Clears the screen.
void op_00EE(); 		// Returns from subroutine.
void op_1NNN(); 		// Jumps to address NNN
void op_2NNN(); 		// Calls subroutine at address NNN.
void op_3XNN(); 		// Skips the next instruction if VX equals NN.
void op_4XNN(); 		// Skips the next instruction if VX doesn't equal NN.
void op_5XY0(); 		// Skips the next instruction if VX equals VY.
void op_6XNN();			// Sets VX to NN.
void op_7XNN();			// Adds NN to VX.
void op_8XY0();         	// Sets VX to the value of VY.
void op_8XY1();         	// Sets VX to VX | VY
void op_8XY2();        	 	// Sets VX to VX & VY
void op_8XY3();         	// Sets VX to VX xor VY
void op_8XY4();         	// Adds VY to VX. Set carry if necesscary.
void op_8XY5();         	// VY is subtracted from VX. Set borrow if necesscary.
void op_8XY6();         	// Shifts VX right by one. Set VF to LSB.
void op_8XY7();         	// Sets VX to VY minus VX. Set borrow if necesscary.
void op_8XYE();         	// Shifts VX left by one. Set VF to MSB.
void op_9XY0();         	// Skips next instruction if VX != VY.
void op_ANNN();         	// Sets I to the address NNN.
void op_BNNN();         	// Jumps to the address NNN plus V0.
void op_CXNN();         	// sets VX to a random number & NN.
void op_DXYN();         	// Draw to screen. See wikipedia entry for more details.
void op_EX9E();         	// Skips the next instruction if the key store in VX is pressed.
void op_EXA1();         	// Skips the next instruction if the key stored in VX isn't pressed.
void op_FX07();         	// Sets VX to the value of the delay timer.
void op_FX0A();         	// A key press is awaited, and then stored in VX.
void op_FX15();         	// Sets the delay timer to VX.
void op_FX18();         	// Sets the sound timer to VX.
void op_FX1E();         	// Adds VX to I.
void op_FX29();         	// Sets I to the location of the sprite for the character in VX.
void op_FX33();         	// See wikipedia entry for FX33, it's really long.
void op_FX55();         	// Stores V0 to VX in memory starting at address I.
void op_FX65();         	// Fills V0 to VX with values from memory starting at address I.


		/* HARDWARE, REGISTERS, etc. */
/* =============================================================*/
unsigned short opcode;
unsigned short instruction;

unsigned char V[NUM_REGISTERS]; 	// general purpose registers

unsigned short I;			// index register

unsigned short pc; 			// program counter

unsigned char delay_timer;		// timers
unsigned char sound_timer;

unsigned short stack[STACK_SIZE];
unsigned short sp;

unsigned int seed;                  	// seed used for RNG
