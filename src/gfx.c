#include "gfx.h"
#include "input.h"
#include "cpu.h"
#include <GLUT/glut.h>

void init_gfx() {
	for (int i = 0; i < NUM_PIXELS; i++) gfx[i] = 0;
}

void set_pixel(int r, int c, unsigned char value) {    gfx[r * 64 + c] = value;
}
    
unsigned char get_pixel(int r, int c) {
    return gfx[r * 64 + c];
}


void reshape_window(GLsizei w, GLsizei h) {
    glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);

    display_width = w;
    display_height = h;
}

void draw_pixel(int x, int y) {
    glBegin(GL_QUADS);
    glVertex3f((x * MODIFIER) + 0.0f,     (y * MODIFIER) + 0.0f,     0.0f);
    glVertex3f((x * MODIFIER) + 0.0f,     (y * MODIFIER) + MODIFIER, 0.0f);
    glVertex3f((x * MODIFIER) + MODIFIER, (y * MODIFIER) + MODIFIER, 0.0f);
    glVertex3f((x * MODIFIER) + MODIFIER, (y * MODIFIER) + 0.0f,     0.0f);
    glEnd();
}

void initTexture() {
    // Clear screen
    for(int y = 0; y < SCREEN_HEIGHT; ++y) {              
        for(int x = 0; x < SCREEN_WIDTH; ++x) {
            screen_data[y][x][0] = screen_data[y][x][1] = screen_data[y][x][2] = 0;
        }
    }

    // Create a texture 
    glTexImage2D(GL_TEXTURE_2D, 0, 3, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screen_data);

    // Set up the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); 

    // Enable textures
    glEnable(GL_TEXTURE_2D);
}

void update_texture() {
    for(int y = 0; y < 32; ++y) {           
        for(int x = 0; x < 64; ++x) {
            if(gfx[(y * 64) + x] == 0)
                screen_data[y][x][0] = screen_data[y][x][1] = screen_data[y][x][2] = 0;    // Disabled
            else 
                screen_data[y][x][0] = screen_data[y][x][1] = screen_data[y][x][2] = 255;  // Enabled
        }
    }

    // Update Texture
    glTexSubImage2D(GL_TEXTURE_2D, 0 ,0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screen_data);

    glBegin( GL_QUADS );
    glTexCoord2d(0.0, 0.0);         glVertex2d(0.0, 0.0);
    glTexCoord2d(1.0, 0.0);         glVertex2d(display_width, 0.0);
    glTexCoord2d(1.0, 1.0);         glVertex2d(display_width, display_height);
    glTexCoord2d(0.0, 1.0);         glVertex2d(0.0, display_height);
    glEnd();
}

void update_quads() {
    // Draw
    for(int y = 0; y < 32; ++y) {            
        for(int x = 0; x < 64; ++x) {
            if(gfx[(y*64) + x] == 0) 
                glColor3f(0.0f,0.0f,0.0f);                      
            else 
                glColor3f(1.0f,1.0f,1.0f);
            draw_pixel(x, y);
        }
    }
}
