#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <iostream>
#include <cstdio>
#include "spdlog/spdlog.h"

#include "chip8_t.hpp"
#include "instructions.hpp"
#include "screen.hpp"

void init_chip8(Chip8* sys);
void load_rom(Chip8* sys, const char* rom_filepath);
void updateTimers(Chip8* sys);
void execute_instruction(Chip8* sys);


#endif
