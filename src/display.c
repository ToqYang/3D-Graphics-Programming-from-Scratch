#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "display.h"

extern SDL_Window *window = NULL;
extern SDL_Renderer *renderer = NULL;
extern uint32_t *color_buffer = NULL;
extern SDL_Texture *color_buffer_texture = NULL;
extern int window_width = 800;
extern int window_height = 600;

bool initialize_window(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return false;
	}

	// Use SDL to query what is the fullscreen max. width and height
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);

	window_width = display_mode.w;
	window_height = display_mode.h;

	// Create SDL Window
	window = SDL_CreateWindow(NULL,
				  SDL_WINDOWPOS_CENTERED,
				  SDL_WINDOWPOS_CENTERED,
				  window_width,
				  window_height,
				  SDL_WINDOW_BORDERLESS);

	if (!window) {
		fprintf(stderr, "Error creating SDL window.\n");
		return false;
	}

	// Create SDL Renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Error creating SDL renderer.\n");
		return false;
	}
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	return true;
}

void clear_color_buffer(uint32_t color)
{
	for (int y = 0; y < window_height; y++) {
		for (int x = 0; x < window_width; x++) {
			color_buffer[(window_width * y) + x] = color;
		}
	}
}

void render_color_buffer(void)
{
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int)(window_width * sizeof(uint32_t)));

	SDL_RenderCopy(
		renderer,
		color_buffer_texture,
		NULL,
		NULL);
}

void draw_grid(void)
{
	for (int y = 0; y < window_height; y += 10) {
		for (int x = 0; x < window_width; x += 10) {
			color_buffer[(window_width * y) + x] = 0xFF0000FF;
		}
	}
}

void draw_pixel(int x, int y, uint32_t color)
{
	if (x < window_width && y < window_height) {
		color_buffer[(window_width * y) + x] = color;
	}
}

void draw_rect(int x, int y, int width, int height, uint32_t color)
{
	// 1) Get position
	// 2) Make other loop until the height
	// 3) Inside make a loop until width
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int current_x = x + i;
			int current_y = y + j;
			color_buffer[(window_width * current_y) + current_x] = color;
		}
	}
}

void destroy_window(void)
{
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}