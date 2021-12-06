#include <stdint.h>

#ifndef DEBUGGER_H
#define DEBUGGER_H
#include "memory.h"
#include "register.h"

typedef struct debugger_type *Debugger;

typedef enum
{
    ADDR_NULL,//no values
    ADDR_ABS, //literal/immediate
    ADDR_REG, //to or from register
    
    //Specific
    ADDR_REG_I,
    ADDR_REG_I_ARR,
    ADDR_REG_SOUND,
    ADDR_REG_TIMER,
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

typedef struct instruction_log_type
{
    uint16_t opcode;
    Menemonic_type menemonic;
    struct Operand
    {
        uint16_t mask;
        Addr_mode addr;//trocar para modo de endereçamento addr_mode, reg_mode
    } operands[3];
} Instruction_log;

Debugger debug_create(Register reg,
                      Memory mem);

void debug_destroy(Debugger debug);

void debug_print(Debugger debug);

void debug_add_instruction(Debugger debug,
                           uint16_t opcode);

void debug_print_state(Register reg);

#endif DEBUGGER_H /* DEBUGGER_H */
