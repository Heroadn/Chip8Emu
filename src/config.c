#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "config.h"
#include "utils/file.h"

#define LINE_LEN 255
#define MAX_PALLETS 8

#define get_r(color) ((color) >> 16)
#define get_g(color) (((color) >> 8) & 0xFF)
#define get_b(color) ((color)&0xFF)

typedef struct
{
    char key[256], val[256];
} Map;

/*
typedef struct config_type
{
    //Screen dimension constants
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int BITS_PER_PIXEL;
    char tab_name[255];
    pallet pallets[8];
};*/

void cfg_get_property_string(char *name,
                             char *ret,
                             Map map)
{
    char *ptr;
    if (strcmp(name, map.key) == 0)
    {
        *ret = map.key;
    }
}

void cfg_get_property_int(const char *name,
                          int *ret,
                          Map *map)
{
    char *ptr;
    if (strcmp(name, map->key) == 0)
    {
        *ret = strtol(map->val,
                      &ptr,
                      10);
    }
}

bool cfg_get_property_hex_color(char *name,
                                uint8_t *r,
                                uint8_t *g,
                                uint8_t *b,
                                Map *map)
{
    long int color = 0;

    if (strcmp(name, map->key) == 0)
    {
        sscanf(map->val, "%x", &color);
        *r = get_r(color);
        *g = get_g(color);
        *b = get_b(color);
        return true;
        //printf("    %12s: ", map->key);
        //printf("%x%x%x\n", *r, *g, *b);
    }

    return false;
}

bool cfg_is_arr_tokens(Map map)
{
    if (map.key[0] == '{' ||
        map.key[0] == '}' ||
        map.val[0] == '{' ||
        map.key[0] == '[' ||
        map.key[0] == ']')
        return true;
    else
        return false;
}

void cfg_parser(Config cfg, char *filename)
{
    FILE *fp = file_open(filename, "r");
    Map map;

    int index_pallet = 0;
    uint8_t colors[3] = {0}, background[3] = {0};
    map.key[255] = '\0';
    map.val[255] = '\0';

    while (feof(fp) == NULL)
    {
        fscanf(fp, "%s = %s", &map.key, &map.val);
        cfg_get_property_int("SCREEN_WIDTH",
                             &cfg->SCREEN_WIDTH,
                             &map);

        cfg_get_property_int("SCREEN_HEIGHT",
                             &cfg->SCREEN_HEIGHT,
                             &map);

        cfg_get_property_int("BITS_PER_PIXEL",
                             &cfg->BITS_PER_PIXEL,
                             &map);
    }

    //colors
    rewind(fp);
    bool result = 0;
    while (feof(fp) == NULL)
    {
        fscanf(fp, "%s = %s", &map.key, &map.val);
        result = cfg_get_property_hex_color("colors",
                                            &cfg->pallets[index_pallet].colors[0],
                                            &cfg->pallets[index_pallet].colors[1],
                                            &cfg->pallets[index_pallet].colors[2],
                                            &map);
        if (result)
            index_pallet++;
    }

    //background
    rewind(fp);
    index_pallet = 0;
    while (feof(fp) == NULL)
    {
        fscanf(fp, "%s = %s", &map.key, &map.val);
        result = cfg_get_property_hex_color("background",
                                            &cfg->pallets[index_pallet].background[0],
                                            &cfg->pallets[index_pallet].background[1],
                                            &cfg->pallets[index_pallet].background[2],
                                            &map);

        if (result)
            index_pallet++;
    }

    fclose(fp);
}

Config cfg_create(char *filename)
{
    Config cfg = malloc(sizeof(struct config_type));
    strcpy(cfg->tab_name, "Hello World");
    cfg_parser(cfg, filename);

    cfg->pallets[0] = (pallet){.colors = {43, 83, 41},
                               .background = {156, 204, 156}};
    cfg->pallets[1] = (pallet){.colors = {250, 240, 230},
                               .background = {25, 25, 25}};
    cfg->pallets[2] = (pallet){.colors = {25, 25, 25},
                               .background = {250, 240, 230}};
    cfg->pallets[3] = (pallet){.colors = {214, 38, 67},
                               .background = {194, 231, 229}};
    cfg->pallets[4] = (pallet){.colors = {242, 217, 199},
                               .background = {48, 212, 193}};
    cfg->pallets[5] = (pallet){.colors = {251, 249, 243},
                               .background = {50, 56, 70}};
    cfg->pallets[6] = (pallet){.colors = {251, 249, 243},
                               .background = {12, 140, 108}};

    return cfg;
}

void cfg_destroy(Config cfg)
{
    free(cfg);
}