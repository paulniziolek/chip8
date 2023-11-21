#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "SDL2/SDL.h"
#include "spdlog/spdlog.h"
#include "chip8_t.hpp"

// Will poll the user for keyboard inputs
// SPACE pauses the Chip8 instance
// F10 restarts the Chip8 instance
// F12 shuts down the emulator.
void process_user_input(Chip8* sys); 

#endif