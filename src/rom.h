#include <stdbool.h>
#include <stdint.h>

#ifndef ROM_H
#define ROM_H

typedef struct rom_type
{
    long n;       //number of chars
    uint8_t *ptr; //pointer to rom
} * ROM;

//const char *filename
ROM rom_create();

bool rom_read_data(ROM rom,
                   const long n,
                   const uint8_t *data);

bool rom_read_file(ROM rom,
                   const char *filename);

void rom_destroy(ROM rom);

#endif /* ROM_H */