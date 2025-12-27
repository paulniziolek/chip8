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
        // Ignore key-repeats, as Chip8 considers buttons binary (down or up, not repeated).
        if (event.type == SDL_KEYDOWN && event.key.repeat) continue;

        switch (event.key.keysym.sym) {
        case SDLK_SPACE:
            if (event.type == SDL_KEYUP) continue;
            spdlog::info("{} key pressed, switching pause flag to {}", event.key.keysym.sym, sys->is_paused_flag^1);
            sys->is_paused_flag ^= 1;
            break;
        case SDLK_F9:
            if (event.type == SDL_KEYUP) continue;
            spdlog::get_level() == spdlog::level::debug ? spdlog::set_level(spdlog::level::info) : spdlog::set_level(spdlog::level::debug);
            break;
        case SDLK_F10:
            if (event.type == SDL_KEYUP) continue;
            spdlog::info("{} key pressed, restarting system", event.key.keysym.sym);
            sys->init_system();
            sys->load_rom();
            break;
        case SDLK_F12:
            if (event.type == SDL_KEYUP) continue;
            spdlog::info("{} key pressed, shutting off system", event.key.keysym.sym);
            sys->is_running_flag = false;
            sys->is_paused_flag = false;
            break;
        case SDLK_1: case SDLK_2: case SDLK_3: case SDLK_4: case SDLK_q: 
            case SDLK_w: case SDLK_e: case SDLK_r: case SDLK_a: case SDLK_s:
            case SDLK_d: case SDLK_f: case SDLK_z: case SDLK_x: case SDLK_c: case SDLK_v:
            spdlog::info("Key {} was pressed or released!", mapKeys[event.key.keysym.sym]);

            if (event.type == SDL_KEYUP) sys->keyboard[mapKeys[event.key.keysym.sym]] = 0;
            if (event.type == SDL_KEYDOWN) {
                if (sys->waiting_for_key) {
                    sys->waiting_for_key = 0;
                    sys->V[sys->waiting_reg] = mapKeys[event.key.keysym.sym];
                }
                sys->keyboard[mapKeys[event.key.keysym.sym]] = 1;
            }
            break;
        }
    }
}
