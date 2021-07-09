#include "config.h"
#include <stdio.h>
#include <string.h>

#define DEBUG_ENTRIES 20
const char *config_keys[DEBUG_ENTRIES] = {"SCREEN_WIDTH",
                                          "SCREEN_HEIGHT",
                                          "BITS_PER_PIXEL",
                                          "TAB_NAME",
                                          "colors", "background",
                                          "colors", "background",
                                          "colors", "background",
                                          "colors", "background",
                                          "colors", "background",
                                          "colors", "background",
                                          "colors", "background",
                                          "colors", "background"};

int main(void)
{

    Config cfg = cfg_create(DEBUG_ENTRIES,
                            "config.cfg");
    int n = 0,
        m = 0,
        val[4];

    n = cfg_open(cfg);
    cfg_get_int_multiple(cfg,
                         4,
                         0,
                         val,
                         config_keys);
    printf("%s = %d\n", config_keys[0], val[0]);
    printf("%s = %d\n", config_keys[1], val[1]);
    printf("%s = %d\n", config_keys[2], val[2]);

    char tab[64];
    cfg_get_string(cfg,
                   62,
                   0,
                   config_keys[3],
                   tab);
    printf("%s = %s\n", config_keys[3], tab);

    int offset = 0, max = 8;
    uint8_t colors[max][CHANNELS];

    cfg_get_color_array(cfg,
                        0,
                        max,
                        config_keys[4],
                        colors);

    for (int i = 0; i < max; i++)
    {
        printf("%s = %x%x%x\n", config_keys[4], colors[i][0], colors[i][1], colors[i][2]);
    }

    cfg_get_color_array(cfg,
                        0,
                        max,
                        config_keys[5],
                        colors);

    for (int i = 0; i < max; i++)
    {
        printf("%s = %x%x%x\n", config_keys[5], colors[i][0], colors[i][1], colors[i][2]);
    }

    //
    /*cfg_get_color(cfg, offset, config_keys[4], colors);
    printf("%s = %x%x%x\n", config_keys[4], colors[0], colors[1], colors[2]);

    cfg_get_color(cfg, offset, config_keys[5], colors);
    printf("%s = %x%x%x\n", config_keys[5], colors[0], colors[1], colors[2]);
    offset++;

    //    
    cfg_get_color(cfg, offset, config_keys[4], colors);
    printf("%s = %x%x%x\n", config_keys[4], colors[0], colors[1], colors[2]);

    cfg_get_color(cfg, offset, config_keys[5], colors);
    printf("%s = %x%x%x\n", config_keys[5], colors[0], colors[1], colors[2]);
    */

    /*
    
    for (int i = 0; i < DEBUG_ENTRIES; i++)
    {
        cfg_get_string(cfg,
                       62,
                       offset,
                       config_keys[i],
                       tab);
        printf("%s\n", tab);

        if(strcmp(config_keys[i], "background") == 0)
            offset++;
    }*/

    cfg_destroy(cfg);

    /*
    int val = 0;
    cfg_get_int(cfg,
                &val,
                config_keys[0]);
    printf("%s = %d\n", config_keys[0], val);

    cfg_get_int(cfg,
                &val,
                config_keys[1]);
    printf("%s = %d\n", config_keys[1], val);
    */

    return 0;
}