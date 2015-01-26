#include "input.h"
#include <stdlib.h>
#include <GLUT/glut.h>

int is_key_pressed(unsigned char VX) {
	return key[VX];
}

void keyboard_down(unsigned char k, int x, int y) {
    if (k == 27)  exit(0); // esc

    else if (k == '1') key[0x1] = 1;
    else if (k == '2') key[0x2] = 1;
    else if (k == '3') key[0x3] = 1;
    else if (k == '4') key[0xC] = 1;

    else if (k == 'q') key[0x4] = 1;
    else if (k == 'w') key[0x5] = 1;
    else if (k == 'e') key[0x6] = 1;
    else if (k == 'r') key[0xD] = 1;

    else if (k == 'a') key[0x7] = 1;
    else if (k == 's') key[0x8] = 1;
    else if (k == 'd') key[0x9] = 1;
    else if (k == 'f') key[0xE] = 1;

    else if (k == 'z') key[0xA] = 1;
    else if (k == 'x') key[0x0] = 1;
    else if (k == 'c') key[0xB] = 1;
    else if (k == 'v') key[0xF] = 1;
}

void keyboard_up(unsigned char k, int x, int y) {
    if (k == '1')      key[0x1] = 0;
    else if (k == '2') key[0x2] = 0;
    else if (k == '3') key[0x3] = 0;
    else if (k == '4') key[0xC] = 0;
    
    else if (k == 'q') key[0x4] = 0;
    else if (k == 'w') key[0x5] = 0;
    else if (k == 'e') key[0x6] = 0;
    else if (k == 'r') key[0xD] = 0;

    else if (k == 'a') key[0x7] = 0;
    else if (k == 's') key[0x8] = 0;
    else if (k == 'd') key[0x9] = 0;
    else if (k == 'f') key[0xE] = 0;

    else if (k == 'z') key[0xA] = 0;
    else if (k == 'x') key[0x0] = 0;
    else if (k == 'c') key[0xB] = 0;
    else if (k == 'v') key[0xF] = 0;
}