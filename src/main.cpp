// testing main cpp file
#include "beep.hpp"
#include "chip8.hpp"
#include "screen.hpp"
#include "keyboard.hpp"

int main(int argc, char *argv[]) {
    Chip8 user_chip8;

    if (argv[2] != NULL && strcmp(argv[2], "log")==0) {
        spdlog::set_level(spdlog::level::debug);
    }

    const char* rompath = argv[1];
    if (rompath == NULL) {
        spdlog::error("ROM Path not specified.");
        spdlog::warn("Usage: ./chip8 romdir/rom");
        exit(EXIT_FAILURE);
    }

    user_chip8.rom_filepath = rompath;
    user_chip8.load_rom();
    
    // TODO: Change resolution scaling based on config file
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(&window, &renderer);

    Beeper beeper;
    if (!init_beeper(&beeper, 440.0f)) {
        spdlog::warn("Failed to init beeper audio: {}", SDL_GetError());
    }
    

    // CPU clock cycle configuration
    const std::chrono::milliseconds frameDuration(1000 / FRAME_RATE);
    const std::chrono::milliseconds clockDuration(1000 / CPU_CLOCK_SPEED);
    const std::chrono::milliseconds timeDuration(1000 / TIMER_RATE);

    auto lastFrameTime = std::chrono::steady_clock::now();
    auto lastClockTime = std::chrono::steady_clock::now();
    auto lastTimerTime = std::chrono::steady_clock::now();
    
    while(user_chip8.is_running_flag) {
        auto currentTime = std::chrono::steady_clock::now();

        process_user_input(&user_chip8);
        while (user_chip8.is_paused_flag && user_chip8.is_running_flag) {
            process_user_input(&user_chip8);
        }

        // Timer Clock updates
        while (currentTime - lastTimerTime > timeDuration) {
            updateTimers(&user_chip8);
            set_beep(&beeper, user_chip8.ST > 0);
            lastTimerTime += timeDuration;
        }

        // CPU Clock updates
        while (currentTime - lastClockTime > clockDuration) {
            if (!user_chip8.waiting_for_key) {
                // If we are waiting for a key, then we don't process instructions. 
                // See Fx0A.
                execute_instruction(&user_chip8);
            }
            lastClockTime += clockDuration;
        }
        
        // Screen Clock updates
        while (currentTime - lastFrameTime > frameDuration) {
            if (user_chip8.draw_flag) {
                drawScreen(&user_chip8, renderer);
                user_chip8.draw_flag = 0;
            }
            lastFrameTime += frameDuration;
        }

    }
    
    shutdown_beeper(&beeper);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Finished running";
}