#include "screen.hpp"

void initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        spdlog::error("SDL fails to initialize: {}", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *window = SDL_CreateWindow("Chip8 Emulator", 
                                    SDL_WINDOWPOS_UNDEFINED, 
                                    SDL_WINDOWPOS_UNDEFINED, 
                                    SCREEN_WIDTH * SCALE_X, 
                                    SCREEN_HEIGHT * SCALE_Y, 
                                    SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
    if (*window == nullptr) {
        spdlog::error("SDL failed to create window: {}", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == nullptr) {
        spdlog::error("SDL failed to create renderer: {}", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    SDL_RenderSetScale(*renderer, (float) SCALE_X, (float) SCALE_Y);
}

void drawScreen(Chip8* sys, SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            SDL_Rect rect;
            rect.x = x;
            rect.y = y;
            rect.w = 1;
            rect.h = 1;
            if (sys->screen[x][y]) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}