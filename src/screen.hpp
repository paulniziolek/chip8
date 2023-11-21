#ifndef SCREEN_HPP
#define SCREEN_HPP

#define SCALE_X 16
#define SCALE_Y 16

#include "SDL2/SDL.h"
#include "spdlog/spdlog.h"
#include "chip8_t.hpp"

void drawScreen(Chip8* sys, SDL_Renderer* renderer);

#endif