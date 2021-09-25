//
// Created by ana on 25/09/21.
//

#include <sstream>
#include "Chip8.h"


Chip8::Chip8():
        opcode(0), // Reset current opcode
        memory{0}, // Reset memory
        registers{0}, // Reset registers
        index_register(0), // Reset index register
        pc(0x200), // Program counter starts at 0x200
        stack{0}, // Reset stack
        sp(0), // Reset stack pointer
        key{0}, // Reset key
        gfx{0}, // graphics
        delay_timer(),
        sound_timer()
{
    std::cout << "Hello World!" << std::endl;

    // Clear display
    // Clear registers V0-VF

    // Load fontset
/*    for(int i = 0; i < 80; ++i)
        memory[i] = chip8_fontset[i];*/

    // Reset timers
}

void Chip8::loadGame(const std::string string) {

    std::ifstream file;
    file.open ("rom/" + string + ".c8", std::ios::in | std::ios::binary);

    if(!file.is_open()) {
        std::cout << "Not found!" << std::endl;
        return;
    }

    unsigned i = pc;
    while(!file.eof())
    {
        memory[i] = file.get();
        ++i;
    }
}

void Chip8::emulateCycle() {
    // Fetch opcode
    opcode = memory[pc] << 8 | memory[pc + 1];
    std::cout << std::hex  << opcode << std::endl;
    // Decode opcode
    switch(opcode & 0xF000)
    {
//        // Some opcodes //
//
//        case 0xA000: // ANNN: Sets I to the address NNN
//            // Execute opcode
//            index_register = opcode & 0x0FFF;
//            pc += 2;
//            break;
//
        case OPCODE_0:
            opcode0();
            break;
        case OPCODE_JP:
            pc = opcode & 0x0FFF;
            break;
        case OPCODE_3XKK:
        {
            unsigned x = (opcode & 0x0F00) >> 8;
            unsigned char kk = opcode & 0x00FF;
            if(registers[x] == kk)
                pc += 2;
            else pc += 4;
        }
            break;
        case OPCODE_6XKK:
        {
            unsigned x = (opcode & 0x0F00) >> 8;
            unsigned char kk = opcode & 0x00FF;
            registers[x] = kk;
            pc += 2;
        }
            break;
        case OPCODE_F:
            opcodeF();
            break;

        default:
            std::stringstream ss;
            ss << "unknown opcode: " << std::hex << opcode;
            throw std::runtime_error(ss.str());
    }


    // Update timers
/*    if(delay_timer > 0)
        --delay_timer;

    if(sound_timer > 0)
    {
        if(sound_timer == 1)
            printf("BEEP!\n");
        --sound_timer;
    }*/
}

void Chip8::opcodeF()
{
    switch(opcode & 0xF0FF)
    {
        case OPCODE_FX15:
        {
            unsigned x = (opcode & 0x0F00) >> 8;
            delay_timer = registers[x];
            pc += 2;
        }
            break;

        default:
            std::stringstream ss;
            ss << "unknown opcode: " << std::hex << opcode;
            throw std::runtime_error(ss.str());
    }
}

void Chip8::opcode0() {
    switch(opcode & 0x000F)
    {
        case OPCODE_CLS:
            std::fill_n(gfx, sizeof gfx, 0);
            pc += 2;
            // TODO: drawFlag = true;
            break;

        case OPCODE_RET:
            break;

        default:
            std::stringstream ss;
            ss << "unknown opcode: " << std::hex << opcode;
            throw std::runtime_error(ss.str());
    }
}

