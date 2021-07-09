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