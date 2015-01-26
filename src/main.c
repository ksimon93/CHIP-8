#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include "cpu.h"
#include "mem.h"
#include "gfx.h"
#include "input.h"

int main (int argc, char *argv[]) {
	init_cpu();
    if (argc > 0)
        load_rom(*(argv + 1));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(display_width, display_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("CHIP-8");
    glutDisplayFunc(cpu_cycle);
    glutIdleFunc(cpu_cycle);
    glutReshapeFunc(reshape_window);
    glutKeyboardFunc(keyboard_down);
    glutKeyboardUpFunc(keyboard_up);

    update_texture();
    glutMainLoop();
}
