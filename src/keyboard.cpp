#include "keyboard.hpp"

void process_user_input(Chip8* sys) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            // the same as F12
            spdlog::info("program closed, shutting off system");
            sys->is_running_flag = false;
            sys->is_paused_flag = false;
        }

        switch (event.key.keysym.sym) {
        case SDLK_SPACE:
            if (event.key.type == SDL_KEYUP) continue;
            spdlog::info("{} key pressed, switching pause flag to {}", event.key.keysym.sym, sys->is_paused_flag^1);
            sys->is_paused_flag ^= 1;
            break;
        case SDLK_F9:
            if (event.key.type == SDL_KEYUP) continue;
            spdlog::get_level() == spdlog::level::debug ? spdlog::set_level(spdlog::level::info) : spdlog::set_level(spdlog::level::debug);
            break;
        case SDLK_F10:
            if (event.key.type == SDL_KEYUP) continue;
            spdlog::info("{} key pressed, restarting system", event.key.keysym.sym);
            break;
        case SDLK_F12:
            if (event.key.type == SDL_KEYUP) continue;
            spdlog::info("{} key pressed, shutting off system", event.key.keysym.sym);
            sys->is_running_flag = false;
            sys->is_paused_flag = false;
            break;
        }
    }
}
