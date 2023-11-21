#ifndef SCREEN_HPP
#define SCREEN_HPP

#define SCALE_X 16
#define SCALE_Y 16

#include "SDL2/SDL.h"
#include "spdlog/spdlog.h"
#include "chip8_t.hpp"

void initSDL(SDL_Window** window, SDL_Renderer** renderer);
void drawScreen(Chip8* sys, SDL_Renderer* renderer);

#endif