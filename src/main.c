/* 
 * Author:    Wadie Assal: 
 * Project:   Amber: Scalable Video Wall
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <glib.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "render.h"
#include "network.h"

static bool running = true;
static SDL_Window *window = NULL;
static SDL_GLContext gl_context;


int main(int argc, char *argv[]) {
    
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Starting Amber");
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s", SDL_GetError());
        exit(1);
    }
    
    // Initialize SDL Window / OpenGl
    SDL_Event event;
    window = SDL_CreateWindow("Amber", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 512, 512, SDL_WINDOW_OPENGL);
    gl_context = SDL_GL_CreateContext(window);
    
    // Initialize networking
    // TODO: Create network connection
    
    // Initialize timer
    unsigned int lastTime = 0, currentTime;
    
    // Main render loop TODO: Time based (NTP)
    while (running) {
        
        // Handle SDL events
        while( SDL_PollEvent(&event) ) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
        }
            
        // TODO: Handle networking
        
        // Update timer
        currentTime = SDL_GetTicks();
        
        // Run at 50 FPS
        if (currentTime > lastTime + 20) {
            
            // Render and short delay before next rendered frame
            render_handle_commands(window, &gl_context);
            
            lastTime = currentTime;
        }
        
        // If less then one millisecond has passed, delay by one millisecond
        if (currentTime > lastTime + 1) {
            SDL_Delay(1);
        }
    }
    
    // Cleanup and exit
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
}