#include <stdint.h>
#include "cpu.h"
#include "memory.h"
#include "graphics.h"

//0x!000
void not_implmented(CPU cpu,
                    Memory mem,
                    Gfx gfx,
                    uint16_t op);

//0x0000
void nop(CPU cpu,
         Memory mem,
         Gfx gfx,
         uint16_t op);

//0x1000
void _1nnn(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);

//Call - 0x2000
void _2nnn(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);

//Skip if equal
void _3xkk(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);

//Draw - 0xd000
void _dxyn(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);

//LD Vx, byte - 0x6000
void _6xkk(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);

//LD I, addr - 0xa000
void _annn(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);