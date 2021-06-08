#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

#include "utils/file.h"
#include "utils/binary_reader.h"
#include "memory.h"
#include "rom.h"
#include "cpu.h"
#include "graphics.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BITS_PER_PIXEL = 32;
const char *tab_name = "Hello World";

void loader(ROM rom,
            Memory mem,
            const char *filename);

void clean(CPU cpu,
           Memory mem);

void decode(CPU cpu,
            uint16_t op,
            Memory mem,
            Gfx gfx);

void execute(CPU cpu);

uint16_t loop(CPU cpu,
              Memory mem);

uint16_t fetch(CPU cpu,
               Memory mem);

int main(void)
{

    ROM rom = rom_create();
    CPU cpu = cpu_create();
    Memory mem = mem_create();

    //Carregando rom na memoria
    loader(rom,
           mem,
           "roms/test_opcode.ch8");

    //Iniciando pc
    cpu_set_pc(cpu,
               512);

    loop(cpu,
         mem);

    clean(cpu,
          mem);

    return 0;
}

void execute(CPU cpu)
{
}

void decode(CPU cpu,
            uint16_t op,
            Memory mem,
            Gfx gfx)
{
    uint16_t instr = (op & 0xF000);
    printf("PC: %4x, OP: %x ", cpu_get_pc(cpu), op);

    Instructions instruction = cpu_get_instruction(cpu,
                                                   instr);
    instruction(cpu,
                mem,
                gfx,
                op);
    cpu_inc_pc_word(cpu);
}

uint16_t loop(CPU cpu,
              Memory mem)
{
    Gfx gfx = gfx_create(SCREEN_WIDTH,
                         SCREEN_HEIGHT,
                         tab_name);

    //The event structure that will be used
    SDL_Event event;
    bool quit = false, run = false;
    uint16_t op;

    while (quit == false)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                if (SDLK_F8)
                    run = true;
                break;
            default:
                break;
            }
        }

        if (run)
        {
            op = fetch(cpu,
                       mem);
            decode(cpu,
                   op,
                   mem,
                   gfx);

            //Update Screen
            gfx_flip(gfx);
        }

        run = false;
    }

    gfx_clean_up(gfx);
    gfx_destroy(gfx);
}

uint16_t fetch(CPU cpu,
               Memory mem)
{
    return mem_load_word(mem,
                         cpu_get_pc(cpu));
}

void loader(ROM rom,
            Memory mem,
            const char *filename)
{
    //carregando rom
    rom_read(rom,
             filename);

    //mover rom para a ram
    mem_move_rom(mem,
                 rom->nchars,
                 rom->ptr);

    //descartando componente rom
    rom_destroy(rom);
}

void clean(CPU cpu,
           Memory mem)
{
    mem_destroy(mem);
    cpu_destroy(cpu);
}
