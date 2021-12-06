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
    return init(argc, &argv);
}
#elif defined(WINDOWS)
int WinMain(int argc, char *argv[])
{
    return init(__argc, __argv);
}
#endif

/* Parse a single option. */
static bool parse_opt(uint8_t key,
                      char *arg,
                      Args *args)
{
    switch (key)
    {
    case 'w':
        args->width = atoi(arg);
        break;
    case 'h':
        args->height = atoi(arg);
        break;
    case 'p':
        args->bpp = atoi(arg);
        break;
    case 'f':
        args->fps = atoi(arg);
        break;
    case 'r':
        args->rom = arg;
        break;
    case 'c':
        sscanf(arg,
               "%2x%2x%2x",
               &args->color[0],
               &args->color[1],
               &args->color[2]);
        break;
    case 'b':
        sscanf(arg,
               "%2x%2x%2x",
               &args->bg[0],
               &args->bg[1],
               &args->bg[2]);
        break;
    default:
        return false;
    }

    return true;
}

static void read_opt(int argc,
                     char *argv[],
                     Args *args)
{
    for (size_t i = 0; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            parse_opt(
                argv[i][1],
                argv[i + 1],
                args);
            i++;
        }
    }
}

static void inva_opt(Args *args)
{
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

    /* Checking for errors such as negative screen width*/
    if (args->width <= 0 || args->height <= 0)
    {
        printf("Invalid Args\nUsage:\n");
        for (size_t i = 0; args_doc[i][0] != '\0'; i++)
            printf("%s", args_doc[i]);
        exit(EXIT_FAILURE);
    }
}

static void debug(uint16_t op,
                  Register reg,
                  Debugger deb)
{
    //debugger
#if defined(DEBUG)
    {
        printf("PC: %4x, OP: %4x          ", reg_get_pc(reg), op);
        debug_add_instruction(deb,
                              op);

        debug_print(deb);
    }
#endif
}

static int init(int argc,
                char *argv[])
{
    /* Default args */
    Args args = {
        .color = {0x18, 0x8c, 0x35},
        .bg = {0x0D, 0x0D, 0x0D},
        .bpp = 16,
        .fps = 30};

    read_opt(argc, argv, &args);
    inva_opt(&args);

    /*INITIALIZING RAND*/
    time_t t;
    srand((unsigned)time(&t));

    /*INITIALIZING MODULES*/
    Memory mem = mem_create();
    Keyboard key = key_create();
    Register reg = reg_create();
    ROM rom = rom_create();
    ROM fnt = rom_create();
    Debugger deb = debug_create(reg,
                                mem);
    Gfx gfx = gfx_create(args.width,
                         args.height,
                         args.bpp,
                         args.color,
                         args.bg,
                         "Chip8Emu");

    /*reading rom, font and setting pc as ADDRS_ROM*/
    rom_read_file(rom,
                  args.rom);
    rom_read_data(fnt,
                  FONT_N,
                  font_data);
    reg_set_pc(reg,
               ADDRS_ROM);

    /*loading rom and font into mem
    rom and fnt are deallocated after use*/
    loader(mem,
           rom,
           fnt);

    /*It's the emu loop,
    draws, and do cpu operations*/
    loop(reg,
         mem,
         gfx,
         key,
         deb,
         args.fps);

    /*dealloc all modules after use*/
    clean(reg,
          mem,
          gfx,
          key,
          deb);

    return EXIT_SUCCESS;
}

static void poolEvents(Signal *sig,
                       Keyboard keyboard)
{
    key_pool(keyboard);
    sig->sig_halt = (key_is_quit_event(keyboard) == true);
    sig->sig_exec = (key_is_pause_event(keyboard) == false);
}

static void clean(Register reg,
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

static void loader(Memory mem,
                   ROM rom,
                   ROM fnt)
{
    mem_load(mem,
             rom->n,
             ADDRS_ROM,
             rom->ptr);

    mem_load(mem,
             fnt->n,
             ADDRS_FONT,
             fnt->ptr);

    //descartando componente rom
    rom_destroy(rom);
    rom_destroy(fnt);
}

static void loop(Register reg,
                 Memory mem,
                 Gfx gfx,
                 Keyboard key,
                 Debugger deb,
                 int fps)
{
    SDL_Event event; //The event structure that will be used

    //Hold the state of execution
    Signal sig = {.sig_exec = true,
                  .sig_halt = false};

    //fps and clock ticking
    uint32_t last = 0;
    uint32_t now = 0;
    uint32_t ticks_per_sec = 1000 / fps;
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

            //Update Screen
            gfx_flip(gfx);

            //debug 
            debug(op,
                  reg,
                  deb);
                  
        }else
        {
            switch (key_pressed_now(key))
            {
            case 1:
                debug_print_state(debug);
                break;
            default:
                break;
            }
        }

        now = SDL_GetTicks();
        SDL_Delay(ticks_per_sec - (now - last));
    }
}