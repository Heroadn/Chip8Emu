#include <stdio.h>
#include <stdlib.h>
#include "../include/file.h"
#include "rom.h"

#define ERROR false
#define SUCESS true

ROM rom_create(const char *filename)
{
    ROM rom = malloc(sizeof(struct rom_type));

    if (rom == NULL)
        fprintf(stderr, "Couldn't alloc memory for the rom\n");

    //carregando rom
    if (rom_read(rom,
                 filename) == ERROR)
    {
        fprintf(stderr, "Rom couldn't be read or, not found\n");
    }

    return rom;
}

bool rom_read(ROM rom,
              const char *filename)
{
    //oppening the file and checking for erros
    FILE *fp = file_open(filename, "rb");
    if (fp == NULL)
        return ERROR;

    //number of chars
    long n = file_nchars(fp);
    char *ptr = malloc(n * sizeof(char));

    //allocating mem for chars
    if (ptr == NULL)
    {
        fprintf(stderr, "Couldn't alloc memory for the rom\n");
        return ERROR;
    }

    //reading rom
    if ((fread(ptr, sizeof(char), (long)n, fp)) != n)
    {
        fprintf(stderr, "Something went wrong with the rom,"
                        "did you put your glasses on? ;)\n");

        return ERROR;
    }

    //freeing file
    fclose(fp);

    rom->ptr = ptr;
    rom->nchars = n;
    return SUCESS;
}

void rom_destroy(ROM rom)
{
    free(rom->ptr);
    free(rom);
}