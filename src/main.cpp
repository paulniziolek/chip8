// testing main cpp file
#include "chip8.hpp"
#include "screen.hpp"

int main(int argc, char *argv[]) {
    Chip8 user_chip8;
    argv[1] = "roms/ultimatetictactoe.ch8"; // temp, just for testing
    //argv[2] = "log"; // temp, just for testing

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
                                        SCREEN_WIDTH, 
                                        SCREEN_HEIGHT, 
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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);

    // TODO: CPU clockcycle debugging here
    
    while(user_chip8.is_running_flag) {

        execute_instruction(&user_chip8);

        SDL_Event event;
        SDL_PollEvent(&event);

        // TODO: process_user_input()
        while (user_chip8.is_paused_flag) {
            // process_user_input
        }

        
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Finished running";
}