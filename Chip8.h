//
// Created by ana on 25/09/21.
//

#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

#include <iostream>
#include <fstream>
#include "utils.h"

//! (0nnn) Jump to a machine code routine at nnn
#define OPCODE_SYS 0x0000
//! (2nnn) Call subroutine at nnn.
//! The interpreter increments the stack pointer
//! then puts the current PC on the top of the stack. The PC is then set to nnn.
#define OPCODE_CALL 0x2000


//! 0x0 opcodes
#define OPCODE_0 0x0000
//! Clear display
#define OPCODE_CLS 0x0000
//! Return from subroutine
#define OPCODE_RET 0x000E

//! (1nnn) Jump to location nnn
#define OPCODE_JP  0x1000
//! Skip next instruction if Vx = kk.
//! The interpreter compares register Vx to kk,
//! and if they are equal, increments the program counter by 2.
#define OPCODE_3XKK 0x3000
//! The interpreter puts the value kk into register Vx.
#define OPCODE_6XKK 0x6000

//! 0xF opcodes
#define OPCODE_F 0xF000
//! 0xF015 Set delay timer = Vx. DT is set equal to the value of Vx.
#define OPCODE_FX15 0xF015


class Chip8 {

    // current opcode (instruction)
    unsigned short opcode;

    // memory for chip 8
    unsigned char memory[4096];

    // cpu registers (V)
    unsigned char registers[16];

    // index register (I)
    unsigned short index_register;

    // program counter (memory position)
    unsigned short pc;

    // stack space for 16 16-bit addresses.
    unsigned short stack[16];

    // stack pointer is used to point to the top of the Stack space.
    unsigned short sp;

    // HEX based keypad
    unsigned char key[16];

    unsigned char gfx[64 * 32];

    unsigned char delay_timer;

    unsigned char sound_timer;

public:
    Chip8();

    void loadGame(const std::string string);

    void emulateCycle();

    void opcodeF();

    void opcode0();
};


#endif //CHIP8_CHIP8_H
