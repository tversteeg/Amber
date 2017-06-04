#pragma once

#include <SDL2/SDL.h>
#include <GL/gl.h>

int render_init();

int render_handle_command();

int render(SDL_Window *window);

int render_close();