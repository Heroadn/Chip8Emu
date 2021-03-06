#include <stdint.h>

#ifndef MEMORY_H
#define MEMORY_H

typedef union memory_type *Memory;

/*
================
 mem_create: 
================
*/
Memory mem_create(void);

/*
================
 mem_destroy: 
================
*/
void mem_destroy(Memory mem);

/*
================
 mem_view: 
================
*/
void mem_view(Memory mem);

/*
================
 mem_clear: 
================
*/
void mem_clear(Memory mem);

/*
================
 mem_laod: load n bytes of data into mem at addrs
================
*/
void mem_load(Memory mem,
              const long n,
              const long addrs,
              const uint8_t *data);

void mem_store_byte(Memory mem,
                    uint16_t addrs,
                    uint8_t value);

uint8_t mem_load_segment(Memory mem,
                         uint8_t n,
                         uint8_t index,
                         uint16_t start_addr);

//rename to move
uint8_t mem_load_byte(Memory mem,
                      uint16_t addrs);

uint16_t mem_load_word(Memory mem,
                       uint16_t addrs);

#endif /* MEMORY_H */
