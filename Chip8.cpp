//
// Created by ana on 25/09/21.
//

#include <sstream>
#include <stdlib.h>
#include <time.h>
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
    srand (time(NULL));
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
            if(registers[x] == kk) pc += 4;
            else pc += 2;
        }
            break;
        case OPCODE_4XKK:
        {
            unsigned x = (opcode & 0x0F00) >> 8;
            unsigned char kk = opcode & 0x00FF;
            if(registers[x] != kk) pc += 4;
            else pc += 2;
        }
            break;
        case OPCODE_5XY0:
        {
            unsigned x = (opcode & 0x0F00) >> 8;
            unsigned y = (opcode & 0x00F0) >> 4;
            if(registers[x] == registers[y]) pc += 4;
            else pc += 2;
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
        case OPCODE_7XKK:
        {
            unsigned x = (opcode & 0x0F00) >> 8;
            unsigned char kk = opcode & 0x00FF;
            registers[x] = registers[x] + kk;
            pc += 2;
        }
            break;
        case OPCODE_8:
            opcode8();
            break;
        case OPCODE_9XYK:
        {
            unsigned x = (opcode & 0x0F00) >> 8;
            unsigned y = (opcode & 0x00F0) >> 4;
            if(registers[x] != registers[y]) pc += 4;
            else pc += 2;
        }
            break;
        case OPCODE_BNNN:
            pc = (opcode & 0x0FFF) + registers[0];
            break;
        case OPCODE_CXKK:
        {
            unsigned n = rand() % 256;
            unsigned char kk = opcode & 0x00FF;
            unsigned x = (opcode & 0x0F00) >> 8;
            registers[x] = n & kk;
            pc += 2;
        }
            break;
        case OPCODE_DXYN:
            // TODO: Display n-byte sprite starting at memory location I at (Vx, Vy),
            //  set VF = collision.
            pc += 2;
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
    switch(opcode & 0x00FF)
    {
        case OPCODE_FX15:
        {
            unsigned x = (opcode & 0x0F00) >> 8;
            delay_timer = registers[x];
            pc += 2;
        }
            break;
        case OPCODE_FX29:
        {
            unsigned x = (opcode & 0x0F00) >> 8;
            index_register = registers[x] * 0x5;
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
            --sp;
            pc = stack[sp];
            sp -= 1;
            break;

        default:
            std::stringstream ss;
            ss << "unknown opcode: " << std::hex << opcode;
            throw std::runtime_error(ss.str());
    }
}

void Chip8::opcode8() {

    unsigned x = (opcode & 0x0F00) >> 8;
    unsigned y = (opcode & 0x00F0) >> 4;
    unsigned char vx = registers[x];
    unsigned char vy = registers[y];

    switch(opcode & 0x000F)
    {
        case OPCODE_8XY0:
        {
            registers[x] = registers[y];
            pc += 2;
        }
            break;
        case OPCODE_8XY1:
        {
            registers[x] = vx | vy;
            pc += 2;
        }
            break;
        case OPCODE_8XY2:
        {
            registers[x] = vx & vy;
            pc += 2;
        }
            break;
        case OPCODE_8XY3:
        {
            registers[x] = vx ^ vy;
            pc += 2;
        }
            break;
        case OPCODE_8XY4:
        {
            registers[x] = vx + vy;
            if(vy + vx > 0xFF) registers[0xF] = 1;
            else registers[0xF] = 0;
            pc += 2;
        }
            break;
        case OPCODE_8XY5:
        {
            registers[x] = vx - vy;
            if(vx > vy) registers[0xF] = 1;
            else registers[0xF] = 0;
            pc += 2;
        }
            break;
        case OPCODE_8XY6:
        {
           if(vx & 0x1 == 1) registers[0xF] = 1;
           else registers[0xF] = 0;
            registers[x] /= 2;
            pc += 2;
        }
            break;
        case OPCODE_8XY7:
        {
            registers[x] = vy - vx;
            if(vy > vx) registers[0xF] = 1;
            else registers[0xF] = 0;
            pc += 2;
        }
            break;
        case OPCODE_8XYE:
        {
            registers[0xF] = vx >> 7;
            registers[x] *= 2;
            pc += 2;
        }
            break;
        default:
            std::stringstream ss;
            ss << "unknown opcode: " << std::hex << opcode;
            throw std::runtime_error(ss.str());
    }
}

