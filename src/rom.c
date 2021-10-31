#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "rom.h"

ROM rom_create(const char *filename)
{
    ROM rom = malloc(sizeof(struct rom_type));

    if (rom == NULL)
        fprintf(stderr, "Couldn't alloc memory for the rom\n");

    //carregando rom
    rom_read(rom,
             filename);
             
    return rom;
}

void rom_read(ROM rom,
              const char *filename)
{
    //oppening the file and checking for erros
    FILE *fp = file_open(filename, "rb");

    //number of chars
    long nchars = file_nchars(fp);

    //allocating mem for chars
    char *ptr = malloc(nchars * sizeof(char));
    if (ptr == NULL)
    {
        fprintf(stderr, "Couldn't alloc memory for the rom\n");
    }

    //reading rom
    long result = fread(ptr, sizeof(char), (long)nchars, fp);
    if (result != nchars)
    {
        fprintf(stderr, "Something went wrong with the rom,"
                        "did you put your glasses on? ;)\n");
    }
    //freeing file
    fclose(fp);

    rom->ptr = ptr;
    rom->nchars = nchars;
}

void rom_destroy(ROM rom)
{
    free(rom->ptr);
    free(rom);
}