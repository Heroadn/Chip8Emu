#include "cpu.h"
#include "debugger.h"

#define ADDRS_ROM 0x200
#define ADDRS_FONT 0x000
#define FONT_HEIGHT 5
#define FONT_CHARS 16
#define FONT_N FONT_HEIGHT *FONT_CHARS

typedef struct
{
    bool *sig_halt, //signal to halt
        *sig_exec;  //signal to cpu_execute the instruction
} Signal;

/*Arguments received by the cmd*/
typedef struct
{
    int width, height;       /* Width and height of the screen */
    int bpp, fps;            /* Bits per pixel and Frames per second*/
    char *rom;               /* Path to the rom */
    uint8_t color[CHANNELS]; /* Color of pixels*/
    uint8_t bg[CHANNELS];    /* Color of the background */
} Args;

static int init(int argc, char *argv[]);

static void poolEvents(Signal *sig,
                       Keyboard keyboard);

static void clean(Register cpu,
                  Memory mem,
                  Gfx gfx,
                  Keyboard key,
                  Debugger deb);

static void loader(Memory mem,
                   ROM rom,
                   ROM font);

static void loop(Register cpu,
                 Memory mem,
                 Gfx gfx,
                 Keyboard key,
                 Debugger deb,
                 int fps);

const uint8_t font_data[FONT_N] =
    {0xF0, 0x90, 0x90, 0x90, 0xF0,
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
