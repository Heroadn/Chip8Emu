#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "rom.h"

#define ERROR false
#define SUCESS true

//const char *filename
ROM rom_create()
{
    ROM rom = malloc(sizeof(struct rom_type));

    if (rom == NULL)
        fprintf(stderr, "Couldn't alloc memory for the rom\n");

    /*
    //carregando rom
    if (rom_read(rom,
                 filename) == ERROR)
        fprintf(stderr, "Rom couldn't be read or, not found\n");
    */
    return rom;
}

//a client error version when something went wrong while reading the file
void static error_reading_file()
{
    fprintf(stderr, "Rom couldn't be read or, not found\n");
}

bool rom_read_data(ROM rom,
                   const long n,
                   const uint8_t *data)
{
    rom->ptr = data;
    rom->n = n;
}

bool rom_read_file(ROM rom,
                   const char *filename)
{
    //oppening the file and checking for erros
    FILE *fp = file_open(filename, "rb");
    if (fp == NULL)
    {
        error_reading_file();
        return ERROR;
    }

    //number of chars
    long n = file_nchars(fp);
    uint8_t *ptr = malloc(n * sizeof(char));

    //allocating mem for chars
    if (ptr == NULL)
    {
        fprintf(stderr, "Couldn't alloc memory for the rom\n");
        error_reading_file();
        return ERROR;
    }

    //reading rom
    if ((fread(ptr, sizeof(uint8_t), (long)n, fp)) != n)
    {
        fprintf(stderr, "Something went wrong with the rom,"
                        "did you put your glasses on? ;)\n");
        error_reading_file();
        return ERROR;
    }

    //freeing file
    fclose(fp);

    rom->ptr = ptr;
    rom->n = n;
    return SUCESS;
}

void rom_destroy(ROM rom)
{
    free(rom->ptr);
    free(rom);
}