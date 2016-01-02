// No copyrights, it's free.
#ifndef _Main_H
#define _Main_H

#include <SDL2/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;

SDL_Window *window;
SDL_GLContext context;

void init();
void close();

#endif
