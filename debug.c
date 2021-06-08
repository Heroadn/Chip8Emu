#include <stdio.h>
#include <stdint.h>

#define INTERNAL_WIDTH 64
#define INTERNAL_HEIGHT 32
#define PIXEL_SIZE 32

void gfx_draw_sprite(uint8_t offset_x,
                     uint8_t offset_y,
                     uint8_t pixel_size,
                     uint8_t sprite_height,
                     uint8_t screen_bits[INTERNAL_WIDTH * INTERNAL_HEIGHT],
                     uint8_t sprite[],
                     uint8_t colors[])
{
    uint8_t mask = (1 << 7), x = 0, y = 0, pixel = 0, loc = 0;

    for (int i = 0; i < sprite_height; i++)
    {
        pixel = sprite[i];

        for (int j = 0; j < 8; j++)
        {
            x = (offset_x + j);
            loc = x + y * INTERNAL_WIDTH;
            screen_bits[loc] = ((pixel & (mask >> j)))? 1 : 0;
        }

        y = (offset_y + i + 1);
    }
}

int main(void)
{
    uint8_t screen_bits[INTERNAL_WIDTH * INTERNAL_HEIGHT] = { 0 },
            sprite[4] = {0xe0, 0x60, 0x20, 0xe0},
            colors[3] = {255, 0, 0};

    gfx_draw_sprite(0,
                    0,
                    PIXEL_SIZE,
                    4,
                    screen_bits,
                    sprite,
                    colors);

    for (int y = 0; y < INTERNAL_HEIGHT; y++)
    {
        for (int x = 0; x < INTERNAL_WIDTH; x++)
        {
            printf("%d", screen_bits[x + y * INTERNAL_WIDTH]);
        }
        printf("\n");
    }
}