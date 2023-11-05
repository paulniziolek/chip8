#include "chip8.hpp"

void load_rom(Chip8* sys, const char* rom_filepath) {
    FILE* rom = fopen(rom_filepath, "rb");
    if (rom == NULL) {
        // log error
        exit(EXIT_FAILURE);
    }
    
    // get file size
    fseek(rom, 0L, SEEK_END);
    long int rom_size = ftell(rom);
    fseek(rom, 0, SEEK_SET);

    if (rom_size > MEMORY_SIZE - PC_START) {
        // log error
        exit(EXIT_FAILURE);
    }
    uint8_t* buffer = (uint8_t *)malloc(rom_size * sizeof(uint8_t));
    
    // TODO: check for unsuccessful read & error
    fread(buffer, sizeof(uint8_t), rom_size, rom);

    for (int i = 0; i < rom_size; i++) {
        sys->ram[i + PC_START] = buffer[i];
    }
    
    fclose(rom);
    free(buffer);
}

void execute_instruction(Chip8* sys) {
    sys->current_op = (sys->ram[sys->PC] << 8) | (sys->ram[sys->PC+1]);
    

}

void printMemory(Chip8* sys) {
    for (int i = 0; i < 0x200; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << sys->ram[i*8+j];
        }
        std::cout << '\n';
    }
}