#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"

#define RAM_SIZE 4095
#define INTERPRETER_SIZE 512
#define DATA_SIZE 3582

typedef union memory_type
{
    struct
    {
        uint8_t interpreter[INTERPRETER_SIZE];
        uint8_t data[DATA_SIZE];
    } segment;

    uint8_t RAM[RAM_SIZE];
};

Memory mem_create(void)
{
    Memory mem = calloc(1, sizeof(union memory_type));
    mem_clear(mem);
    return mem;
}

void mem_view(Memory mem)
{
    for (int i = 0; i < 4095; i++)
    {
        if ((i % 10) == 0)
            printf("\n");

        printf("%4x: %2X ", i, mem->RAM[i]);
    }
    printf("\n");
}

void mem_clear(Memory mem)
{
    for (int i = 0; i < 4095; i++)
        mem->RAM[i];
}

void mem_load(Memory mem,
              const long n,
              const long addrs,
              const uint8_t *data)
{
    memcpy((mem->RAM + addrs),
           data,
           n);
}

void mem_destroy(Memory mem)
{
    free(mem);
}

void mem_store_byte(Memory mem,
                    uint16_t addrs,
                    uint8_t value)
{
    mem->RAM[addrs % RAM_SIZE] = value;
}

uint8_t mem_load_segment(Memory mem,
                         uint8_t n,
                         uint8_t index,
                         uint16_t start_addr)
{
    start_addr += (n * index);
    return (start_addr % RAM_SIZE);
}

uint8_t mem_load_byte(Memory mem,
                      uint16_t addrs)
{
    return mem->RAM[addrs % RAM_SIZE];
}

uint16_t mem_load_word(Memory mem,
                       uint16_t addrs)
{
    return (mem_load_byte(mem, addrs) << 8 | mem_load_byte(mem, addrs + 1));
}