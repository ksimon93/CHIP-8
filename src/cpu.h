#define NUM_REGISTERS 16
#define MEMORY_SIZE 4096
#define STACK_SIZE 16
#define NUM_KEYS 16
#define NUM_PIXELS 64*32
#define PC_START_ADDRESS 0x200

void initialize(); 		// initialize hardware in CPU
void arithmetic();
void fdx_cycle(); 		// fetch_decode_execute cycle
void fetch();			// get current instruction from memory, inc pc
void execute();			// index into function table with opcode

/* OPCODES */
void NOP();
void call_subroutine(); // 0x2NNN

				/* HARDWARE, REGISTERS, etc. */
/* =============================================================*/

unsigned short opcode;
unsigned short instruction;
unsigned char memory[MEMORY_SIZE];

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

// keys pressed
unsigned char key[NUM_KEYS];

unsigned char gfx[NUM_PIXELS];



// function pointers for opcode tables
void (*function_table[17])();
void (*arithmetic_table[16])();