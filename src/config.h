#include "graphics.h"

typedef struct
{
    //Screen dimension constants
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int BITS_PER_PIXEL;
    char tab_name[255];
    pallet pallets[];
} *Config;


Config cfg_create();

void cfg_destroy(Config cfg);