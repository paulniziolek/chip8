#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <iostream>
#include <cstdio>
#include "spdlog/spdlog.h"

#include "chip8_t.hpp"
#include "instructions.hpp"
#include "screen.hpp"

#define CPU_CLOCK_SPEED 500
#define FRAME_RATE 60
#define TIMER_RATE 60

void updateTimers(Chip8* sys);
void execute_instruction(Chip8* sys);


#endif
