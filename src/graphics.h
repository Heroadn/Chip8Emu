#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>

#ifndef GRAPHICS_H
#define GRAPHICS_H

#define INTERNAL_WIDTH 64
#define INTERNAL_HEIGHT 32
#define PIXEL_SIZE 8
#define CHANNELS 3

typedef struct gfx_type *Gfx;

//
Gfx gfx_create(int screen_width,
               int screen_height,
               const char *filename);

//
void gfx_destroy(Gfx gfx);

//
void gfx_draw_pixel(SDL_Rect rect,
                    uint8_t colors[],
                    Gfx gfx);

//
void gfx_draw_sprite(uint8_t offset_x,
                     uint8_t offset_y,
                     uint8_t pixel_size,
                     uint8_t sprite_height,
                     uint8_t sprite[],
                     Gfx gfx);

//
void gfx_draw_screen(Gfx gfx);

//Copying the image from one surface to another
void gfx_apply_surface(int x,
                       int y,
                       SDL_Surface *source,
                       SDL_Surface *destination);

//
void gfx_clean_up(Gfx gfx);

//
void gfx_flip(Gfx gfx);

//
SDL_Surface *gfx_load_image(char *filename);

//
bool gfx_init(const char *filename,
              Gfx gfx);

//
bool gfx_load_files(SDL_Surface **image,
                    const char *filename[]);

#endif /* GRAPHICS_H */