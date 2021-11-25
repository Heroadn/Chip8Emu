//Using SDL and standard IO#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>
#include "graphics.h"

typedef struct gfx_type
{
    SDL_Surface *screen;
    int screen_width,
        screen_height,
        pixel_width,
        pixel_height,
        bits_per_pixel;

    uint8_t screen_pixels[INTERNAL_WIDTH][INTERNAL_HEIGHT];
    uint8_t colors[LAYERS][CHANNELS];
    //uint8_t background[CHANNELS];
};

static uint8_t *select_color(Gfx gfx,
                             const int x,
                             const int y)
{
    /*
    return (gfx->screen_pixels[x][y]) ? gfx->colors
                                      : gfx->background;*/
    return gfx->colors[gfx->screen_pixels[x][y] == false];
}

static bool is_bit_set(uint8_t byte,
                       int i,
                       int mask)
{
    return (byte & (mask >> i)) == true;
}

Gfx gfx_create(const int width,
               const int height,
               const int bpp,
               const uint8_t colors[CHANNELS],
               const uint8_t background[CHANNELS],
               const char *name)
{
    Gfx gfx = malloc(sizeof(struct gfx_type));
    gfx->screen_width = width;
    gfx->screen_height = height;
    gfx->bits_per_pixel = bpp;
    gfx->pixel_width = ceil((double)width / INTERNAL_WIDTH);
    gfx->pixel_height = ceil((double)height / INTERNAL_HEIGHT);
    gfx->screen = gfx_init(name,
                           gfx);
    gfx_load_pallet(gfx,
                    colors,
                    background);
    return gfx;
}

void gfx_draw_pixel(SDL_Rect rect,
                    uint8_t colors[CHANNELS],
                    Gfx gfx)
{
    uint32_t color = SDL_MapRGB(gfx->screen->format,
                                colors[0],
                                colors[1],
                                colors[2]);

    SDL_FillRect(gfx->screen,
                 &rect,
                 color);
}

bool gfx_draw_sprite(uint8_t offset_x,
                     uint8_t offset_y,
                     uint8_t height,
                     uint8_t sprite[],
                     Gfx gfx)
{
    uint8_t mask = (1 << 7),
            new_pixel = 0,
            old_pixel = 0,
            sprite_pixel = 0,
            x = 0,
            y = 0;
    bool is_modified = false;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            x = (offset_x + j) % INTERNAL_WIDTH;
            y = (offset_y + i) % INTERNAL_HEIGHT;

            old_pixel = gfx->screen_pixels[x][y];
            new_pixel = (old_pixel ^ (sprite[i] & (mask >> j)));
            gfx->screen_pixels[x][y] = new_pixel;

            /*if the pixel was been turn off, is_modified = true 
              '||' if is_modified is true keep it as true */
            is_modified = is_modified || (old_pixel && new_pixel == false);
        }
    }

    return is_modified;
}

void gfx_load_pallet(Gfx gfx,
                     const uint8_t colors[CHANNELS],
                     const uint8_t background[CHANNELS])
{
    memcpy(gfx->colors[0], colors,
           CHANNELS * sizeof(uint8_t));
    memcpy(gfx->colors[1], background,
           CHANNELS * sizeof(uint8_t));
}

void gfx_apply_surface(int x,
                       int y,
                       SDL_Surface *source,
                       SDL_Surface *destination)
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface(source,
                    NULL,
                    destination,
                    &offset);
}

void gfx_clear_screen(Gfx gfx)
{
    memset(gfx->screen_pixels,
           0,
           sizeof(gfx->screen_pixels[0][0]) * INTERNAL_WIDTH * INTERNAL_HEIGHT);
    gfx_draw_screen(gfx);
}

void gfx_clean_up(Gfx gfx)
{
    //Quit SDL
    SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
    SDL_Quit();
}

void gfx_draw_screen(Gfx gfx)
{
    SDL_Rect rect = {.x = 0,
                     .y = 0,
                     .w = gfx->pixel_width,
                     .h = gfx->pixel_height};

    uint8_t *colors;

    for (int y = 0; y < INTERNAL_HEIGHT; y++)
    {
        for (int x = 0; x < INTERNAL_WIDTH; x++)
        {
            //can be precalculated
            rect.x = x * gfx->pixel_width;
            rect.y = y * gfx->pixel_height;

            colors = select_color(gfx,
                                  x,
                                  y);

            gfx_draw_pixel(rect,
                           colors,
                           gfx);
        }
    }
}

void gfx_flip(Gfx gfx)
{
    if (SDL_Flip(gfx->screen) == -1)
    {
        fprintf(stderr, "Error in flip\n");
        exit(EXIT_FAILURE);
    }
}

void gfx_destroy(Gfx gfx)
{
    free(gfx);
}

SDL_Surface *gfx_init(const char *name,
                      Gfx gfx)
{
    SDL_Surface *screen;

    //Start SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return false;
    }

    //Set up screen
    screen = SDL_SetVideoMode(gfx->screen_width,
                              gfx->screen_height,
                              gfx->bits_per_pixel,
                              SDL_SWSURFACE);

    //setsid
    if (screen == NULL)
    {
        fprintf(stderr, "Error when creating window\n");
        printf("Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //Set the window caption
    SDL_WM_SetCaption(name,
                      NULL);
    return screen;
}

bool gfx_load_files(SDL_Surface **image,
                    const char *filename[])
{
    *image = gfx_load_image(filename);
    return true;
}

SDL_Surface *gfx_load_image(char *filename)
{
    //Temporary storage for the image that's loaded
    SDL_Surface *loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface *optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load(filename);

    //If nothing went wrong in loading the image
    if (loadedImage != NULL)
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat(loadedImage);

        //Free the old image
        SDL_FreeSurface(loadedImage);
    }

    return optimizedImage;
}
