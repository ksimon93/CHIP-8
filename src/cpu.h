void initiailze(); 		// initialize hardware in CPU
void fetch();			// get current instruction from memory, inc pc
void execute();			// 
void arithmetic();
void fdx_cycle(); 		// fetch_decode_execute cycle

/* OPCODES */
void NOP();
void call_subroutine(); // 0x2NNN