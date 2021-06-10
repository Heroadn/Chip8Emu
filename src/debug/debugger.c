#include <stdio.h>
#include "../utils/file.h"

#define DEBUG_FILE_PATH "debug.txt"
static FILE *fp;

void debug_print_assembly(char *str)
{
    fp = file_open(DEBUG_FILE_PATH,
                         "a+");

    fputs(str, fp);
}

void debug_close()
{
    fclose(fp);
}


