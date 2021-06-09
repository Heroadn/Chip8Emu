#include <stdint.h>
#include "cpu.h"
#include "memory.h"
#include "graphics.h"
#include "instructions.h"

typedef struct opcode
{
    uint8_t opcode;
    uint8_t values[3];
    char *menemonic;
};

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

void _00ee(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op)
{
    printf("RET %x\n", cpu_get_sp(cpu));
    cpu_set_pc(cpu, cpu_stack_pop(cpu));
    cpu_stack_print(cpu);
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
    cpu_stack_push(cpu,
                   cpu_get_pc(cpu));

    cpu_set_pc(cpu,
               (op & 0x0FFF));
    cpu_set_pc(cpu,
               cpu_get_pc(cpu) - 2);

    printf("CALL %x\n", cpu_get_pc(cpu) + 2);
}

void _3xkk(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int kk = (op & 0x0FF);

    printf("SKIP Vx == kk, %x == %x\n", cpu_get_reg(cpu, x), kk);
    if (cpu_get_reg(cpu, x) == kk)
    {
        cpu_set_pc(cpu, cpu_get_pc(cpu) + 2);
    }
}

//Skip if Vx != kk - 0x4000
void _4xkk(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int kk = (op & 0x0FF);

    printf("SKIP Vx != kk, %x != %x\n", cpu_get_reg(cpu, x), kk);
    if (cpu_get_reg(cpu, x) != kk)
    {
        cpu_set_pc(cpu, cpu_get_pc(cpu) + 2);
    }
}

//Skip if Vx == Vy - 0x5000
void _5xy0(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int y = (op & 0x0F0) >> 4;

    printf("SKIP V%x, V%x, %x == %x\n", x, y,
           cpu_get_reg(cpu, x), cpu_get_reg(cpu, y));

    if (cpu_get_reg(cpu, x) == cpu_get_reg(cpu, y))
    {
        cpu_set_pc(cpu, cpu_get_pc(cpu) + 2);
    }
}

//ADD - Vx = Vx + kk
void _7xkk(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int kk = (op & 0x0FF);

    printf("ADD V%x = %x + %x\n", x, cpu_get_reg(cpu, x), kk);
    cpu_set_reg(cpu, x, cpu_get_reg(cpu, x) + kk);
}

void _8xy0(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int y = (op & 0x0F0) >> 4;

    printf("LD V%x, V%x, V%x = %x\n", x, y,
           x, cpu_get_reg(cpu, y));
    cpu_ld_reg(cpu, y, x);
}

//OR Vx = Vx OR Vy - 0x8001
void _8xy1(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int y = (op & 0x0F0) >> 4;

    //cpu_set_reg(cpu, x, cpu_get_reg(cpu, y) | cpu_get_reg(cpu, x));
    cpu_or_reg(cpu, y, x);
    printf("OR V%x = %x | %x\n",
           x,
           cpu_get_reg(cpu, x),
           cpu_get_reg(cpu, y));
}

void _9xy0(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int y = (op & 0x0F0) >> 4;

    printf("SKIP V%x, V%x, %x == %x\n", x, y,
           cpu_get_reg(cpu, x), cpu_get_reg(cpu, y));

    if (cpu_get_reg(cpu, x) != cpu_get_reg(cpu, y))
    {
        cpu_set_pc(cpu, cpu_get_pc(cpu) + 2);
    }
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

void _fx0a(CPU cpu,
           Memory mem,
           Gfx gfx,
           uint16_t op)
{
    uint8_t x = cpu_get_reg(cpu,
                            (op & 0xF00) >> 8);

    printf("LD V%x = %x\n", (op & 0xFFF));
}

/*
enum
    {
        CLS,
        LD,
        RET,
        JP,
        CALL,
        SE,
        SNE,
        ADD,
        OR,
        AND,
        XOR,
        ADD,
        SUB,
        SHR,
        SUBN,
        SHL,
        SUBN,
        SHL,
        RND,
        DRW,
        SKP,
        SKNP
    } menemonics;
    */