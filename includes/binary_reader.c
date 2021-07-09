#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

#include "binary_reader.h"
#include "file.h"

static void print_line(const uint8_t str[], int n, int i_bytes, int bytes_per_line)
{
    int i = 0, group = 1, c = 0;
    
    //print offset
    printf("%6d  ", i_bytes);

    //print bytes
    for (i = 0; i < bytes_per_line; i++)
    {
        if((i % group) == 0)
            printf(" ");

        printf("%.2X", (unsigned int)(unsigned char)str[i]);
    }

    //chars
    printf("     ");
    for (i = 0, c = 0; i < bytes_per_line; i++)
    {  
        c = (isprint(str[i]) && isspace(str[i]) == 0 && i < n)? str[i] : '.';
        printf("%c", c);
    }
    printf("\n");
}

int print_file(const char *filename)
{
    FILE *fp = file_open(filename, "rb");

    int bytes_line = 16, i_bytes = 0, n = 0;
    uint8_t str[bytes_line + 1]; 

    printf("Offset  %30s  %33s\n", "Bytes", "Characters");
    printf("------  -----------------------------------------------------  ----------\n");

    while(n = file_read_line(bytes_line, fp, str))
    {
        print_line(str, n, i_bytes, bytes_line);
        i_bytes += n;
    }

    fclose(fp);


    return 0;
}