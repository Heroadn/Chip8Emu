#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include "cpu.h"

typedef struct cpu_type
{

} CPU;

CPU cpu;

Instruction_ptr cpu_decode(Register reg,
                           uint16_t op)
{
    printf("PC: %4x, OP: %x ", reg_get_pc(reg), op);

    switch (op & 0xF000)
    {
    case 0x1000:
        return ins_1nnn;
    case 0x2000:
        return ins_2nnn;
    case 0x3000:
        return ins_3xkk;
    case 0x4000:
        return ins_4xkk;
    case 0x5000:
        return ins_5xy0;
    case 0x6000:
        return ins_6xkk;
    case 0x7000:
        return ins_7xkk;
    case 0x9000:
        return ins_9xy0;
    case 0xC000:
        return ins_cxkk;
    case 0xD000:
        return ins_dxyn;
    case 0xA000:
        return ins_annn;
    default:
        switch (op & 0xF0FF)
        {
        case 0x0000:
            return ins_nop;
        case 0x00E0:
            return ins_00e0;
        case 0x00EE:
            return ins_00ee;
        case 0xE09E:
            return ins_ex9e;
        case 0xE0A1:
            return ins_exa1;
        }

        switch (op & 0xF00F)
        {
        case 0x8000:
            return ins_8xy0;
        case 0x8001:
            return ins_8xy1;
        case 0x8002:
            return ins_8xy2;
        case 0x8003:
            return ins_8xy3;
        case 0x8004:
            return ins_8xy4;
        case 0x8005:
            return ins_8xy5;
        case 0x8006:
            return ins_8xy6;
        case 0x8007:
            return ins_8xy7;
        case 0x800E:
            return ins_8xye;
        }

        switch (op & 0xF0FF)
        {
        case 0xF007:
            return ins_fx07;
        case 0xF00A:
            return ins_fx0a;
        case 0xF015:
            return ins_fx15;
        case 0xF018:
            return ins_fx18;
        case 0xF01E:
            return ins_fx1e;
        case 0xF029:
            return ins_fx29;
        case 0xF033:
            return ins_fx33;
        case 0xF055:
            return ins_fx55;
        case 0xF065:
            return ins_fx65;
        }

        return ins_not_implmented;
    }
}

void cpu_execute(Register reg,
                 Memory mem,
                 Gfx gfx,
                 Instruction_ptr ins,
                 uint16_t op,
                 Keyboard key)
{
    ins(reg,
        mem,
        gfx,
        key,
        op);

    reg_inc_pc(reg);
}

uint16_t cpu_fetch(Register cpu,
                   Memory mem)
{
    return mem_load_word(mem,
                         reg_get_pc(cpu));
}

uint16_t cpu_cycle(Register reg,
                   Memory mem,
                   Gfx gfx,
                   Keyboard key)
{
    static Instruction_ptr ins;
    static uint16_t op;

    op = cpu_fetch(reg,
                   mem);

    ins = cpu_decode(reg,
                     op);

    cpu_execute(reg,
                mem,
                gfx,
                ins,
                op,
                key);

    return op;
}