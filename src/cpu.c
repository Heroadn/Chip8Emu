#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "cpu.h"
#include "instructions.h"

typedef struct cpu_type
{
    //architecture
    uint8_t v[15], delay, timer;
    uint16_t stack[16], pc, sp, i;

    Instructions *instructions[16];
};

CPU cpu_create()
{
    CPU cpu = malloc(sizeof(struct cpu_type));

    cpu->instructions[0] = nop;
    cpu->instructions[1] = _1nnn;
    cpu->instructions[2] = _2nnn;
    cpu->instructions[3] = not_implmented;
    cpu->instructions[4] = not_implmented;
    cpu->instructions[5] = not_implmented;
    cpu->instructions[6] = _6xkk;
    cpu->instructions[7] = not_implmented;
    cpu->instructions[8] = not_implmented;
    cpu->instructions[9] = not_implmented;
    cpu->instructions[10] = _annn;
    cpu->instructions[11] = not_implmented;
    cpu->instructions[12] = not_implmented;
    cpu->instructions[13] = _dxyn;
    cpu->instructions[14] = not_implmented;
    cpu->instructions[15] = not_implmented;

    return cpu;
}

Instructions* cpu_get_instruction(CPU cpu,
                          uint16_t instr)
{
    return cpu->instructions[instr >> 12];
}

void cpu_destroy(CPU cpu)
{
    free(cpu);
}

void cpu_inc_pc_byte(CPU cpu)
{
    cpu_set_pc(cpu, cpu_get_pc(cpu) + 1);
}

void cpu_inc_pc_word(CPU cpu)
{
    cpu_set_pc(cpu, cpu_get_pc(cpu) + 2);
}

void cpu_set_pc(CPU cpu,
                uint16_t pc)
{
    cpu->pc = pc;
}

void cpu_set_reg(CPU cpu,
                 uint8_t n,
                 uint8_t value)
{
    cpu->v[n] = value;
}

void cpu_set_reg_I(CPU cpu,
                   uint16_t value)
{
    cpu->i = value;
}

void cpu_set_reg_delay(CPU cpu,
                       uint8_t value)
{
    cpu->delay = value;
}

void cpu_set_reg_timer(CPU cpu,
                       uint8_t value)
{
    cpu->timer = value;
}

uint8_t cpu_get_reg_delay(CPU cpu)
{
    return cpu->delay;
}

uint8_t cpu_get_reg_timer(CPU cpu)
{
    return cpu->timer;
}

uint8_t cpu_get_reg(CPU cpu,
                    uint8_t n)
{
    return cpu->v[n];
}

uint16_t cpu_get_reg_I(CPU cpu)
{
    return cpu->i;
}

uint16_t cpu_get_pc(CPU cpu)
{
    return cpu->pc;
}