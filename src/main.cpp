// testing main cpp file
#include "chip8.hpp"
#include "screen.hpp"

int main(int argc, char *argv[]) {
    Chip8 user_chip8;

    // TODO: init logger setup here
    
    // TODO: load rom here
    argv[1] = "roms/ultimatetictactoe.ch8"; // temp, just for testing
    const char* rompath = argv[1];
    if (rompath == NULL) {
        // log out usage
        exit(EXIT_FAILURE);
    }
    load_rom(&user_chip8, rompath);

    // TODO: CPU clockcycle debugging here
    
    while(user_chip8.is_running_flag) {

        execute_instruction(&user_chip8);

        // TODO: process_user_input()
        while (user_chip8.is_paused_flag) {
            // process_user_input
        }
        break;
    }
    std::cout << "Finished running";

}