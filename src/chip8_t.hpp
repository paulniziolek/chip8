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
    // ...

    // Status Flags
    uint8_t is_running_flag;
    uint8_t is_paused_flag;
    uint8_t draw_flag;

    // Chip8 initializer
    Chip8() {
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

        is_running_flag = 1;
        is_paused_flag = 0;
        draw_flag = 1;
    }
};

#endif
