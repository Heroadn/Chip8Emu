#include <stdio.h>
#include "debugger.h"
#include "instructions.h"
#define INSTRUCTIONS_SIZE 4095

typedef struct debugger_type
{
    Instruction_info history[INSTRUCTIONS_SIZE];
    int index;
};

typedef enum
{
    ID_00E0,
    ID_00EE,
    ID_1nnn,
    ID_2nnn,
    ID_3xkk,
    ID_4xkk,
    ID_5xy0,
    ID_6xkk,
    ID_7xkk,
    ID_8xy0,
    ID_8xy1,
    ID_8xy2,
    ID_8xy3,
    ID_8xy4,
    ID_8xy5,
    ID_8xy6,
    ID_8xy7,
    ID_8xyE,
    ID_9xy0,
    ID_Annn,
    ID_Bnnn,
    ID_Cxkk,
    ID_Dxyn,
    ID_Ex9E,
    ID_ExA1,
    ID_Fx07,
    ID_Fx0A,
    ID_Fx15,
    ID_Fx18,
    ID_Fx1E,
    ID_Fx29,
    ID_Fx33,
    ID_Fx55,
    ID_Fx65,
    ID_NOP,
    ID_NIMP
} ID_instruction;

Instruction_info instruction_info[] = {
    [ID_00E0] = {//[0] 0x00E0
                 .menemonic = MNE_CLS,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = {ARG_NULL, ARG_NULL},
                 },
    [ID_00EE] = {//[1] 0x00EE
                 .menemonic = MNE_RET,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = {ARG_NULL, ARG_NULL}},
    [ID_1nnn] = {//[2] 0x1nnn
                 .menemonic = MNE_JP,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = {ARG_ADDR, ARG_NULL}},
    [ID_2nnn] = {//[3] 0x2nnn
                 .menemonic = MNE_CALL,
                 .operands.args_mask = {0, 0xFFF},
                 .operands.arg_type = {ARG_NULL, ARG_ADDR}},
    [ID_3xkk] = {//[4] 0x3xkk
                 .menemonic = MNE_SE,
                 .operands.args_mask = {0x0F00, 0x00FF},
                 .operands.arg_type = {ARG_REG, ARG_ADDR}},
    [ID_4xkk] = {//[5] 0x4xkk
                 .menemonic = MNE_SNE,
                 .operands.args_mask = {0x0F00, 0x00FF},
                 .operands.arg_type = {ARG_REG, ARG_ADDR}},
    [ID_5xy0] = {//[6] 0x5xy0
                 .menemonic = MNE_SE,
                 .operands.args_mask = {0xF00, 0x00F0},
                 .operands.arg_type = {ARG_REG, ARG_REG}},
    [ID_6xkk] = {//[7] 0x6xkk
                 .menemonic = MNE_LD,
                 .operands.args_mask = {0x0F00, 0x00FF},
                 .operands.arg_type = {ARG_REG, ARG_ADDR}},
    [ID_7xkk] = {//[8] 0x7xkk
                 .menemonic = MNE_ADD,
                 .operands.args_mask = {0x0F00, 0x00FF},
                 .operands.arg_type = {ARG_REG, ARG_ADDR}},
    [ID_8xy0] = {//[9] 0x8xy0
                 .menemonic = MNE_LD,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_REG},
    [ID_8xy0] = {//[10] 0x8xy1
                 .menemonic = MNE_OR,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_REG},
    [ID_8xy1] = {//[11] 0x8xy2
                 .menemonic = MNE_AND,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_REG},
    [ID_8xy2] = {//[12] 0x8xy3
                 .menemonic = MNE_XOR,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_REG},
    [ID_8xy3] = {//[13] 0x8xy4
                 .menemonic = MNE_ADD,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_REG},
    [ID_8xy4] = {//[14] 0x8xy5
                 .menemonic = MNE_SUB,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_REG},
    [ID_8xy5] = {//[15] 0x8xy6
                 .menemonic = MNE_SHR,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_REG},
    [ID_8xy6] = {//[16] 0x8xy7
                 .menemonic = MNE_SUBN,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_REG},
    [ID_8xy7] = {//[17] 0x8xyE
                 .menemonic = MNE_SHL,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_REG},
    [ID_9xy0] = {//[18] 0x9xy0
                 .menemonic = MNE_SNE,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_REG},
    [ID_Annn] = {//[19] 0xAnnn
                 .menemonic = MNE_LD,
                 .operands.args_mask = {0, 0x0FFF},
                 .operands.arg_type = {ARG_REG_I, ARG_ADDR}},
    [ID_Bnnn] = {//[20] 0xBnnn
                 .menemonic = MNE_JP,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_ADDR},
    [ID_Cxkk] = {//[21] 0xCxkk
                 .menemonic = MNE_RND,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_ADDR},
    [ID_Dxyn] = {//[22] 0xDxyn
                 .menemonic = MNE_DRW,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_REG},
    [ID_Ex9E] = {//[23] 0xEx9E
                 .menemonic = MNE_SKP,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_NULL},
    [ID_ExA1] = {//[24] 0xExA1
                 .menemonic = MNE_SKNP,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_NULL},
    [ID_Fx07] = {//[25] 0xFx07
                 .menemonic = MNE_LD,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_ADDR},
    [ID_Fx0A] = {//[26] 0xFx0A
                 .menemonic = MNE_LD,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_DATA},
    [ID_Fx15] = {//[27] 0xFx15
                 .menemonic = MNE_LD,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_REG},
    [ID_Fx18] = {//[28] 0xFx18
                 .menemonic = MNE_LD,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_REG},
    [ID_Fx1E] = {//[29] 0xFx1E
                 .menemonic = MNE_ADD,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_REG,
                 .operands.arg_type = ARG_REG},
    [ID_Fx29] = {//[30] 0xFx29
                 .menemonic = MNE_LD,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_ADDR,
                 .operands.arg_type = ARG_REG},
    [ID_Fx33] = {//[31] 0xFx33
                 .menemonic = MNE_LD,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_ADDR,
                 .operands.arg_type = ARG_REG},
    [ID_Fx55] = {//[32] 0xFx55
                 .menemonic = MNE_LD,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_ADDR,
                 .operands.arg_type = ARG_REG},
    [ID_Fx65] = {//[33] 0xFx65
                 .menemonic = MNE_LD,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_ADDR,
                 .operands.arg_type = ARG_REG},
    [ID_NOP] = {//[34] Do nothing
                .menemonic = MNE_NOP,
                .operands.args_mask = {0, 0},
                .operands.arg_type = ARG_NULL,
                .operands.arg_type = ARG_NULL},
    [ID_NIMP] = {//[35] Not implemented
                 .menemonic = MNE_NIMP,
                 .operands.args_mask = {0, 0},
                 .operands.arg_type = ARG_NULL,
                 .operands.arg_type = ARG_NULL}};

static uint16_t remove_nimble_zeros(uint16_t operands)
{
    while ((operands & 0xF) == 0 && (operands != 0))
        operands >>= 4;

    return operands;
};

//print the instruction
static void print_intruction(Instruction_info info)
{
    //Enum of menemonics to str
    static const char *menemonics[] =
        {
            "SET", "CLS",
            "RET", "JP",
            "LD", "CALL",
            "SE", "SNE",
            "OR", "AND",
            "XOR", "SUB",
            "SUBN", "SHR",
            "SHL", "RND",
            "DRW", "SKP",
            "SKP", "SKNP",
            "ADD", "NOP",
            "NIMP"};

    //
    static const char *arg_name[] =
        {
            [ARG_REG] = "V",
            [ARG_ADDR] = "",
            [ARG_NULL] = "",
            [ARG_DATA] = "",
            [ARG_REG_I] = "Vi"};

    //Type of operation done by the instruction
    static const char *type_op[] =
        {
            [MNE_CLS] = "",
            [MNE_LD] = "=",
            [MNE_AND] = "&",
            [MNE_OR] = "|",
            [MNE_CALL] = "<-",
            [MNE_RET] = "->",
            [MNE_SNE] = "!=",
            [MNE_SE] = "=="};

    //menemonic
    printf("%s ", menemonics[info.menemonic]);
        
    //Reg or Addres
    printf("%s", arg_name[info.operands[0].arg_type]);

    //If index of general register
    if (info.operands[0].arg_type == ARG_REG)
        printf("%x", remove_nimble_zeros(info.opcode & info.operands[0].args_mask));

    //Symbol of operation done
    printf(" %s ", type_op[info.menemonic]);

    //Second operands
    if (info.operands[1].arg_type != ARG_NULL)
        printf("%x", (info.opcode & info.operands[1].args_mask));
    printf("\n");
}

//return instruction id
static uint16_t dissasembler(uint16_t op)
{
    switch (op & 0xF000)
    {
    case 0x1000:
        return ID_1nnn;
    case 0x2000:
        return ID_2nnn;
    case 0x3000:
        return ID_3xkk;
    case 0x4000:
        return ID_4xkk;
    case 0x5000:
        return ID_5xy0;
    case 0x6000:
        return ID_6xkk;
    case 0x7000:
        return ID_7xkk;
    case 0x9000:
        return ID_9xy0;
    case 0xC000:
        return ID_Cxkk;
    case 0xD000:
        return ID_Dxyn;
    case 0xA000:
        return ID_Annn;
    default:
        switch (op & 0xF0FF)
        {
        case 0x0000:
            return ID_NOP;
        case 0x00E0:
            return ID_00E0;
        case 0x00EE:
            return ID_00E0;
        case 0xE09E:
            return ID_Ex9E;
        case 0xE0A1:
            return ID_ExA1;
        }

        switch (op & 0xF00F)
        {
        case 0x8000:
            return ID_8xy0;
        case 0x8001:
            return ID_8xy1;
        case 0x8002:
            return ID_8xy2;
        case 0x8003:
            return ID_8xy3;
        case 0x8004:
            return ID_8xy4;
        case 0x8005:
            return ID_8xy5;
        case 0x8006:
            return ID_8xy6;
        case 0x8007:
            return ID_8xy7;
        case 0x800E:
            return ID_8xyE;
        }

        switch (op & 0xF0FF)
        {
        case 0xF007:
            return ID_Fx07;
        case 0xF00A:
            return ID_Fx0A;
        case 0xF015:
            return ID_Fx15;
        case 0xF018:
            return ID_Fx18;
        case 0xF01E:
            return ID_Fx1E;
        case 0xF029:
            return ID_Fx29;
        case 0xF033:
            return ID_Fx33;
        case 0xF055:
            return ID_Fx55;
        case 0xF065:
            return ID_Fx65;
        }

        return ID_NIMP;
    }
}

Debugger debug_create()
{
    Debugger debug = malloc(sizeof(struct debugger_type));
    debug->index = 0;
    return debug;
}

void debug_destroy(Debugger debug)
{
    free(debug);
}

void debug_add_instruction(Debugger debug,
                           uint16_t opcode)
{
    Instruction_info info = instruction_info[dissasembler(opcode)];
    info.opcode = opcode;

    debug->history[debug->index % INSTRUCTIONS_SIZE] = info;
    debug->index++;
}

void debug_print_last(Debugger debug)
{
    if (debug->index > 0)
    {
        Instruction_info info = debug->history[debug->index - 1];
        print_intruction(info);
    }
    else
    {
        printf("NO INSTRUCTIONS STORED, NULL INDEX");
    }
}

void debug_print_all_instructions()
{

    for (int i = 0; i < INSTRUCTIONS_SIZE; i++)
    {
        //printf("%s\n", menemonics[history[i].add_info->menemonic]);
    }
}