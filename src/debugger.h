#include <stdint.h>
#ifndef DEBUGGER_H
#define DEBUGGER_H

typedef struct debugger_type *Debugger;

typedef enum
{
    ARG_ADDR,
    ARG_REG,
    ARG_DATA,
    ARG_NULL,

    ARG_REG_I,
    ARG_REG_SOUND,
    ARG_REG_TIMER,
    ARG_ADDR_ARR,
    SIZE_ARGS
} Addr_mode;

typedef enum
{
    MNE_SET,
    MNE_CLS,
    MNE_RET,
    MNE_JP,
    MNE_LD,
    MNE_CALL,
    MNE_SE,
    MNE_SNE,
    MNE_OR,
    MNE_AND,
    MNE_XOR,
    MNE_SUB,
    MNE_SUBN,
    MNE_SHR,
    MNE_SHL,
    MNE_RND,
    MNE_DRW,
    MNE_SKP,
    MNE_SKNP,
    MNE_ADD,
    MNE_NOP,
    MNE_NIMP,
    SIZE_MNE
} Menemonic_type;

typedef struct instruction_debug
{
    uint16_t opcode;
    Menemonic_type menemonic;
    struct Operand
    {
        uint16_t args_mask;
        Addr_mode arg_type;//trocar para modo de endereçamento addr_mode, reg_mode
    } operands[2];
} Instruction_info;

Instruction_info teste = {.operands = {.arg_type = ARG_ADDR, .arg_mask = 0}};

Debugger debug_create();

void debug_destroy(Debugger debug);

void debug_print_last(Debugger debug);

void debug_add_instruction(Debugger debug,
                           uint16_t opcode);

#endif DEBUGGER_H /* DEBUGGER_H */
