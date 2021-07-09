#include <SDL/SDL.h>
#include <stdint.h>

typedef struct keyboard_type *Keyboard;

Keyboard key_create();

void key_destroy(Keyboard key);

uint8_t key_pool(Keyboard keyboard);

uint8_t key_pressed_now(Keyboard keyboard);

bool key_is_pause_event(Keyboard keyboard);

bool key_is_quit_event(Keyboard keyboard);


