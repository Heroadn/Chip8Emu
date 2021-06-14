#include "graphics.h"

typedef struct config_type
{
    //Screen dimension constants
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int BITS_PER_PIXEL;
    char tab_name[255];
    pallet pallets[8];
} *Config;

Config cfg_create(char *filename);

void cfg_destroy(Config cfg);