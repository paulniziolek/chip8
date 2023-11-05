#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "chip8_t.hpp"

// instructions
void cls(Chip8* sys);               // 00E0
void ret(Chip8* sys);               // 00EE
void jp(Chip8* sys);                // 1nnn
void call_subroutine(Chip8* sys);   // 2nnn
void se_Vx_kk(Chip8* sys);          // 3xkk
void sne_Vx_kk(Chip8* sys);         // 4xkk
void se_Vx_Vy(Chip8* sys);          // 5xy0
void ld_Vx_kk(Chip8* sys);          // 6xkk
void add_Vx_kk(Chip8* sys);         // 7xkk
void ld_Vx_Vy(Chip8* sys);          // 8xy0
void set_Vx_or_Vy(Chip8* sys);      // 8xy1
void set_Vx_and_Vy(Chip8* sys);     // 8xy2
void set_Vx_xor_Vy(Chip8* sys);     // 8xy3
void add_Vx_Vy(Chip8* sys);         // 8xy4
void sub_Vx_Vy(Chip8* sys);         // 8xy5
void shr_Vx_Vy(Chip8* sys);         // 8xy6
void subn_Vx_Vy(Chip8* sys);        // 8xy7
void shl(Chip8* sys);               // 8xyE
void sne_Vx_Vy(Chip8* sys);         // 9xy0
void set_i(Chip8* sys);             // Annn
void jp_V0(Chip8* sys);             // Bnnn
void set_Vx_rand(Chip8* sys);       // Cxkk
void draw(Chip8* sys);              // Dxyn
void skp(Chip8* sys);               // Ex9E
void skpn(Chip8* sys);              // ExA1
void ld_DT_Vx(Chip8* sys);          // Fx07
void set_K_Vx(Chip8* sys);          // Fx0A
void set_DT_Vx(Chip8* sys);         // Fx15
void set_ST_Vx(Chip8* sys);         // Fx18
void add_I_Vx(Chip8* sys);          // Fx1E
void set_I_S(Chip8* sys);           // Fx29      
void ld_B_Vx(Chip8* sys);           // Fx33
void ld_I_Vk(Chip8* sys);           // Fx55
void ld_Vk_I(Chip8* sys);           // Fx65

#endif
