#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>

struct MouseClickEvent {
    float mouse_x;
    float mouse_y;
    Uint8 button;
};

#endif
