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
#include "config.h"

void loader(ROM rom,
            Memory mem,
            const char *filename);

void clean(CPU cpu,
           Memory mem,
           Config *conf);

void execute(CPU cpu,
             Memory mem,
             Gfx gfx,
             Instruction instruction,
             uint16_t op);

void cycle(CPU cpu,
           Memory mem,
           Gfx gfx);

Instruction decode(CPU cpu,
                   uint16_t op);

uint16_t loop(CPU cpu,
              Memory mem,
              Gfx gfx);

uint16_t fetch(CPU cpu,
               Memory mem);

int main(void)
{
    ROM rom = rom_create();
    CPU cpu = cpu_create();
    Memory mem = mem_create();
    Config conf = cfg_create();
    Gfx gfx = gfx_create(conf->SCREEN_WIDTH,
                         conf->SCREEN_HEIGHT,
                         conf->pallets[6],
                         conf->tab_name);

    //Roms disponiveis
    char *rom_path[] = {"roms/test_opcode.ch8",
                        "roms/helloworld.rom"};

    //Carregando rom na memoria
    loader(rom,
           mem,
           rom_path[0]);

    //Iniciando pc
    cpu_set_pc(cpu,
               512);

    loop(cpu,
         mem,
         gfx);

    clean(cpu,
          mem,
          conf);

    return 0;
}

void cycle(CPU cpu,
           Memory mem,
           Gfx gfx)
{
    static uint16_t op;
    static Instruction instruction;

    op = fetch(cpu,
               mem);

    instruction = decode(cpu,
                         op);

    execute(cpu,
            mem,
            gfx,
            instruction,
            op);
}

void execute(CPU cpu,
             Memory mem,
             Gfx gfx,
             Instruction instruction,
             uint16_t op)
{
    instruction(cpu,
                mem,
                gfx,
                op);
    cpu_inc_pc_word(cpu);
}

Instruction decode(CPU cpu,
                   uint16_t op)
{
    uint16_t instr = (op & 0xF000);
    printf("PC: %4x, OP: %x ", cpu_get_pc(cpu), op);

    return cpu_get_instruction(cpu,
                               op);
}

uint16_t loop(CPU cpu,
              Memory mem,
              Gfx gfx)
{

    //The event structure that will be used
    SDL_Event event;
    bool quit = false, run = false;
    uint16_t op;
    Instruction instruction;

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
            //cycle
            cycle(cpu, mem, gfx);

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
           Memory mem,
           Config *cfg)
{
    mem_destroy(mem);
    cpu_destroy(cpu);
    cfg_destroy(cfg);
}
