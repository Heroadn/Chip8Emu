#include <stdbool.h>
#include "keyboard.h"
#define NOT_CHANGED 255

typedef struct keyboard_type
{
    SDL_Event event;
    bool is_quit_event, is_pause_event;
    uint8_t key_pressed_now;
};

Keyboard key_create()
{
    Keyboard key = calloc(1, sizeof(struct keyboard_type));
    return key;
}

void key_destroy(Keyboard key)
{
    free(key);
}

uint8_t key_pool(Keyboard keyboard)
{
    while (SDL_PollEvent(&keyboard->event))
    {
        switch (keyboard->event.type)
        {
        case SDL_QUIT:
            keyboard->is_quit_event = true;
            break;
        case SDL_KEYDOWN:
        SDL_KEYUP:
            //0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F
            switch (keyboard->event.key.keysym.sym)
            {
            case SDLK_F8:
                break;
            break;
            case SDLK_0:
                keyboard->key_pressed_now = 0;
                break;
            case SDLK_1:
                keyboard->key_pressed_now = 1;
                break;
            case SDLK_2:
                keyboard->key_pressed_now = 2;
                break;
            case SDLK_3:
                keyboard->key_pressed_now = 3;
                break;
            case SDLK_4:
                keyboard->key_pressed_now = 4;
                break;
            case SDLK_5:
                keyboard->key_pressed_now = 5;
                break;
            case SDLK_6:
                keyboard->key_pressed_now = 6;
                break;
            case SDLK_7:
                keyboard->key_pressed_now = 7;
                break;
            case SDLK_8:
                keyboard->key_pressed_now = 8;
                break;
            case SDLK_9:
                keyboard->key_pressed_now = 9;
                break;
            case SDLK_a:
                keyboard->key_pressed_now = 10;
                break;
            case SDLK_b:
                keyboard->key_pressed_now = 11;
                break;
            case SDLK_c:
                keyboard->key_pressed_now = 12;
                break;
            case SDLK_d:
                keyboard->key_pressed_now = 13;
                break;
            case SDLK_e:
                keyboard->key_pressed_now = 14;
                break;
            case SDLK_f:
                keyboard->key_pressed_now = 15;
                break;
            case SDLK_ESCAPE:
                keyboard->is_pause_event ^= true;
                break;
            default:
                break;
            }
            break;
        default:
            keyboard->key_pressed_now = NOT_CHANGED;
            break;
        }
    }
    return NOT_CHANGED;
}

bool key_is_pause_event(Keyboard keyboard)
{
    return keyboard->is_pause_event;
}

bool key_is_quit_event(Keyboard keyboard)
{
    return keyboard->is_quit_event;
}

uint8_t key_pressed_now(Keyboard keyboard)
{
    return keyboard->key_pressed_now;
}


/*
uint8_t key_pool(Keyboard keyboard)
{
    while (SDL_PollEvent(&keyboard->event))
    {
        switch (keyboard->event.type)
        {
        case SDL_QUIT:
            keyboard->is_quit_event = true;
            break;
        case SDL_KEYDOWN:
        SDL_KEYUP:
            //0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F
            switch (keyboard->event.key.keysym.sym)
            {
            case SDLK_F8:
                break;
            break;
            case SDLK_0:
                keyboard->key_pressed_now = 0;
                break;
            case SDLK_1:
                keyboard->key_pressed_now = 1;
                break;
            case SDLK_2:
                keyboard->key_pressed_now = 2;
                break;
            case SDLK_3:
                keyboard->key_pressed_now = 3;
                break;
            case SDLK_4:
                keyboard->key_pressed_now = 4;
                break;
            case SDLK_5:
                keyboard->key_pressed_now = 5;
                break;
            case SDLK_6:
                keyboard->key_pressed_now = 6;
                break;
            case SDLK_7:
                keyboard->key_pressed_now = 7;
                break;
            case SDLK_8:
                keyboard->key_pressed_now = 8;
                break;
            case SDLK_9:
                keyboard->key_pressed_now = 9;
                break;
            case SDLK_a:
                keyboard->key_pressed_now = 10;
                break;
            case SDLK_b:
                keyboard->key_pressed_now = 11;
                break;
            case SDLK_c:
                keyboard->key_pressed_now = 12;
                break;
            case SDLK_d:
                keyboard->key_pressed_now = 13;
                break;
            case SDLK_e:
                keyboard->key_pressed_now = 14;
                break;
            case SDLK_f:
                keyboard->key_pressed_now = 15;
                break;
            case SDLK_ESCAPE:
                keyboard->is_pause_event ^= true;
                break;
            default:
                break;
            }
            break;
        default:
            keyboard->key_pressed_now = NOT_CHANGED;
            break;
        }
    }
    return NOT_CHANGED;
}
*/
