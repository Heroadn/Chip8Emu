#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "register.h"
#define SIZE_STACK 16

#define REGISTER_STACK REG_BYTE_STACK
#define REGISTER_PC REG_WORD_PC

typedef struct register_type
{
    //architecture
    uint8_t regs_byte[SIZE_REG_BYTE];
    uint16_t regs_word[SIZE_REG_WORD], stack[SIZE_STACK];
};

Register reg_create()
{
    Register reg = calloc(1,
                     sizeof(struct register_type));
    return reg;
}

void reg_destroy(Register cpu)
{
    free(cpu);
}

void reg_inc_pc_byte(Register cpu)
{
    reg_set_pc(cpu,
               reg_get_pc(cpu) + 1);
}

void reg_inc_pc(Register cpu)
{
    reg_set_pc(cpu,
               reg_get_pc(cpu) + 2);
}

void reg_xor_reg(Register cpu,
                 uint8_t reg_src,
                 uint8_t reg_dst)
{
    reg_set_byte(cpu, reg_dst,
                 reg_get_byte(cpu, reg_src) ^ reg_get_byte(cpu, reg_dst));
}

void reg_and_reg(Register cpu,
                 uint8_t reg_src,
                 uint8_t reg_dst)
{
    reg_set_byte(cpu,
                 reg_dst,
                 reg_get_byte(cpu, reg_src) & reg_get_byte(cpu, reg_dst));
}

void reg_or_reg(Register cpu,
                uint8_t reg_src,
                uint8_t reg_dst)
{
    reg_set_byte(cpu,
                 reg_dst,
                 reg_get_byte(cpu, reg_src) | reg_get_byte(cpu, reg_dst));
}

void reg_add_reg(Register cpu,
                 uint8_t reg_src,
                 uint8_t reg_dst)
{
    uint8_t x, y;
    uint16_t result;

    x = reg_get_byte(cpu,
                     reg_src);

    y = reg_get_byte(cpu,
                     reg_dst);

    result = x + y;
    reg_set_byte(cpu,
                 0xF,
                 (result > 255) ? 1 : 0);

    reg_set_byte(cpu,
                 reg_dst,
                 result);
}

void reg_sub_reg(Register cpu,
                 uint8_t reg_src,
                 uint8_t reg_dst)
{
    uint8_t x, y;
    uint8_t result;

    x = reg_get_byte(cpu,
                     reg_src);

    y = reg_get_byte(cpu,
                     reg_dst);

    result = y - x;

    //setting value of reg_dst
    reg_set_byte(cpu,
                 reg_dst,
                 result);
}

void reg_subn_reg(Register cpu,
                  uint8_t reg_src,
                  uint8_t reg_dst)
{
    uint8_t x, y;
    uint8_t result;

    x = reg_get_byte(cpu,
                     reg_src);

    y = reg_get_byte(cpu,
                     reg_dst);

    result = x - y;

    //setting value of reg_dst
    reg_set_byte(cpu,
                 reg_dst,
                 result);
}

void reg_shr(Register cpu,
             uint8_t reg_src,
             uint8_t reg_dst)
{
    reg_set_byte(cpu,
                 reg_dst,
                 reg_get_byte(cpu, reg_src) >> 1);
}

void reg_shl(Register cpu,
             uint8_t reg_src,
             uint8_t reg_dst)
{
    reg_set_byte(cpu,
                 reg_dst,
                 reg_get_byte(cpu, reg_src) << 1);
}

void reg_load(Register cpu,
              uint8_t src,
              uint8_t dst)
{
    reg_set_byte(cpu, dst, reg_get_byte(cpu, src));
}

void reg_set_flag(Register cpu,
                  Flag flag,
                  bool value)
{
    reg_set_byte(cpu,
                 REG_BYTE_V15,
                 value);
}

void reg_set_byte(Register cpu,
                  Register_byte reg,
                  const uint8_t value)
{
    cpu->regs_byte[reg] = value;
}

void reg_set_word(Register cpu,
                  Register_word reg,
                  const uint16_t value)
{
    return cpu->regs_word[reg] = value;
}

void reg_stack_push(Register cpu,
                    uint16_t value)
{
    cpu->stack[cpu->regs_byte[REGISTER_STACK]++] = value;
}

void reg_set_pc(Register cpu,
                const uint16_t value)
{
    reg_set_word(cpu,
                 REG_WORD_PC,
                 value);
}

void reg_stack_print(Register cpu)
{
    for (int i = 0; i < 16; i++)
        printf("    %2d: %x\n", i, cpu->stack[i]);
}

void reg_clear_flags(Register cpu)
{
    reg_set_flag(cpu,
                 FLAG_COLLISION,
                 false);
    reg_set_flag(cpu,
                 FLAG_NOTBORROW,
                 false);
    reg_set_flag(cpu,
                 FLAG_OVERFLOW,
                 false);
}

uint8_t reg_get_byte(Register cpu,
                     Register_byte reg)
{
    return cpu->regs_byte[reg];
}

uint16_t reg_get_word(Register cpu,
                      Register_byte reg)
{
    return cpu->regs_word[reg];
}

uint16_t reg_stack_pop(Register cpu)
{
    return cpu->stack[--cpu->regs_byte[REGISTER_STACK]];
}

uint16_t reg_get_pc(Register cpu)
{
    return reg_get_word(cpu,
                        REGISTER_PC);
}

bool reg_get_flag(Register cpu,
                  Flag flag)
{
    return reg_get_byte(cpu,
                        REG_BYTE_V15);
}