#ifndef CHIP8_T_HPP
#define CHIP8_T_HPP

#define MEMORY_SIZE 4096
#define STACK_SIZE 16
#define NUM_OF_V_REGISTERS 16
#define PC_START 0x200 // 512
#define FONTSET_SIZE 80

#define NUM_KEYS 16
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

#include <stdint.h>
#include <iostream>
#include <cstdio>
#include "spdlog/spdlog.h"

constexpr uint8_t fontset[FONTSET_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80, // F
};

class Chip8 {
public:
    uint8_t ram[MEMORY_SIZE];
    uint16_t stack[STACK_SIZE];

    // registers:
    uint8_t V[NUM_OF_V_REGISTERS];
    uint16_t I;
    // Delay Timer Register
    uint8_t DT;
    // Sound Timer Register
    uint8_t ST;
    // Program Counter
    uint16_t PC; 
    // Stack Pointer
    uint8_t SP;

    uint16_t current_op;

    // screen
    uint8_t screen[SCREEN_WIDTH][SCREEN_HEIGHT];

    // keyboard
    uint8_t keyboard[NUM_KEYS];

    // Status Flags associated with Fx0A.
    uint8_t waiting_for_key;
    uint8_t waiting_reg;

    // Status Flags
    uint8_t is_running_flag;
    uint8_t is_paused_flag;
    uint8_t draw_flag;

    // misc
    const char* rom_filepath;

    // Chip8 initializer
    Chip8() {
        init_system();
    }

    void init_system() {
        // clear RAM
        for (int i=0; i < MEMORY_SIZE; i++) {
            ram[i] = 0;
        }
        
        // load fontset
        for (int i = 0; i < FONTSET_SIZE; i++) {
            ram[i] = fontset[i];
        }

        // clear registers
        for (int i=0; i < NUM_OF_V_REGISTERS; i++) {
            V[i] = 0;
        }
        I = 0;
        PC = PC_START;
        DT = 0;
        ST = 0;
        
        // clear stack
        for (int i=0; i < STACK_SIZE; i++) {
            stack[i] = 0;
        }
        SP = 0;

        // clear screen
        for (int y=0; y < SCREEN_HEIGHT; y++) {
            for (int x=0; x < SCREEN_WIDTH; x++) {
                screen[x][y] = 0;
            }
        }

        // clear keyboard inputs
        for (int i=0; i < 0xF; i++) {
            keyboard[i] = 0;
        }

        is_running_flag = 1;
        is_paused_flag = 0;
        draw_flag = 1;
        
        waiting_for_key = 0;
        waiting_reg = 0;
    }
    
    // Must set rom_filepath before calling.
    void load_rom() {
        FILE* rom = fopen(rom_filepath, "rb");
        if (rom == NULL) {
            // log error
            exit(EXIT_FAILURE);
        }
        
        // get file size
        fseek(rom, 0L, SEEK_END);
        long int rom_size = ftell(rom);
        long int max_rom_size = MEMORY_SIZE - PC_START;
        fseek(rom, 0, SEEK_SET);

        if (rom_size > max_rom_size) {
            spdlog::error("ROM Size greater than allowed memory {}", max_rom_size);
            exit(EXIT_FAILURE);
        }
        uint8_t* buffer = (uint8_t *)malloc(rom_size * sizeof(uint8_t));
        
        // TODO: check for unsuccessful read & error
        fread(buffer, sizeof(uint8_t), rom_size, rom);

        for (int i = 0; i < rom_size; i++) {
            ram[i + PC_START] = buffer[i];
        }
        
        fclose(rom);
        free(buffer);
    }
};

#endif
