// testing main cpp file
#include "chip8.hpp"
#include "screen.hpp"
#include "keyboard.hpp"

int main(int argc, char *argv[]) {
    Chip8 user_chip8;
    argv[1] = "roms/ultimatetictactoe.ch8"; // temp, just for testing
    argv[1] = "roms/heart_monitor.ch8";
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
    
    // TODO: Change resolution scaling based on config file
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(&window, &renderer);

    // TODO: CPU clockcycle debugging here
    
    while(user_chip8.is_running_flag) {
        execute_instruction(&user_chip8);

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