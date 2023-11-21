#include "screen.hpp"

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