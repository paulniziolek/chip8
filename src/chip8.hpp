#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <iostream>
#include <cstdio>

#include "chip8_t.hpp"

void init_chip8(Chip8* sys);
void load_rom(Chip8* sys, const char* rom_filepath);
void execute_instruction(Chip8* sys);


#endif
