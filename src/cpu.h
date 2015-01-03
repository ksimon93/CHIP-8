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
void (*zero_function_table[2])();

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

				/* HARDWARE, REGISTERS, etc. */
/* =============================================================*/
unsigned short opcode;
unsigned short instruction;

unsigned char V[NUM_REGISTERS]; 	// general purpose registers

unsigned short I;					// index register

unsigned short pc; 					// program counter

unsigned char delay_timer;			// timers
unsigned char sound_timer;

unsigned short stack[STACK_SIZE];
unsigned short sp;