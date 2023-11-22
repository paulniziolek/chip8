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
        sys->ram[i + PC_START] = buffer[i];
    }
    
    fclose(rom);
    free(buffer);
}

void updateTimers(Chip8* sys) {
    if (sys->DT) {
        sys->DT -= 1;
    }
    if (sys->ST) {
        sys->ST -= 1;
    } 
}

void execute_instruction(Chip8* sys) {
    sys->current_op = (sys->ram[sys->PC] << 8) | (sys->ram[sys->PC+1]);
    
    switch(sys->current_op & 0xF000) {
    case 0x0000:
        switch(sys->current_op & 0xFF0F) {
        case 0x0000:
            spdlog::debug("Running opcode 00E0");
            cls(sys);
            break;
        default:
            spdlog::debug("Running opcode 00EE");
            ret(sys);
        }
        break;
    case 0x1000:
        spdlog::debug("Running opcode 1nnn");
        jp(sys);
        break;
    case 0x2000:
        spdlog::debug("Running opcode 2nnn");
        call_subroutine(sys);
        break;
    case 0x3000:
        spdlog::debug("Running opcode 3xkk");
        se_Vx_kk(sys);
        break;
    case 0x4000:
        spdlog::debug("Running opcode 4xkk");
        sne_Vx_kk(sys);
        break;
    case 0x5000:
        spdlog::debug("Running opcode 5xy0");
        se_Vx_Vy(sys);
        break;
    case 0x6000:
        spdlog::debug("Running opcode 6xkk");
        ld_Vx_kk(sys);
        break;
    case 0x7000:
        spdlog::debug("Running opcode 7xkk");
        add_Vx_kk(sys);
        break;
    case 0x8000:
        switch(sys->current_op & 0xF00F) {
        case 0x8000:
            spdlog::debug("Running opcode 8xy0");
            ld_Vx_Vy(sys);
            break;
        case 0x8001:
            spdlog::debug("Running opcode 8xy1");
            set_Vx_or_Vy(sys);
            break;
        case 0x8002:
            spdlog::debug("Running opcode 8xy2");
            set_Vx_and_Vy(sys);
            break;
        case 0x8003:
            spdlog::debug("Running opcode 8xy3");
            set_Vx_xor_Vy(sys);
            break;
        case 0x8004:
            spdlog::debug("Running opcode 8xy4");
            add_Vx_Vy(sys);
            break;
        case 0x8005:
            spdlog::debug("Running opcode 8xy5");
            sub_Vx_Vy(sys);
            break;
        case 0x8006:
            spdlog::debug("Running opcode 8xy6");
            shr_Vx_Vy(sys);
            break;
        case 0x8007:
            spdlog::debug("Running opcode 8xy7");
            subn_Vx_Vy(sys);
            break;
        case 0x800E:
            spdlog::debug("Running opcode 8xyE");
            shl(sys);
            break;
        default:
            spdlog::warn("Invalid opcode found for 0x8xyF: {}", sys->current_op);
        }
        break;
    case 0x9000:
        spdlog::debug("Running opcode 0x9xy0");
        sne_Vx_Vy(sys);
        break;
    case 0xA000:
        spdlog::debug("Running opcode 0xAnnn");
        set_i(sys);
        break;
    case 0xB000:
        spdlog::debug("Running opcode 0xBnnn");
        jp_V0(sys);
        break;
    case 0xC000:
        spdlog::debug("Running opcode 0xCxkk");
        set_Vx_rand(sys);
        break;
    case 0xD000:
        spdlog::debug("Running opcode 0xDxyn");
        draw(sys);
        break;
    case 0xE000:
        switch(sys->current_op & 0xF0FF) {
        case 0xE09E:
            spdlog::debug("Running opcode 0xEx9E");
            skp(sys);
            break;
        case 0xE0A1:
            spdlog::debug("Running opcode 0xExA1");
            skpn(sys);
            break;
        default:
            spdlog::warn("Invalid opcode found for 0xExFF: {}", sys->current_op);
        }
        break;
    case 0xF000:
        switch(sys->current_op & 0xF0FF) {
        case 0xF007:
            spdlog::debug("Running opcode 0xFx07");
            ld_DT_Vx(sys);
            break;
        case 0xF00A:
            spdlog::debug("Running opcode 0xFx0A");
            set_K_Vx(sys);
            break;
        case 0xF015:
            spdlog::debug("Running opcode 0xFx15");
            set_DT_Vx(sys);
            break;
        case 0xF018:
            spdlog::debug("Running opcode 0xFx18");
            set_ST_Vx(sys);
            break;
        case 0xF01E:
            spdlog::debug("Running opcode 0xFx1E");
            add_I_Vx(sys);
            break;
        case 0xF029:
            spdlog::debug("Running opcode 0xFx29");
            set_I_S(sys);
            break;
        case 0xF033:
            spdlog::debug("Running opcode 0xFx33");
            ld_B_Vx(sys);
            break;
        case 0xF055:
            spdlog::debug("Running opcode 0xFx55");
            ld_I_Vk(sys);
            break;
        case 0xF065:
            spdlog::debug("Running opcode 0xFx65");
            ld_Vk_I(sys);
            break;
        default:
            spdlog::warn("Invalid opcode found for 0xFxFF: {}", sys->current_op);
        }
        break;
    }
}

void printMemory(Chip8* sys) {
    for (int i = 0; i < 0x200; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << sys->ram[i*8+j];
        }
        std::cout << '\n';
    }
}