#ifndef GFX_H
#define GFX_H

#include <GLUT/glut.h>


#define FONTSET_SIZE 80
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define NUM_PIXELS 64*32
#define MODIFIER 10

static int display_width = SCREEN_WIDTH * MODIFIER;
static int display_height = SCREEN_HEIGHT * MODIFIER;

unsigned char gfx[NUM_PIXELS];
unsigned char screen_data [SCREEN_HEIGHT][SCREEN_WIDTH][3];

void init_gfx(); // clears screen
void create_screen(int *argcp, char **argv);
void reshape_window(GLsizei w, GLsizei h);
void set_pixel(int index, unsigned char value);
unsigned char get_pixel(int index);
void drawPixel(int x, int y);
void updateQuads();

#endif
