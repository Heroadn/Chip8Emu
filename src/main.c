#include "main.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define DEBUG

//win32 needs a diferent entrypoint 'WinMain'
#if defined(LINUX)
int main(int argc, char *argv[])
{
    init(argc, &argv);
    return 0;
}
#elif defined(WINDOWS)
int WinMain(int argc, char *argv[])
{
    init(__argc, __argv);
    return 0;
}
#endif

/*Arguments received by the cmd*/
typedef struct
{
    int width, height;       /* Width and height of the screen */
    int bpp, fps;            /* Bits per pixel and Frames per second*/
    char *rom;               /* Path to the rom */
    uint8_t color[CHANNELS]; /* Color of pixels*/
    uint8_t bg[CHANNELS];    /* Color of the background */
} Args;

char *args_doc[] =
    {
        "    -w Width of the screen\n"
        "    -h Height of the screen\n",
        "    -p Bits per pixel(opt)\n",
        "    -r Path to the ROM\n",
        "    -f Frames per second(opt)\n",
        "    -c Color of pixels(opt)\n",
        "    -b Color of the background(opt)\n",
        "\0"};

/* Parse a single option. */
static bool parse_opt(uint8_t key, char *arg, Args *arguments)
{
    switch (key)
    {
    case 'w':
        arguments->width = atoi(arg);
        break;
    case 'h':
        arguments->height = atoi(arg);
        break;
    case 'p':
        arguments->bpp = atoi(arg);
        break;
    case 'f':
        arguments->fps = atoi(arg);
        break;
    case 'r':
        arguments->rom = arg;
        break;
    case 'c':
        sscanf(arg,
               "%2x%2x%2x",
               &arguments->color[0],
               &arguments->color[1],
               &arguments->color[2]);
        break;
    case 'b':
        sscanf(arg,
               "%2x%2x%2x",
               &arguments->bg[0],
               &arguments->bg[1],
               &arguments->bg[2]);
        break;
    default:
        return false;
    }

    return true;
}

void init(int argc, char *argv[])
{
    /* Default arguments */
    Args arguments = {
        .color = {0x18,0x8c,0x35}, 
        .bg = {0x0D, 0x0D, 0x0D},
        .bpp = 16,
        .fps = 60};

    for (size_t i = 0; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            parse_opt(
                argv[i][1],
                argv[i + 1],
                &arguments);
            i++;
        }
    }

    /* Checking for errors such as negative screen width*/
    if (arguments.width <= 0 || arguments.height <= 0)
    {
        printf("Invalid Args\nUsage:\n");
        for (size_t i = 0; args_doc[i][0] != '\0'; i++)
            printf("%s", args_doc[i]);
        exit(EXIT_FAILURE);
    }

    
    Register reg = reg_create();
    Memory mem = mem_create();
    Keyboard key = key_create();
    ROM rom = rom_create(arguments.rom);
    Debugger deb = debug_create(reg,
                                mem);

    Font font = font_create(font_data,
                            FONT_NCHARS * FONT_HEIGHT);

    Gfx gfx = gfx_create(arguments.width,
                         arguments.height,
                         arguments.bpp,
                         arguments.color,
                         arguments.bg,
                         "Chip8Emu");

    /*INITIALIZING RAND*/
    time_t t;
    srand((unsigned)time(&t));

    /*Carregando rom na memoria e font, 
     *ambas as classes limpas apos o carregamento*/
    loader(rom,
           mem,
           font);

    //Iniciando pc
    reg_set_pc(reg,
               MEM_INIT_PC_ADDR);

    loop(reg,
         mem,
         gfx,
         key,
         deb,
         arguments.fps);

    clean(reg,
          mem,
          gfx,
          key,
          deb);
}

void poolEvents(Signal *sig,
                Keyboard keyboard)
{
    key_pool(keyboard);
    sig->sig_halt = (key_is_quit_event(keyboard) == true);
    sig->sig_exec = (key_is_pause_event(keyboard) == false);
}

void clean(Register reg,
           Memory mem,
           Gfx gfx,
           Keyboard key,
           Debugger deb)
{
    gfx_clean_up(gfx);
    gfx_destroy(gfx);
    mem_destroy(mem);
    reg_destroy(reg);
    key_destroy(key);
    debug_destroy(deb);
}

void loader(ROM rom,
            Memory mem,
            Font font)
{
    //mover rom para a ram
    mem_move_rom(mem,
                 rom->nchars,
                 rom->ptr);

    mem_move_interpreter(mem,
                         font->size,
                         font->ptr);

    //descartando componente rom
    rom_destroy(rom);
    font_destroy(font);
}

void loop(Register reg,
          Memory mem,
          Gfx gfx,
          Keyboard key,
          Debugger deb,
          int fps)
{
    SDL_Event event;             //The event structure that will be used

    //Hold the state of execution
    Signal sig = {.sig_exec = true,
                  .sig_halt = false};

    uint32_t last = 0,
             now = 0,
             delay = 0,
             ticks_per_sec = 1000 / fps;
    uint16_t op;

    while (sig.sig_halt == false)
    {
        poolEvents(&sig,
                   key);

        last = SDL_GetTicks();
        if (sig.sig_exec)
        {
            //cpu_cycle
            op = cpu_cycle(reg,
                           mem,
                           gfx,
                           key);

            //debugger
            #if defined(DEBUG)
                debug_add_instruction(deb,
                                      op);

                debug_print(deb);
            #endif

            //Update Screen
            gfx_flip(gfx);
        }
        now = SDL_GetTicks();
        delay = ticks_per_sec - (now - last);
        SDL_Delay(delay);
    }
}