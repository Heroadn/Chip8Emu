#include <stdint.h>
#include <stdbool.h>

#ifndef REG_H
#define REG_H

typedef struct register_type *Register;

typedef enum
{
    FLAG_COLLISION,
    FLAG_NOTBORROW,
    FLAG_OVERFLOW,
    FLAG_MSB_ON,
    FLAG_LSB_ON,
    SIZE_FLAGS
} Flag;

typedef enum
{
    REG_BYTE_V0,
    REG_BYTE_V1,
    REG_BYTE_V2,
    REG_BYTE_V3,
    REG_BYTE_V4,
    REG_BYTE_V5,
    REG_BYTE_V6,
    REG_BYTE_V7,
    REG_BYTE_V8,
    REG_BYTE_V9,
    REG_BYTE_VA,
    REG_BYTE_VB,
    REG_BYTE_VC,
    REG_BYTE_VD,
    REG_BYTE_VE,
    REG_BYTE_VF,
    REG_BYTE_SOUND,
    REG_BYTE_DELAY,
    REG_BYTE_STACK,
    SIZE_REG_BYTE
} Register_byte;

typedef enum
{
    REG_WORD_PC,
    REG_WORD_I,
    SIZE_REG_WORD
} Register_word;

Register reg_create();

void reg_destroy(Register cpu);

void reg_inc_pc_byte(Register cpu);

void reg_inc_pc(Register cpu);

void reg_stack_print(Register cpu);

void reg_clear_flags(Register cpu);

void reg_load(Register cpu,
              uint8_t reg_src,
              uint8_t reg_dst);

void reg_or_reg(Register cpu,
                uint8_t reg_src,
                uint8_t reg_dst);

void reg_and_reg(Register cpu,
                 uint8_t reg_src,
                 uint8_t reg_dst);

void reg_xor_reg(Register cpu,
                 uint8_t reg_src,
                 uint8_t reg_dst);

void reg_add_reg(Register cpu,
                 uint8_t reg_src,
                 uint8_t reg_dst);

void reg_sub_reg(Register cpu,
                 uint8_t reg_src,
                 uint8_t reg_dst);

void reg_subn_reg(Register cpu,
                  uint8_t reg_src,
                  uint8_t reg_dst);

void reg_shr(Register cpu,
             uint8_t reg_src,
             uint8_t reg_dst);

void reg_shl(Register cpu,
             uint8_t reg_src,
             uint8_t reg_dst);

void reg_set_pc(Register cpu,
                uint16_t pc);

void reg_set_byte(Register cpu,
                  Register_byte reg,
                  const uint8_t value);

void reg_set_word(Register cpu,
                  Register_word reg,
                  const uint16_t value);

void reg_stack_push(Register cpu,
                    uint16_t value);

void reg_set_pc(Register cpu,
                const uint16_t value);

void reg_set_flag(Register cpu,
                  Flag flag,
                  bool value);

uint8_t reg_get_byte(Register cpu,
                     Register_byte reg);

uint16_t reg_stack_pop(Register cpu);

uint16_t reg_get_pc(Register cpu);

uint16_t reg_get_word(Register cpu,
                     Register_byte reg);

bool reg_get_flag(Register cpu,
                  Flag flag);

#endif /* REG_H */
