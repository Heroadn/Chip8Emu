#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include "file.h"

FILE *file_open(const char *filename, const char *mode)
{

    FILE *fp;

    if ((fp = fopen(filename, mode)) == NULL)
    {
        fprintf(stderr, "%s cannot be %s\n",
                filename, (mode[0] == 'r') ? "opened" : "created");
    }

    return fp;
}

int file_write_line(FILE *fp,
                    char *str)
{
    
}

long file_nchars(FILE *fp)
{
    long bytes = 0;

    //number of chars
    fseek(fp, 0L, SEEK_END);
    bytes = ftell(fp);
    rewind(fp);

    return bytes;
}

int file_read_line(const int n, FILE *fp, char *str)
{
    int i = 0;

    for (uint8_t ch = 0; (i < n) && (ch = fgetc(fp)) != EOF;)
    {
        if (0 <= ch && ch <= 128)
            str[i++] = ch;
    }
    str[i] = '\0';
    return i;
}