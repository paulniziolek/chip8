#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <map>

#include "SDL2/SDL.h"
#include "spdlog/spdlog.h"
#include "chip8_t.hpp"

// Will poll the user for keyboard inputs
// SPACE pauses the Chip8 instance
// F10 restarts the Chip8 instance
// F12 shuts down the emulator.
void process_user_input(Chip8* sys); 

static std::map<SDL_Keycode, int> mapKeys = {
    {SDLK_1, 0x1},
    {SDLK_2, 0x2},
    {SDLK_3, 0x3},
    {SDLK_4, 0xC},
    {SDLK_q, 0x4},
    {SDLK_w, 0x5},
    {SDLK_e, 0x6},
    {SDLK_r, 0xD},
    {SDLK_a, 0x7},
    {SDLK_s, 0x8},
    {SDLK_d, 0x9},
    {SDLK_f, 0xE},
    {SDLK_z, 0xA},
    {SDLK_x, 0x0},
    {SDLK_c, 0xB},
    {SDLK_v, 0xF}
};

#endif