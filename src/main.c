/* 
 * Author:    Wadie Assal: 
 * Project:   Amber: Scalable Video Wall
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <glib.h>
#include <SDL2/SDL.h>

#include "render.h"
#include "network.h"

#define WIDTH 640
#define HEIGHT 480

int main(int argc, char *argv[]) {
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Starting Amber");

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s", SDL_GetError());
		exit(1);
	}

	// Initialize rendering & networking
	render_init(WIDTH, HEIGHT, "vertex.glsl", "fragment.glsl");
	int test_png = render_load_texture("test.png");
	network_init();

	// Add some channels
	render_add_channel(0, 0, 0.5, 0.5, 0);
	render_add_channel(0.5, 0, 0.5, 0.5, 0);

	// Initialize timer
	unsigned int lastTime = 0, currentTime;

	SDL_Event event;
	bool running = true;

	// Main render loop
	while (running) {

		// Handle SDL events
		while( SDL_PollEvent(&event) ) {
			if(event.type == SDL_QUIT) {
				running = false;
			}
		}

		network_get_command();
		render_handle_command();

		// Run at 50 FPS
		currentTime = SDL_GetTicks();
		if (currentTime > lastTime + 20) {
			render(WIDTH, HEIGHT, 0);
			lastTime = currentTime;
		}

		// If less then one millisecond has passed, delay by one millisecond
		currentTime = SDL_GetTicks();
		if (currentTime > lastTime + 1) {
			SDL_Delay(1);
		}
	}

	// Cleanup and exit
	render_close();
	network_close();
	SDL_Quit();
	exit(0);
}
