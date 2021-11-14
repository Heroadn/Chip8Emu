#include "cpu.h"
#include "debugger.h"

#define ADDRS_ROM 0x200
#define ADDRS_FONT 0x000
#define FONT_HEIGHT 5
#define FONT_CHARS 16
#define FONT_N FONT_HEIGHT * FONT_CHARS

typedef struct
{
    bool *sig_halt, //signal to halt
        *sig_exec;  //signal to cpu_execute the instruction
} Signal;

int init(int argc, char *argv[]);

void poolEvents(Signal *sig,
                Keyboard keyboard);

void clean(Register cpu,
           Memory mem,
           Gfx gfx,
           Keyboard key,
           Debugger deb);

void loader(Memory mem,
            ROM rom,
            ROM font);

void loop(Register cpu,
          Memory mem,
          Gfx gfx,
          Keyboard key,
          Debugger deb,
          int fps);

const char *rom_path[] = {"roms/test_opcode.ch8",
                          "roms/helloworld.rom",
                          "roms/breakout.ch8",
                          "roms/SCTEST.CH8",
                          "roms/chip8-test-rom.ch8",
                          "roms/Clock Program.ch8",
                          "roms/Keypad Test.ch8",
                          "roms/Chip8 Picture.ch8",
                          "roms/IBM Logo.ch8",
                          "roms/Particle Demo.ch8",
                          "roms/Tetris.ch8",
                          "roms/Maze.ch8",
                          "roms/c8_test.c8",
                          "roms/BC_test.ch8",
                          "roms/snake.ch8"};

const uint8_t font_data[FONT_N] = {0xF0, 0x90, 0x90, 0x90, 0xF0,
                                                      0x20, 0x60, 0x20, 0x20, 0x70,
                                                      0xF0, 0x10, 0xF0, 0x80, 0xF0,
                                                      0xF0, 0x10, 0xF0, 0x10, 0xF0,
                                                      0x90, 0x90, 0xF0, 0x10, 0x10,
                                                      0xF0, 0x80, 0xF0, 0x10, 0xF0,
                                                      0xF0, 0x80, 0xF0, 0x90, 0xF0,
                                                      0xF0, 0x10, 0x20, 0x40, 0x40,
                                                      0xF0, 0x90, 0xF0, 0x90, 0xF0,
                                                      0xF0, 0x90, 0xF0, 0x10, 0xF0,
                                                      0xF0, 0x90, 0xF0, 0x90, 0x90,
                                                      0xE0, 0x90, 0xE0, 0x90, 0xE0,
                                                      0xF0, 0x80, 0x80, 0x80, 0xF0,
                                                      0xE0, 0x90, 0x90, 0x90, 0xE0,
                                                      0xF0, 0x80, 0xF0, 0x80, 0xF0,
                                                      0xF0, 0x80, 0xF0, 0x80, 0x80};
