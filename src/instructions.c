#include <stdint.h>
#include "cpu.h"
#include "memory.h"
#include "graphics.h"
#include "instructions.h"

void not_implmented(CPU cpu,
                    Memory mem,
                    Gfx gfx,
                    uint16_t op)
{
    printf("OP %x NOT IMPLEMENTED\n", op);
}

void nop(CPU cpu,
         Memory mem,
         Gfx gfx,
         uint16_t op)
{
    printf("NOP\n");
}

void _1nnn(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op)
{
    cpu_set_pc(cpu,
               (op & 0x0FFF));
    cpu_set_pc(cpu,
               cpu_get_pc(cpu) - 2);

    printf("JUMP %x\n", cpu_get_pc(cpu) + 2);
}

void _2nnn(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op)
{
    //salvar na stack endereço do pc atual
    cpu_set_pc(cpu,
               (op & 0x0FFF));
    cpu_set_pc(cpu,
               cpu_get_pc(cpu) - 2);

    printf("CALL %x\n", cpu_get_pc(cpu) + 2);
}

void _dxyn(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op)
{
    uint8_t bytes, x, y, sprite[8] = {0};
    bytes = (op & 0x00F);

    x = cpu_get_reg(cpu,
                    (op & 0xF00) >> 8);
    y = cpu_get_reg(cpu,
                    (op & 0x0F0) >> 4);
    printf("Dxyn x=%x y=%x bytes=%x \n", x, y, bytes);

    for (int i = 0, pixel = 0; i < bytes; i++)
    {
        pixel = mem_load_byte(mem,
                              (cpu_get_reg_I(cpu) + i));
        printf("    %x\n", pixel);
        sprite[i] = pixel;
    }

    gfx_draw_sprite(x,
                    y,
                    PIXEL_SIZE,
                    bytes,
                    sprite,
                    gfx);

    gfx_draw_screen(gfx);
}

void _6xkk(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op)
{
    cpu_set_reg(cpu,
                (op & 0x0F00) >> 8,
                (op & 0xFF));
    printf("LD V%d = %x\n", (op & 0x0F00) >> 8, (op & 0xFF));
}

void _annn(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op)
{
    cpu_set_reg_I(cpu,
                  (op & 0xFFF));
    printf("LD Vi = %x\n", (op & 0xFFF));
}