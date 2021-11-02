#include "main.h"
//#define WINDOWS //the target system

 //windows needs a diferent entrypoint name 'WinMain'
#if defined(LINUX)
    int main(int argc, char *argv[])
    {
        printf("XD %d", argc);
        //init(argc, &argv);   
        return 0;
    }
#elif defined(WINDOWS)

    int WinMain(int argc, char *argv[])
    {
        init(__argc, __argv);   
        return 0;
    }
#endif

//resolver resolução do disposiivo de target

void init(int argc, char *argv[])
{
    if(argc < 3)
    {
        fprintf(stdout, "Missing cmd arguments\n");
        fprintf(stdout, "-w screen width\n");
        fprintf(stdout, "-h screen height\n");
        fprintf(stdout, "-p rrggbb rrggbb\n");
        fprintf(stdout, "-r rom_path\n");

        return 1;
    }

    int screen_width, screen_height, bpp;
    char tab_name = "Chip8Emu";
    const uint8_t color[CHANNELS];
    const uint8_t background[CHANNELS];

    Debugger deb = debug_create();
    Register cpu = reg_create();
    Memory mem = mem_create();
    Keyboard key = key_create();
    ROM rom = rom_create(rom_path[CFG_IDX_ROM]);
    Font font = font_create(font_data,
                            FONT_NCHARS * FONT_HEIGHT);

    Gfx gfx = gfx_create(screen_width,
                         screen_height,
                         bpp,
                         color,
                         background,
                         tab_name);

    /*INITIALIZING RAND*/
    time_t t;
    srand((unsigned)time(&t));

    /*Carregando rom na memoria e font, 
     *ambas as classes limpas apos o carregamento*/
    loader(rom,
           mem,
           font);

    //Iniciando pc
    reg_set_pc(cpu,
               MEM_INIT_PC_ADDR);

    loop(cpu,
         mem,
         gfx,
         key,
         deb);

    clean(cpu,
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

void init_conf(Config cfg,
               char *tab_name,
               int val[NUM_CFG_INT],
               uint8_t colors[][CHANNELS],
               uint8_t background[][CHANNELS])
{

    cfg_open(cfg);
    cfg_get_int_multiple(cfg,
                         NUM_CFG_INT,
                         0,
                         val,
                         config_ints);
    cfg_get_string(cfg,
                   CFG_SIZE_TAB_NAME,
                   0,
                   config_strings[0],
                   tab_name);

    cfg_get_color_array(cfg,
                        0,
                        CFG_NUM_PALLETS / CFG_NUM_LAYERS,
                        config_colors[0],
                        colors);

    cfg_get_color_array(cfg,
                        0,
                        CFG_NUM_PALLETS / CFG_NUM_LAYERS,
                        config_colors[1],
                        background);
}

void clean(Register cpu,
           Memory mem,
           Gfx gfx,
           Keyboard key,
           Debugger deb)
{
    gfx_clean_up(gfx);
    gfx_destroy(gfx);
    mem_destroy(mem);
    reg_destroy(cpu);
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

void loop(Register cpu,
          Memory mem,
          Gfx gfx,
          Keyboard key,
          Debugger deb)
{
    SDL_Event event;             //The event structure that will be used
    Instruction_ptr instruction; //Class resposible for current exec intructions

    //Hold the state of execution
    Signal sig = {.sig_exec = true,
                  .sig_halt = false};

    uint32_t last = 0,
             now = 0,
             delay = 0,
             ticks_per_sec = 1000 / TICK;
    uint16_t op;

    while (sig.sig_halt == false)
    {
        poolEvents(&sig,
                   key);

        last = SDL_GetTicks();
        if (sig.sig_exec)
        {
            //cpu_cycle
            op = cpu_cycle(cpu,
                           mem,
                           gfx,
                           key);

            //debugger
            debug_add_instruction(deb,
                                  op);

            debug_print(deb);

            //Update Screen
            gfx_flip(gfx);
        }
        now = SDL_GetTicks();
        delay = ticks_per_sec - (now - last);
        SDL_Delay(delay);
    }
}