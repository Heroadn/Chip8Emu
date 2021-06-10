#include <stdio.h>

#ifndef FILE_H
#define FILE_H

//return the amount of chars readed
int read_line(const int n,
              FILE *fp,
              char *str);

int file_read_line(const int n,
                   FILE *fp,
                   char *str);

int file_write_line(FILE *fp,
                    char *str);

//return the amount of chars in the file
long file_nchars(FILE *fp);

//return the file, and check for erros
FILE *file_open(const char *filename,
                const char *mode);

#endif /* FILE_H */