#include <stdint.h>
#include <stdlib.h>
#include "memory.h"
#include "graphics.h"
#include "instructions.h"
#define get_sign(x) ((x) >= 0) ? 1 : -1

void ins_not_implmented(Register reg,
                        Memory mem,
                        Gfx gfx,
                        Keyboard key,
                        uint16_t op)
{
    printf("OP %x NOT IMPLEMENTED\n", op);
}

void ins_nop(Register reg,
             Memory mem,
             Gfx gfx,
             Keyboard key,
             uint16_t op)
{
    printf("NOP\n");
}

//0x00e0
void ins_00e0(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    //printf("CLR SCREEN\n");
    gfx_clear_screen(gfx);
}

void ins_00ee(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    //printf("RET %x\n",
    //       reg_get_byte(reg, REG_BYTE_STACK));
    reg_set_pc(reg,
               reg_stack_pop(reg));
    //reg_stack_print(reg);
}

void ins_1nnn(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    reg_set_pc(reg,
               (op & 0x0FFF));
    reg_set_pc(reg,
               reg_get_pc(reg) - 2);

    //printf("JUMP %x\n", reg_get_pc(reg) + 2);
}

void ins_2nnn(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    //salvar na stack endereço do pc atual
    reg_stack_push(reg,
                   reg_get_pc(reg));

    reg_set_pc(reg,
               (op & 0x0FFF));
    reg_set_pc(reg,
               reg_get_pc(reg) - 2);

    //printf("CALL %x\n", reg_get_pc(reg) + 2);
}

void ins_3xkk(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int kk = (op & 0x0FF);

    //printf("SKIP V%x == kk, %x == %x\n", x, reg_get_byte(reg, x), kk);
    if (reg_get_byte(reg, x) == kk)
    {
        reg_set_pc(reg, reg_get_pc(reg) + 2);
    }
}

//Skip if Vx != kk - 0x4000
void ins_4xkk(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int kk = (op & 0x0FF);

    //printf("SKIP V%x != kk, %x != %x\n", x, reg_get_byte(reg, x), kk);
    if (reg_get_byte(reg, x) != kk)
    {
        reg_set_pc(reg,
                   reg_get_pc(reg) + 2);
    }
}

//Skip if Vx == Vy - 0x5000
void ins_5xy0(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int y = (op & 0x0F0) >> 4;

    //printf("SKIP V%x, V%x, %x == %x\n", x, y,
    //       reg_get_byte(reg, x), reg_get_byte(reg, y));

    if (reg_get_byte(reg, x) == reg_get_byte(reg, y))
    {
        reg_set_pc(reg, reg_get_pc(reg) + 2);
    }
}

//ADD - Vx = Vx + kk
void ins_7xkk(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    uint8_t x = (op & 0xF00) >> 8;
    uint8_t kk = (op & 0x0FF);
    uint8_t result = (reg_get_byte(reg, x) + kk);
    reg_set_flag(reg,
                 FLAG_OVERFLOW,
                 false);

    //printf("ADD V%x = %x + %x\n", x, reg_get_byte(reg, x), kk);
    reg_set_byte(reg,
                 x,
                 result);
}

void ins_8xy0(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int y = (op & 0x0F0) >> 4;

    //printf("LD V%x, V%x, V%x = %x\n", x, y,
    //       x, reg_get_byte(reg, y));
    reg_load(reg, y, x);
}

//OR Vx = Vx OR Vy - 0x8001
void ins_8xy1(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int y = (op & 0x0F0) >> 4;

    /*
    printf("OR V%x = %x | %x\n",
           x,
           reg_get_byte(reg, x),
           reg_get_byte(reg, y));*/
    reg_or_reg(reg, y, x);
}

void ins_8xy2(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int y = (op & 0x0F0) >> 4;

    /*
    printf("AND V%x = %x & %x\n",
           x,
           reg_get_byte(reg, x),
           reg_get_byte(reg, y));*/
    reg_and_reg(reg, y, x);
}

void ins_8xy3(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int y = (op & 0x0F0) >> 4;

    /*
    printf("XOR V%x = %x ^ %x\n",
           x,
           reg_get_byte(reg, x),
           reg_get_byte(reg, y));*/
    reg_xor_reg(reg, y, x);
}

void ins_8xy4(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int y = (op & 0x0F0) >> 4;

    /*
    printf("ADD V%x = %x + %x\n",
           x,
           reg_get_byte(reg, x),
           reg_get_byte(reg, y));*/
    reg_add_reg(reg, y, x);
}

void ins_8xy5(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int y = (op & 0x0F0) >> 4;

    reg_set_flag(reg,
                 FLAG_NOTBORROW,
                 reg_get_byte(reg, x) > reg_get_byte(reg, y));

    /*
    printf("SUB V%x = %x - %x\n",
           x,
           reg_get_byte(reg, y),
           reg_get_byte(reg, x));*/
    reg_sub_reg(reg, y, x);
}

void ins_8xy6(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int y = (op & 0x0F0) >> 4;

    /*
    printf("SHR V%x = %x >> 1\n",
           x,
           reg_get_byte(reg, y));*/

    reg_set_flag(reg,
                 FLAG_LSB_ON,
                 (reg_get_byte(reg, x) & 1));

    reg_shr(reg, y, x);
}

void ins_8xy7(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int y = (op & 0x0F0) >> 4;


    reg_set_flag(reg,
                 FLAG_NOTBORROW,
                 reg_get_byte(reg, x) < reg_get_byte(reg, y));

    /*
    printf("SUBN V%x = %x - %x\n",
           x,
           reg_get_byte(reg, x),
           reg_get_byte(reg, y));*/
    reg_subn_reg(reg, y, x);
}

void ins_8xye(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int y = (op & 0x0F0) >> 4;
    /*
    printf("SHL V%x = %x << 1\n",
           x,
           reg_get_byte(reg, y));*/

    reg_set_flag(reg,
                 FLAG_MSB_ON,
                 (reg_get_byte(reg, x) & (1 << 7)));
    reg_shl(reg, y, x);
}

void ins_9xy0(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    int x = (op & 0xF00) >> 8;
    int y = (op & 0x0F0) >> 4;

    /*
    printf("SKIP V%x, V%x, %x == %x\n", x, y,
           reg_get_byte(reg, x), reg_get_byte(reg, y));*/

    if (reg_get_byte(reg, x) != reg_get_byte(reg, y))
    {
        reg_set_pc(reg, reg_get_pc(reg) + 2);
    }
}

//RND Vx = byte AND kk - 0xcxkk
void ins_cxkk(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    uint8_t x = ((op & 0x0F00) >> 8),
            kk = ((op & 0x00FF)),
            r = rand();

    reg_set_byte(reg,
                 x,
                 r & kk);

    //printf("RAND V%x = %x\n", x, r & kk);
}

void ins_dxyn(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    uint8_t bytes = (op & 0x00F),
            sprite[15] = {0},
            x = reg_get_byte(reg,
                             (op & 0x0F00) >> 8),
            y = reg_get_byte(reg,
                             (op & 0x00F0) >> 4);
    bool is_colission = false;

    //printf("Dxyn x=%x y=%x bytes=%x \n", x, y, bytes);

    for (int i = 0, addr = 0; i < bytes; i++)
    {
        addr = reg_get_word(reg, REG_WORD_I) + i;
        sprite[i] = mem_load_byte(mem,
                                  addr);
    }

    is_colission = gfx_draw_sprite(x,
                                   y,
                                   bytes,
                                   sprite,
                                   gfx);

    reg_set_flag(reg,
                 FLAG_COLLISION,
                 is_colission);

    gfx_draw_screen(gfx);
}

void ins_6xkk(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    reg_set_byte(reg,
                 (op & 0x0F00) >> 8,
                 (op & 0xFF));
    //printf("LD V%d = %x\n", (op & 0x0F00) >> 8, (op & 0xFF));
}

void ins_annn(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    reg_set_word(reg,
                 REG_WORD_I,
                 (op & 0xFFF));
    //printf("LD Vi = %x\n", (op & 0xFFF));
}

void ins_ex9e(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard keyboard,
              uint16_t op)
{
    uint8_t x = ((op & 0x0F00) >> 8);
    uint8_t key = key_pressed_now(keyboard);

    //printf("SKIP V%x, %x == %x\n", x, reg_get_byte(reg, x), key);
    if (x == key_pressed_now(keyboard))
        reg_inc_pc(reg);
}

//SKIP if key in Vx is not pressed - 0xExA1
void ins_exa1(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard keyboard,
              uint16_t op)
{
    uint8_t x = ((op & 0xF00) >> 8);
    uint8_t key = key_pressed_now(keyboard);

    //printf("SKIP V%x, %x == %x\n", x, reg_get_byte(reg, x), key);
    if (x != key_pressed_now(keyboard))
        reg_inc_pc(reg);
}

//Set Vx = delay - 0xf007
void ins_fx07(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard keyboard,
              uint16_t op)
{
    uint8_t x = ((op & 0xF00) >> 8);
    //printf("Set V%x = %x\n", x, reg_get_byte(reg, REG_BYTE_DELAY));
    reg_set_byte(reg,
                 x,
                 reg_get_byte(reg, REG_BYTE_DELAY));
}

void ins_fx0a(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard keyboard,
              uint16_t op)
{

    uint8_t x = ((op & 0xF00) >> 8);
    uint8_t key = key_pressed_now(keyboard);


    if (key == 255)
    {
        //printf("WAITING INPUT %d\n", key);
        reg_set_pc(reg,
                   reg_get_pc(reg) - 2);
    }
    else
    {   
        //printf("WAITING INPUT %d\n", key);
        printf("\n");
        reg_set_byte(reg,
                     x,
                     key);
    }
}

void ins_fx15(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    uint8_t x = reg_get_byte(reg,
                             (op & 0xF00) >> 8);

    reg_set_byte(reg, REG_BYTE_DELAY, x);
}

void ins_fx18(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    uint8_t x = reg_get_byte(reg,
                             (op & 0xF00) >> 8);
    reg_set_byte(reg,
                 REG_BYTE_SOUND,
                 x);
    //printf("Set sound = V%x\n", x);
}

//ADD I = Vx + I, 0x_fx1e
void ins_fx1e(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    uint8_t x = reg_get_byte(reg,
                             (op & 0xF00) >> 8);
    uint16_t i = reg_get_word(reg,
                              REG_WORD_I);

    /*
    printf("ADD Vi = %x + %x\n",
           x,
           i);*/
    reg_set_word(reg,
                 REG_WORD_I,
                 (x + i));
}

void ins_fx29(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    uint8_t x = reg_get_byte(reg,
                             ((op & 0xF00) >> 8));
    uint8_t addr = mem_load_segment(mem,
                                    5,
                                    x,
                                    0);
    /*printf("Set Vi = addr(%x) = %x\n",
           x,
           addr);*/
    reg_set_word(reg,
                 REG_WORD_I,
                 addr);
}

//BCD of Vx, store starting at I, I + 1, I + 2
void ins_fx33(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    uint8_t x, d[3] = {0};
    x = reg_get_byte(reg,
                     (op & 0xF00) >> 8);

    //extracting digits(reversed)
    for (int i = 2, aux = x; aux > 0; i--)
    {
        d[i] = (aux % 10);
        aux /= 10;
    }

    //digits are reversed in the array
   // printf("BCD %d, ", x);
    for (int i = 0; i < 3; i++)
    {
        //printf("%d ", d[i]);
        mem_store_byte(mem, reg_get_word(reg, REG_WORD_I) + i,
                       d[i]);
    }
    //printf("\n");
}

//Store V0 though Vx, starting at I
void ins_fx55(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    uint8_t x = ((op & 0xF00) >> 8);

    for (uint8_t i = 0; i <= x; i++)
    {
        mem_store_byte(mem,
                       reg_get_word(reg, REG_WORD_I) + i,
                       reg_get_byte(reg, i));
        /*printf("\nSTORE ALL %x = V%x = %x",
               reg_get_word(reg, REG_WORD_I) + i,
               i,
               reg_get_byte(reg, i));*/
    }
    //printf("\n");
}

//Load V0 though Vx, starting at I
void ins_fx65(Register reg,
              Memory mem,
              Gfx gfx,
              Keyboard key,
              uint16_t op)
{
    uint8_t x = ((op & 0xF00) >> 8);
    uint8_t byte = 0;

    for (uint8_t i = 0; i <= x; i++)
    {
        byte = mem_load_byte(mem,
                             reg_get_word(reg, REG_WORD_I) + i);

        /*printf("\nLOAD ALL V%x = %x(%x)",
               i,
               byte,
               reg_get_word(reg, REG_WORD_I) + i);*/

        reg_set_byte(reg,
                     i,
                     byte);
    }
    //printf("\n");
}