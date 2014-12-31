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
void (*arithmetic_table[16])();

/* OPCODES */
void NOP();
void op_00E0(); // Clears the screen.
void op_00EE(); // Returns from subroutine.
void op_1NNN(); // Jumps to address NNN
void op_2NNN(); // Calls subroutine at address NNN.

				/* HARDWARE, REGISTERS, etc. */
/* =============================================================*/
unsigned short opcode;
unsigned short instruction;

// general purpose registers
unsigned char V[NUM_REGISTERS];

// index register
unsigned short I;

// program counter
unsigned short pc;

// timers
unsigned char delay_timer;
unsigned char sound_timer;

unsigned short stack[STACK_SIZE];
unsigned short sp;
