#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#include "register.h"
#include "instructions.h"
#include "memory.h"
#include "rom.h"
#include "graphics.h"
#include "keyboard.h"

#ifndef CPU_H
#define CPU_H

/*
================
 cpu_cycle: calls fetch, 
 decode and execute the instruction 
================
*/
uint16_t cpu_cycle(Register cpu,
                   Memory mem,
                   Gfx gfx,
                   Keyboard key);

/*
================
 cpu_execute: execute the instruction 
================
*/
void cpu_execute(Register cpu,
                 Memory mem,
                 Gfx gfx,
                 Instruction_ptr instruction,
                 uint16_t op,
                 Keyboard key);

/*
================
 cpu_fetch: fetch the instruction from mem 
================
*/
uint16_t cpu_fetch(Register cpu,
                   Memory mem);

/*
================
 cpu_decode: decode op in a instruction 
================
*/
Instruction_ptr cpu_decode(Register cpu,
                           uint16_t op);

#endif /* CPU_H */
