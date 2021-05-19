#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)
#define N_POINTS (9 * 9 * 9)


uint32_t *color_buffer;
SDL_Texture *color_buffer_texture;

int window_width;
int window_height;


SDL_Window *window;
SDL_Renderer *renderer;

bool initialize_window(void);

void draw_grid(void);
void draw_pixel(int x, int y, uint32_t color);
void draw_rect(int x, int y, int width, int height, uint32_t color);

void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void destroy_window(void);

#endif