//Using SDL and standard IO#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <assert.h>
#include "graphics.h"

typedef struct gfx_type
{
    SDL_Surface *screen;
    int screen_width,
        screen_height,
        bits_per_pixel;

    uint8_t screen_pixels[INTERNAL_WIDTH][INTERNAL_HEIGHT],
        colors[CHANNELS],
        background[CHANNELS];
};

Gfx gfx_create(int screen_width,
               int screen_height,
               const pallet pallets,
               const char *filename)
{
    Gfx gfx = malloc(sizeof(struct gfx_type));
    gfx->screen_width = screen_width;
    gfx->screen_height = screen_height;
    gfx->bits_per_pixel = 32;

    gfx->colors[0] = pallets.colors[0];
    gfx->colors[1] = pallets.colors[1];
    gfx->colors[2] = pallets.colors[2];
    gfx->background[0] = pallets.background[0];
    gfx->background[1] = pallets.background[1];
    gfx->background[2] = pallets.background[2];
    /*
    gfx->colors[0] = pallet[0][0];
    gfx->colors[1] = pallet[1][0];
    gfx->colors[2] = pallet[2][0];
    gfx->background[0] = pallet[0][1];
    gfx->background[1] = pallet[1][1];
    gfx->background[2] = pallet[2][1];

    gfx->colors[0] = 43;
    gfx->colors[1] = 83;
    gfx->colors[2] = 41;
    gfx->background[0] = 156;
    gfx->background[1] = 204;
    gfx->background[2] = 156;
    */

    memset(gfx->screen_pixels,
           0,
           sizeof(gfx->screen_pixels[0][0]) * INTERNAL_WIDTH * INTERNAL_HEIGHT);

    //Init sdl subsystems
    if (gfx_init(filename, gfx) == 0)
    {
        fprintf(stderr, "Error while initiating sdl\n");
        return EXIT_FAILURE;
    }

    return gfx;
}

void gfx_draw_pixel(SDL_Rect rect,
                    uint8_t colors[CHANNELS],
                    Gfx gfx)
{
    SDL_FillRect(gfx->screen,
                 &rect,
                 SDL_MapRGB(gfx->screen->format, colors[0], colors[1], colors[2]));
}

void gfx_draw_sprite(uint8_t offset_x,
                     uint8_t offset_y,
                     uint8_t pixel_size,
                     uint8_t sprite_height,
                     uint8_t sprite[],
                     Gfx gfx)
{
    uint8_t mask = (1 << 7), pixel = 0;

    for (int i = 0; i < sprite_height; i++)
    {
        pixel = sprite[i];

        for (int j = 0; j < 8; j++)
        {
            gfx->screen_pixels[offset_x + j][offset_y + i] =
                ((pixel & (mask >> j))) ? 1 : 0;
        }
    }
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

void gfx_clean_up(Gfx gfx)
{
    SDL_FreeSurface(gfx->screen);

    //Quit SDL
    SDL_Quit();
}

void gfx_draw_screen(Gfx gfx)
{
    SDL_Rect rect = {.x = 0,
                     .y = 0,
                     .w = INTERNAL_WIDTH * PIXEL_SIZE,
                     .h = INTERNAL_HEIGHT * PIXEL_SIZE};

    for (int y = 0; y < INTERNAL_HEIGHT; y++)
    {
        for (int x = 0; x < INTERNAL_WIDTH; x++)
        {
            rect.x = x * PIXEL_SIZE;
            rect.y = y * PIXEL_SIZE;
            rect.h = PIXEL_SIZE;
            rect.w = PIXEL_SIZE;

            printf("%d", gfx->screen_pixels[x][y]);
            if (gfx->screen_pixels[x][y])
            {
                gfx_draw_pixel(rect,
                               gfx->colors,
                               gfx);
            }
            else
            {
                gfx_draw_pixel(rect,
                               gfx->background,
                               gfx);
            }
        }
        printf("\n");
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

bool gfx_init(const char *filename,
              Gfx gfx)
{
    //Start SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return false;
    }

    //Set up screen
    gfx->screen = SDL_SetVideoMode(gfx->screen_width,
                                   gfx->screen_height,
                                   gfx->bits_per_pixel,
                                   SDL_SWSURFACE);

    //Set the window caption
    SDL_WM_SetCaption(filename, NULL);

    return true;
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
