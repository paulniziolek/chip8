// testing main cpp file
#include "chip8.hpp"
#include "screen.hpp"
#include "keyboard.hpp"

int main(int argc, char *argv[]) {
    Chip8 user_chip8;
    argv[1] = "roms/ultimatetictactoe.ch8"; // temp, just for testing
    argv[2] = "log"; // temp, just for testing

    if (argv[2] != NULL && strcmp(argv[2], "log")==0) {
        spdlog::set_level(spdlog::level::debug);
    }

    const char* rompath = argv[1];
    if (rompath == NULL) {
        spdlog::error("ROM Path not specified.");
        spdlog::warn("Usage: ./chip8 romdir/rom");
        exit(EXIT_FAILURE);
    }

    load_rom(&user_chip8, rompath);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        spdlog::error("SDL fails to initialize: {}", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    // TODO: Implement resolution scaling in window & renderer
    // TODO: Change resolution scaling based on config file
    SDL_Window* window = SDL_CreateWindow("Chip8 Emulator", 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        SCREEN_WIDTH * SCALE_X, 
                                        SCREEN_HEIGHT * SCALE_Y, 
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);

    if (window == nullptr) {
        spdlog::error("SDL failed to create window: {}", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        spdlog::error("SDL failed to create renderer: {}", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    SDL_RenderSetScale(renderer, (float) SCALE_X, (float) SCALE_Y);

    SDL_RenderPresent(renderer);

    // TODO: CPU clockcycle debugging here
    
    while(user_chip8.is_running_flag) {
        execute_instruction(&user_chip8);

        user_chip8.screen[15][15] = 1; // test
        if (user_chip8.draw_flag) {
            drawScreen(&user_chip8, renderer);
        }

        SDL_Event event;
        process_user_input(&user_chip8);
        while (user_chip8.is_paused_flag && user_chip8.is_running_flag) {
            process_user_input(&user_chip8);
        }

    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Finished running";
}