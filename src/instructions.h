#include <stdint.h>
#include "register.h"
#include "memory.h"
#include "graphics.h"
#include "keyboard.h"

//#define ins_get_group(op, instructions) (instructions[((op) & 0xF000) >> 12])
//#define ins_get_instruction(op) ins_get_group(op).group[((v) & ins_get_group(op))].mask];

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef void (*Instruction_ptr)(void *,
                                void *,
                                void *,
                                void *,
                                uint16_t op);

/*Map a group of instructions_group to a mask 
like a 2d array indexer*/
typedef struct instruction_type
{
    Instruction_ptr *group;
    uint16_t mask;
} Instruction;

//0x!000
void ins_not_implmented(Register cpu,
                        Memory mem,
                        Gfx gfx,
                        Keyboard key,
                        uint16_t op);

//0x0000
void ins_nop(Register cpu,
             Memory mem,
             Gfx gfx,
             Keyboard key,
             uint16_t op);

//CLR - 0x00e0
void ins_00e0(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//0x00ee
void ins_00ee(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//0x1000
void ins_1nnn(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//Call - 0x2000
void ins_2nnn(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//Skip if equal - 0x3000
void ins_3xkk(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//Skip if Vx != kk - 0x4000
void ins_4xkk(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//Skip if Vx == Vy - 0x5000
void ins_5xy0(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//LD Vx, byte - 0x6000
void ins_6xkk(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//ADD - Vx = Vx + kk
void ins_7xkk(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//LD Vx = Vy - 0x8000
void ins_8xy0(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//OR Vx = Vx OR Vy - 0x8001
void ins_8xy1(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//AND Vx = Vx AND Vy - 0x8002
void ins_8xy2(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//XOR Vx = Vx AND Vy - 0x8003
void ins_8xy3(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//ADD Vx = Vx AND Vy - 0x8004
void ins_8xy4(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//SUB Vx = Vx AND Vy - 0x8005
void ins_8xy5(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//SUB SHR Vx = Vy >> 1 - 0x8006
void ins_8xy6(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//SUBN Vx = Vx AND Vy - 0x8005
void ins_8xy7(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//SUB SHL Vx = Vy << 1 - 0x8006
void ins_8xye(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//SKIP - if Vx != Vy - 0x9000
void ins_9xy0(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//RND Vx = byte AND kk - 0xcxkk
void ins_cxkk(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//Draw - 0xd000
void ins_dxyn(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//LD I, addr - 0xa000
void ins_annn(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//SKIP if key in Vx is pressed - 0xEx9e
void ins_ex9e(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard keyboard,
              uint16_t op);

//SKIP if key in Vx is not pressed - 0xExA1
void ins_exa1(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard keyboard,
              uint16_t op);

//Set Vx = delay - 0xf007
void ins_fx07(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard keyboard,
              uint16_t op);

//IN Vx = Key - 0xf00a
void ins_fx0a(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//SET delay timer = Vx - 0xf015
void ins_fx15(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//SET sound timer = Vx - 0xf018
void ins_fx18(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//ADD I = Vx, 0x_fx1e
void ins_fx1e(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//SET I = location of sprite for digit in Vx - 0xf018
void ins_fx29(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//BCD of Vx, starting at I, I + 1, I + 2
void ins_fx33(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//Store V0 though Vx, starting at I
void ins_fx55(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

//Load V0 though Vx, starting at I
void ins_fx65(Register cpu,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op);

#endif /* INSTRUCTION_H */

/*
//0xF000
1nnn - JP addr
2nnn - CALL addr
3xkk - SE Vx, byte
4xkk - SNE Vx, byte
5xy0 - SE Vx, Vy
6xkk - LD Vx, byte
7xkk - ADD Vx, byte
9xy0 - SNE Vx, Vy
Bnnn - JP V0, addr
Cxkk - RND Vx, byte
Dxyn - DRW Vx, Vy, nibble

//0xF00F
8xy0 - LD Vx, Vy
8xy1 - OR Vx, Vy
8xy2 - AND Vx, Vy
8xy3 - XOR Vx, Vy
8xy4 - ADD Vx, Vy
8xy5 - SUB Vx, Vy
8xy6 - SHR Vx {, Vy}
8xy7 - SUBN Vx, Vy
8xyE - SHL Vx {, Vy}

//0xF0FF
Ex9E - SKP Vx
ExA1 - SKNP Vx
00E0 - CLS
00EE - RET

//0xF0FF
Fx07 - LD Vx, DT
Fx0A - LD Vx, K
Fx15 - LD DT, Vx
Fx18 - LD ST, Vx
Fx1E - ADD I, Vx
Fx29 - LD F, Vx
Fx33 - LD B, Vx
Fx55 - LD [I], Vx
Fx65 - LD Vx, [I]
*/
