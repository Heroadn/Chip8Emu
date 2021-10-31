#include "cpu.h"
#include "font.h"
#include "config.h"
#include "debugger.h"

#define NUM_CFG_INT 3
#define NUM_CFG_STRING 1
#define NUM_CFG_COLOR 18
#define NUM_CFG_ATTRIB_COLOR 2

#define MEM_INIT_PC_ADDR 512
#define SIZE_TAB_NAME 32

#define ROM_INDEX 0
#define PALLE_INDEX 4

#define FONT_HEIGHT 5
#define FONT_NCHARS 16
#define TICK 5.0

void init();

void poolEvents(Signal *sig,
                Keyboard keyboard);

void clean(Register cpu,
           Memory mem,
           Gfx gfx,
           Config *cfg,
           Keyboard key,
           Debugger deb);

void loader(ROM rom,
            Memory mem,
            Font font);

void loop(Register cpu,
          Memory mem,
          Gfx gfx,
          Keyboard key,
          Debugger deb);

const char *config_strings[NUM_CFG_STRING] = {"TAB_NAME"};

const char *config_colors[NUM_CFG_COLOR] = {"colors",
                                            "background"};

const char *config_ints[NUM_CFG_INT] = {"SCREEN_WIDTH",
                                        "SCREEN_HEIGHT",
                                        "BITS_PER_PIXEL"};

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

const uint8_t font_data[FONT_NCHARS * FONT_HEIGHT] = {0xF0, 0x90, 0x90, 0x90, 0xF0,
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
