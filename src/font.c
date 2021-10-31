#include <stdlib.h>
#include <stdio.h>
#include "font.h"

Font font_create(const uint8_t *data,
                 const int size)
{
    Font font = malloc(sizeof(struct font_type));
    font->ptr = data;
    font->size = size;
    return font;
}

void font_destroy(Font font)
{
    free(font);
}