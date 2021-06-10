#include "config.h"

Config cfg_create()
{
    int n_pallet = 10;
    Config conf;

    conf = malloc(sizeof(Config) + ((sizeof(pallet) * n_pallet)));
    conf->SCREEN_WIDTH = 640;
    conf->SCREEN_HEIGHT = 480;
    conf->BITS_PER_PIXEL = 32;
    strcpy(conf->tab_name, "Hello World");

    conf->pallets[0] = (pallet){.colors = {43, 83, 41},
                                .background = {156, 204, 156}};
    conf->pallets[1] = (pallet){.colors = {250, 240, 230},
                                .background = {25, 25, 25}};
    conf->pallets[2] = (pallet){.colors = {25, 25, 25},
                                .background = {250, 240, 230}};
    conf->pallets[3] = (pallet){.colors = {214, 38, 67},
                                .background = {194, 231, 229}};
    conf->pallets[4] = (pallet){.colors = {242, 217, 199},
                                .background = {48, 212, 193}};
    conf->pallets[5] = (pallet){.colors = {251, 249, 243},
                                .background = {50, 56, 70}};
    conf->pallets[6] = (pallet){.colors = {251, 249, 243},
                                .background = {12, 140, 108}};

    return conf;
}

void cfg_destroy(Config cfg)
{
        free(cfg);
}