#ifndef ROM_H
#define ROM_H

typedef struct rom_type
{
    //number of chars
    long nchars;

    //pointer to rom
    char *ptr;  
} *ROM;

ROM rom_create(const char *filename);

void rom_read(ROM rom, const char *filename);

void rom_destroy(ROM rom);

#endif /* ROM_H */