#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "file.h"

#ifndef CONFIG_H

#define get_r(color) ((color) >> 16)
#define get_g(color) (((color) >> 8) & 0xFF)
#define get_b(color) ((color)&0xFF)

typedef struct entry_type
{
    char key[SIZE_LINE + 1], val[SIZE_LINE + 1];
    int index;
} Entry;

typedef struct config_type
{
    const char *filename;
    int n_entries;
    Entry *map;
} * Config;

static void read_key(const int n,
                     FILE *fp,
                     Entry *map)
{
    char ch;
    int i = 0;

    while ((ch = fgetc(fp)) != EOF && ch != '=')
    {
        if (i < n && !isspace(ch))
            map->key[i++] = ch;
    }
    map->key[i] = '\0';
}

static void read_val(const int n,
                     FILE *fp,
                     Entry *map)
{
    char ch;
    int i = 0;

    while ((ch = fgetc(fp)) != EOF && ch != '\n' && ch != ',')
    {
        if (i < SIZE_LINE && !isspace(ch))
            map->val[i++] = ch;
    }
    map->val[i] = '\0';
}

static void string_to_int(const char *str,
                          int *ret)
{
    char *ptr;
    *ret = strtol(str,
                  &ptr,
                  10);
}

static void string_to_color(const char *str,
                            uint8_t *r,
                            uint8_t *g,
                            uint8_t *b)
{
    long int color = 0;
    sscanf(str, "%x", &color);
    *r = get_r(color);
    *g = get_g(color);
    *b = get_b(color);
}

static int read_entry(int n_chars,
                      FILE *fp,
                      Entry *map)
{
    //READ KEY
    read_key(n_chars,
             fp,
             map);

    //READ VAL
    read_val(n_chars,
             fp,
             map);

    return (feof(fp) == NULL);
}

static int get_entry_index(Config cfg,
                           const int offset,
                           const char *key)
{
    int aux = offset;

    for (int i = 0; i < cfg->n_entries; i++)
    {
        if (strncmp(key, cfg->map[i].key, SIZE_LINE) == 0)
        {
            if (aux == 0)
                return cfg->map[i].index;
            else
                aux--;
        }
    }

    return ENTRY_NOT_FOUND;
};


int cfg_get_int(Config cfg,
                int offset,
                int *val,
                const char *key)
{
    int id = get_entry_index(cfg,
                             offset,
                             key);

    if (id == ENTRY_NOT_FOUND)
        return ENTRY_NOT_FOUND;

    string_to_int(cfg->map[id].val,
                  val);

    return ENTRY_FOUND;
}

int cfg_get_int_multiple(Config cfg,
                         int n,
                         int offset,
                         int val[n],
                         const char *key[n])
{
    for (int i = 0, result = 0; i < n; i++)
    {
        result = cfg_get_int(cfg,
                             offset,
                             &val[i],
                             key[i]);

        if (result == ENTRY_NOT_FOUND)
            return ENTRY_NOT_FOUND;
    }

    return ENTRY_FOUND;
}

int cfg_get_color(Config cfg,
                  int offset,
                  const char *key,
                  uint8_t colors[CHANNELS])
{
    int id = get_entry_index(cfg,
                             offset,
                             key);

    if (id == ENTRY_NOT_FOUND)
        return ENTRY_NOT_FOUND;

    string_to_color(cfg->map[id].val,
                    &colors[0],
                    &colors[1],
                    &colors[2]);

    return ENTRY_FOUND;
}

int cfg_get_color_array(Config cfg,
                        int offset,
                        const int n,
                        const char *key,
                        uint8_t colors[n][CHANNELS])
{
    int result = 0, i = 0;

    uint8_t aux[CHANNELS] = {0};
    while (i < n)
    {
        if (result == ENTRY_NOT_FOUND)
            return ENTRY_NOT_FOUND;

        result = cfg_get_color(cfg,
                               i,
                               key,
                               colors[i]);

        i++;
    }
}

int cfg_get_string(Config cfg,
                   const int n,
                   const int offset,
                   const char *key,
                   char *dest)
{
    int id = get_entry_index(cfg,
                             offset,
                             key);

    if (id == ENTRY_NOT_FOUND)
        return ENTRY_NOT_FOUND;

    strncpy(dest,
            cfg->map[id].val,
            n);
    return ENTRY_FOUND;
}

int cfg_open(Config cfg)
{
    FILE *fp = file_open(cfg->filename,
                         "r");

    int i = 0,
        n = cfg->n_entries;

    while (i < n && read_entry(SIZE_LINE,
                               fp,
                               &cfg->map[i]))
    {
        cfg->map[i].index = i;
        i++;
    }

    fclose(fp);
    return i;
}

Config cfg_create(const int n,
                  const char *filename)
{
    Config cfg = calloc(1,
                        sizeof(struct config_type));
    cfg->map = calloc(n,
                      sizeof(struct entry_type));
    cfg->filename = filename;
    cfg->n_entries = n;
    return cfg;
}

void cfg_print_keys(Config cfg,
                    const int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d: %s = %s\n",
               cfg->map[i].index,
               cfg->map[i].key,
               cfg->map[i].val);
    }
}

void cfg_destroy(Config cfg)
{
    free(cfg->map);
    free(cfg);
}

#endif /* CONFIG_H */