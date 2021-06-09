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

//0x00ee
void _00ee(CPU cpu,
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

//Skip if equal - 0x3000
void _3xkk(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);

//Skip if Vx != kk - 0x4000
void _4xkk(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);

//Skip if Vx == Vy - 0x5000
void _5xy0(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);

//LD Vx, byte - 0x6000
void _6xkk(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);

//ADD - Vx = Vx + kk
void _7xkk(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);

//LD Vx = Vy - 0x8000
void _8xy0(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);

//OR Vx = Vx OR Vy - 0x8001
void _8xy1(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);

//SKIP - if Vx != Vy - 0x9000
void _9xy0(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);

//Draw - 0xd000
void _dxyn(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);

//LD I, addr - 0xa000
void _annn(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);

//0xf00a
void _fx0a(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op);
