#include <stdint.h>

#ifndef MEMORY_H
#define MEMORY_H

typedef union memory_type *Memory;

/*
================
 create: 
================
*/
Memory mem_create(void);

/*
================
 destroy: 
================
*/
void mem_destroy(Memory mem);

void mem_view(Memory mem);

void mem_clear(Memory mem);

void mem_move_rom(Memory mem,
                  long size,
                  const uint8_t *rom);

void mem_move_interpreter(Memory mem,
                          long size,
                          const uint8_t *interpreter);

uint8_t mem_load_byte(Memory mem,
                      uint16_t addrs);

uint16_t mem_load_word(Memory mem,
                       uint16_t addrs);

#endif /* MEMORY_H */
