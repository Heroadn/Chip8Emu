#include <stdint.h>

#ifndef FONT_H
#define FONT_H

typedef struct font_type
{
    int size;     //number of chars
    uint8_t *ptr; //pointer to font
} * Font;

Font font_create(const uint8_t *data,
                 const int size);

void font_destroy(Font font);

#endif /* FONT_H */