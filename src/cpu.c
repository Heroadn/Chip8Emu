#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "cpu.h"
#include "instructions.h"

typedef struct cpu_type
{
    //architecture
    uint8_t v[15], delay, timer;
    uint16_t stack[16], pc, sp, i;;
};

CPU cpu_create()
{
    CPU cpu = malloc(sizeof(struct cpu_type));
    cpu->sp = 0;
    return cpu;
}

Instruction *const cpu_get_instruction(CPU cpu,
                                        uint16_t op)
{
    switch (op & 0xF000)
    {
    case 0x1000:
        return _1nnn;
        break;
    case 0x2000:
        return _2nnn;
        break;
    case 0x3000:
        return _3xkk;
        break;
    case 0x4000:
        return _4xkk;
        break;
    case 0x5000:
        return _5xy0;
        break;
    case 0x6000:
        return _6xkk;
        break;
    case 0x7000:
        return _7xkk;
        break;
    case 0x9000:
        return _9xy0;
        break;
    case 0xD000:
        return _dxyn;
        break;
    case 0xA000:
        return _annn;
        break;
    default:

        switch (op & 0xF0FF)
        {
        case 0x0000:
            return nop;
            break;
        case 0x00E0:
            return not_implmented;
            break;
        case 0x00EE:
            return _00ee;
            break;
        }

        switch (op & 0xF00F)
        {
        case 0x8000:
            return _8xy0;
            break;
        case 0x8001:
            return _8xy1;
            break;
        case 0x8002:
            return not_implmented;
            break;
        case 0x8003:
            return not_implmented;
            break;
        case 0x8004:
            return not_implmented;
            break;
        case 0x8005:
            return not_implmented;
            break;
        case 0x8006:
            return not_implmented;
            break;
        case 0x8007:
            return not_implmented;
            break;
        case 0x800E:
            return not_implmented;
            break;
        }

        switch (op & 0xF0FF)
        {
        case 0xF007:
            return not_implmented;
            break;
        case 0xF00A:
            return not_implmented;
            break;
        case 0xF015:
            return not_implmented;
            break;
        case 0xF018:
            return not_implmented;
            break;
        case 0xF01E:
            return not_implmented;
            break;
        case 0xF029:
            return not_implmented;
            break;
        case 0xF033:
            return not_implmented;
            break;
        case 0xF055:
            return not_implmented;
            break;
        case 0xF065:
            return not_implmented;
            break;
        }

        return not_implmented;
    }
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

void cpu_or_reg(CPU cpu,
                uint8_t src,
                uint8_t dst)
{
    cpu_set_reg(cpu, dst, cpu_get_reg(cpu, src) | cpu_get_reg(cpu, dst));
}

void cpu_ld_reg(CPU cpu,
                uint8_t src,
                uint8_t dst
                )
{
    cpu_set_reg(cpu, dst, cpu_get_reg(cpu, src));
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

uint16_t cpu_get_sp(CPU cpu)
{
    return cpu->sp;
}

uint16_t cpu_stack_pop(CPU cpu)
{
    return cpu->stack[--cpu->sp];
}

void cpu_stack_push(CPU cpu,
                    uint16_t value)
{
    cpu->stack[cpu->sp++] = value;
}

void cpu_stack_print(CPU cpu)
{
    for (int i = 0; i < 16; i++)
    {
        printf("    %2d: %x\n", i, cpu->stack[i]);
    }
}
