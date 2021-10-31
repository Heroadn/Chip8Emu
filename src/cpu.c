#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include "cpu.h"

const Instruction_ptr op_8[] =
    {
        [0x0] = ins_8xy0,
        [0x1] = ins_8xy1,
        [0x2] = ins_8xy2,
        [0x3] = ins_8xy3,
        [0x4] = ins_8xy4,
        [0x5] = ins_8xy5,
        [0x6] = ins_8xy6,
        [0x7] = ins_8xy7,
        [0xE] = ins_8xye};

const Instruction_ptr op_f[] =
    {
        [0x7] = ins_fx07,
        [0xa] = ins_fx0a,
        [0x15] = ins_fx15,
        [0x18] = ins_fx18,
        [0x1e] = ins_fx1e,
        [0x29] = ins_fx29,
        [0x33] = ins_fx33,
        [0x55] = ins_fx55,
        [0x65] = ins_fx65};

const Instruction_ptr op_e[] =
    {
        [0x1] = ins_exa1,
        [0xe] = ins_ex9e};

const Instruction_ptr op_0[] =
    {
        [0x0] = ins_00e0,
        [0xe] = ins_00ee};

Instruction instructions_group[] =
    {
        [0x0] = {.group = op_0, .mask = 0x000F},
        [0x1] = {.group = (Instruction_ptr[]){ins_1nnn}, .mask = 0x0000},
        [0x2] = {.group = (Instruction_ptr[]){ins_2nnn}, .mask = 0x0000},
        [0x3] = {.group = (Instruction_ptr[]){ins_3xkk}, .mask = 0x0000},
        [0x4] = {.group = (Instruction_ptr[]){ins_4xkk}, .mask = 0x0000},
        [0x5] = {.group = (Instruction_ptr[]){ins_5xy0}, .mask = 0x0000},
        [0x6] = {.group = (Instruction_ptr[]){ins_6xkk}, .mask = 0x0000},
        [0x7] = {.group = (Instruction_ptr[]){ins_7xkk}, .mask = 0x0000},
        [0x8] = {.group = op_8, .mask = 0x000F},
        [0x9] = {.group = (Instruction_ptr[]){ins_9xy0}, .mask = 0x0000},
        [0xa] = {.group = (Instruction_ptr[]){ins_annn}, .mask = 0x0000},
        [0xc] = {.group = (Instruction_ptr[]){ins_cxkk}, .mask = 0x0000},
        [0xd] = {.group = (Instruction_ptr[]){ins_dxyn}, .mask = 0x0000},
        [0xe] = {.group = op_e, .mask = 0x000F},
        [0xf] = {.group = op_f, .mask = 0x00FF}};

Instruction_ptr cpu_decode(Register reg,
                           uint16_t op)
{
    printf("PC: %4x, OP: %4x          ", reg_get_pc(reg), op);
    Instruction m = instructions_group[(op & 0xF000) >> 12];
    return m.group[op & m.mask];
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

uint16_t cpu_fetch(Register reg,
                   Memory mem)
{
    return mem_load_word(mem,
                         reg_get_pc(reg));
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