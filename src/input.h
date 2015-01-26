#ifndef INPUT_H
#define INPUT_H

#include <GLUT/glut.h>

#define NUM_KEYS 16

// keys pressed
unsigned char key[NUM_KEYS];

int is_key_pressed(unsigned char VX);
void keyboard_down(unsigned char k, int x, int y);
void keyboard_up(unsigned char k, int x, int y);

#endif
