#include <stdint.h>
#define SIZE_KEYS 6
#define SIZE_LINE 64
#define CHANNELS 3
#define ENTRY_NOT_FOUND -1
#define ENTRY_FOUND 1

#ifndef CONFIG_H

typedef struct config_type *Config;

Config cfg_create(const int n,
                  const char *filename);

int cfg_get_int(Config cfg,
                int offset,
                int *val,
                const char *key);

int cfg_get_int_multiple(Config cfg,
                         int n,
                         int offset,
                         int val[n],
                         const char *key[n]);

int cfg_get_color(Config cfg,
                  int offset,
                  const char *key,
                  uint8_t colors[CHANNELS]);

int cfg_get_color_array(Config cfg,
                        int offset,
                        const int n,
                        const char *key,
                        uint8_t colors[][CHANNELS]);

int cfg_get_string(Config cfg,
                   const int n,
                   const int offset,
                   const char *key,
                   char *dest);

//returns the amount of keys reads, the amount is also limited by NUM_ENTRY
int cfg_open(Config cfg);

void cfg_print_keys(Config cfg,
                    const int n);

void cfg_destroy(Config cfg);

#endif /*CONFIG_H*/

/*
typedef struct config_type
{
    int SCREEN_WIDTH,
        SCREEN_HEIGHT,
        BITS_PER_PIXEL;
    char TAB_NAME[255];
    pallet pallets[SIZE_PALLETS];
} * Config;*/

/*
SCREEN_WIDTH = 512
SCREEN_HEIGHT = 256
BITS_PER_PIXEL = 32
TAB_NAME = HELLO_WORLD

colors = 2b5329, background = 9ccc9c
colors = faf0e6, background = 191919
colors = 191919, background = faf0e6
colors = d62643, background = c2e7e5
colors = f2d9c7, background = 30d4c1
colors = fbf9f3, background = 323846
colors = fbf9f3, background = 0c8c6c
colors = ffffff, background = 7289da 
colors = 0c040b, background = f4f4fc   
*/