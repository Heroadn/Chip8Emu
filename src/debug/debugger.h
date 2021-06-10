#include <stdint.h>
#include <stdio.h>

typedef struct opcode
{
    uint8_t opcode;
    uint8_t values[3];
    char *menemonic;
};

void debug_print_assembly(char *str);

void debug_close();