#include <stdio.h>
#include "debugger.h"
#include "instructions.h"
#define INSTRUCTIONS_SIZE 4095

//modificar para que o emulador mande o endereço que esta executando
typedef struct debugger_type
{
    Instruction_log instruction_log;
    Register reg;
    Memory mem;
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
    ID_NIMP,
    SIZE_ID_INS
} ID_instruction;

Instruction_log instruction_info[] = {
    [ID_00E0] = {//0x00E0
                 .menemonic = MNE_CLS,
                 .operands[0] = {.addr = ADDR_NULL, .mask = 0},
                 .operands[1] = {.addr = ADDR_NULL, .mask = 0}},
    [ID_00EE] = {//0x00E0
                 .menemonic = MNE_RET,
                 .operands[0] = {.addr = ADDR_NULL, .mask = 0},
                 .operands[1] = {.addr = ADDR_NULL, .mask = 0}},
    [ID_1nnn] = {//0x1nnn
                 .menemonic = MNE_JP,
                 .operands[0] = {.addr = ADDR_ABS, .mask = 0x0FFF},
                 .operands[1] = {.addr = ADDR_NULL, .mask = 0}},
    [ID_2nnn] = {//0x2nnn
                 .menemonic = MNE_CALL,
                 .operands[0] = {.addr = ADDR_NULL, .mask = 0},
                 .operands[1] = {.addr = ADDR_ABS, .mask = 0xFFF}},
    [ID_3xkk] = {//0x3xkk
                 .menemonic = MNE_SE,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_ABS, .mask = 0x00FF}},
    [ID_4xkk] = {//0x4xkk
                 .menemonic = MNE_SNE,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_ABS, .mask = 0x00FF}},
    [ID_5xy0] = {//0x5xy0
                 .menemonic = MNE_SE,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x00F0}},
    [ID_6xkk] = {//0x6xkk
                 .menemonic = MNE_LD,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_ABS, .mask = 0x00FF}},
    [ID_7xkk] = {//0x7xkk
                 .menemonic = MNE_ADD,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_ABS, .mask = 0x00FF}},
    [ID_8xy0] = {//0x8xy0
                 .menemonic = MNE_LD,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x00F0}},
    [ID_8xy0] = {//0x8xy1
                 .menemonic = MNE_OR,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x00F0}},
    [ID_8xy1] = {//0x8xy2
                 .menemonic = MNE_AND,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x00F0}},
    [ID_8xy2] = {//0x8xy3
                 .menemonic = MNE_XOR,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x00F0}},
    [ID_8xy3] = {//0x8xy4
                 .menemonic = MNE_ADD,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x00F0}},
    [ID_8xy4] = {//0x8xy5
                 .menemonic = MNE_SUB,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x00F0}},
    [ID_8xy5] = {//0x8xy6
                 .menemonic = MNE_SHR,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x00F0}},
    [ID_8xy6] = {//0x8xy7
                 .menemonic = MNE_SUBN,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x00F0}},
    [ID_8xyE] = {//0x8xyE
                 .menemonic = MNE_SHL,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x00F0}},
    [ID_8xy7] = {//0x8xy7
                 .menemonic = MNE_SHL,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x00F0}},
    [ID_9xy0] = {//0x9xy0
                 .menemonic = MNE_SNE,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x00F0}},
    [ID_Annn] = {//0xAnnn
                 .menemonic = MNE_LD,
                 .operands[0] = {.addr = ADDR_REG_I, .mask = 0x0},
                 .operands[1] = {.addr = ADDR_ABS, .mask = 0x0FFF}},
    [ID_Bnnn] = {//0xBnnn
                 .menemonic = MNE_JP,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0},
                 .operands[1] = {.addr = ADDR_ABS, .mask = 0x0FFF}},
    [ID_Cxkk] = {//0xCxkk
                 .menemonic = MNE_RND,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0},
                 .operands[1] = {.addr = ADDR_ABS, .mask = 0x0}},
    [ID_Dxyn] = {//0xDxyn
                 .menemonic = MNE_DRW,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x00F0},
                 .operands[2] = {.addr = ADDR_ABS, .mask = 0x000F}},
    [ID_Ex9E] = {//0xEx9E
                 .menemonic = MNE_SKP,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0},
                 .operands[1] = {.addr = ADDR_NULL, .mask = 0x0}},
    [ID_ExA1] = {//0xExA1
                 .menemonic = MNE_SKNP,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0},
                 .operands[1] = {.addr = ADDR_NULL, .mask = 0x0}},
    [ID_Fx07] = {//0xFx07
                 .menemonic = MNE_LD,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0},
                 .operands[1] = {.addr = ADDR_ABS, .mask = 0x0}},
    [ID_Fx0A] = {//0xFx0A
                 .menemonic = MNE_LD,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0},
                 .operands[1] = {.addr = ADDR_ABS, .mask = 0x0}},
    [ID_Fx15] = {//0xFx15
                 .menemonic = MNE_LD,
                 .operands[0] = {.addr = ADDR_REG_TIMER, .mask = 0x0},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x0F00}},
    [ID_Fx18] = {//0xFx18
                 .menemonic = MNE_LD,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x0}},
    [ID_Fx1E] = {//0xFx1E
                 .menemonic = MNE_ADD,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x0}},
    [ID_Fx29] = {//0xFx29
                 .menemonic = MNE_LD,
                 .operands[0] = {.addr = ADDR_ABS, .mask = 0x0},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x0}},
    [ID_Fx33] = {//0xFx33
                 .menemonic = MNE_LD,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_REG_I, .mask = 0x0}},
    [ID_Fx55] = {//0xFx55
                 .menemonic = MNE_LD,
                 .operands[0] = {.addr = ADDR_REG_I_ARR, .mask = 0x0},
                 .operands[1] = {.addr = ADDR_REG, .mask = 0x0F00}},
    [ID_Fx65] = {//0xFx65
                 .menemonic = MNE_LD,
                 .operands[0] = {.addr = ADDR_REG, .mask = 0x0F00},
                 .operands[1] = {.addr = ADDR_REG_I_ARR, .mask = 0x0}},
    [ID_NOP] = {//Do nothing
                .menemonic = MNE_NOP,
                .operands[0] = {.addr = ADDR_NULL, .mask = 0x0},
                .operands[1] = {.addr = ADDR_NULL, .mask = 0x0}},
    [ID_NIMP] = {//Not implemented
                 .menemonic = MNE_NIMP,
                 .operands[0] = {.addr = ADDR_NULL, .mask = 0x0},
                 .operands[1] = {.addr = ADDR_NULL, .mask = 0x0}}};

static uint16_t remove_nimble_zeros(uint16_t operands)
{
    while ((operands & 0xF) == 0 && (operands != 0))
        operands >>= 4;

    return operands;
};

static void print_type_instruction(Instruction_log info)
{
    //Type of operation done by the instruction
    static const char *op_type[] =
        {
            [MNE_CLS] = " ",
            [MNE_LD] = ",",
            [MNE_AND] = " &",
            [MNE_OR] = " |",
            [MNE_CALL] = "<-",
            [MNE_RET] = "->",
            [MNE_SNE] = " !=",
            [MNE_SE] = " ==",
            [MNE_DRW] = ",",
            [MNE_ADD] = " +",
            [MNE_XOR] = " ^",
            [MNE_OR] = " |",
            [MNE_SUB] = " -",
            [MNE_SHR] = " >>",
            [MNE_SHL] = " <<",
            [MNE_SUBN] = " -"};

    printf("%s ", op_type[info.menemonic]);
}

static void print_menemonic(Instruction_log info)
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
    printf("%s ", menemonics[info.menemonic]);
}

static void print_addressing(uint16_t opcode,
                             struct Operand operand)
{
    static const char *arg_name[] =
        {
            [ADDR_REG] = "V",
            [ADDR_ABS] = "#",
            [ADDR_NULL] = "",
            [ADDR_REG_I] = "Vi",
            [ADDR_REG_TIMER] = "Vt",
            [ADDR_REG_I_ARR] = "[I]"};

    printf("%s", arg_name[operand.addr]);
}

static void print_operand(uint16_t opcode,
                          struct Operand operand)
{
    if (operand.addr == ADDR_REG || operand.addr == ADDR_ABS)
        printf("%x", remove_nimble_zeros(opcode & operand.mask));
}

//print the instruction
static void print_intruction(Instruction_log info)
{
    //menemonic
    print_menemonic(info);

    //Addresing addr and operand
    if (info.operands[0].addr != ADDR_NULL)
    {
        print_addressing(info.opcode,
                         info.operands[0]);
        print_operand(info.opcode,
                      info.operands[0]);
    }

    //Addresing addr and operand
    if (info.operands[1].addr != ADDR_NULL)
    {
        //Symbol of operation done
        print_type_instruction(info);

        print_addressing(info.opcode,
                         info.operands[1]);
        print_operand(info.opcode,
                      info.operands[1]);
    }

    //Addresing addr and operand
    if (info.operands[2].addr != ADDR_NULL)
    {
        //Symbol of operation done
        print_type_instruction(info);

        print_addressing(info.opcode,
                         info.operands[2]);
        print_operand(info.opcode,
                      info.operands[2]);
    }
}

void debug_print_state(Register reg)
{
    //for (size_t i = 0; i < SIZE_REG_BYTE - 1; i++)
    //    printf("V%.2x ", i);

    //printf("\n");
    printf("regs:[");
    for (size_t i = 0; i < SIZE_REG_BYTE - 1; i++)
    {
        printf("%x, ", reg_get_byte(reg, i));
    }
    printf("]");
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
    case 0xB000:
        return ID_Bnnn;
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

Debugger debug_create(Register reg,
                      Memory mem)
{
    Debugger debug = malloc(sizeof(struct debugger_type));
    debug->mem = mem;
    debug->reg = reg;
    return debug;
}

void debug_destroy(Debugger debug)
{
    free(debug);
}

void debug_print(Debugger debug)
{
    Instruction_log info = debug->instruction_log;
    print_intruction(info);
    printf("\n");
}

void debug_add_instruction(Debugger debug,
                           uint16_t opcode)
{
    Instruction_log info = instruction_info[dissasembler(opcode)];
    info.opcode = opcode;
    debug->instruction_log = info;
}
