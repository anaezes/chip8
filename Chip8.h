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

//! 0x3000 Skip next instruction if Vx = kk.
//! The interpreter compares register Vx to kk,
//! and if they are equal, increments the program counter by 2.
#define OPCODE_3XKK 0x3000

//! 0x4000 Skip next instruction if Vx != kk. The interpreter compares
//! register Vx to kk, and if they are not equal, increments the program counter by 2.
#define OPCODE_4XKK 0x4000

//! 0x5000 Skip next instruction if Vx = Vy. The interpreter compares register Vx
//! to register Vy, and if they are equal, increments the program counter by 2.
#define OPCODE_5XY0 0x5000

//! 0x6000 The interpreter puts the value kk into register Vx.
#define OPCODE_6XKK 0x6000

//! 0x7000 Set Vx = Vx + kk.
//! Adds the value kk to the value of register Vx, then stores the result in Vx.
#define OPCODE_7XKK 0x7000

//! 0x8 opcodes
#define OPCODE_8 0x8000
//! 0x8000 Set Vx = Vy. Stores the value of register Vy in register Vx.
#define OPCODE_8XY0 0x0000
//! 0x8001 Set Vx = Vx OR Vy.
#define OPCODE_8XY1 0x0001
//! 0x8002 Set Vx = Vx AND Vy.
#define OPCODE_8XY2 0x0002
//! 0x8003 Set Vx = Vx XOR Vy.
#define OPCODE_8XY3 0x0003
//! 0x8004 Set Vx = Vx + Vy, set VF = carry.
#define OPCODE_8XY4 0x0004
//! 0x8005 Set Vx = Vx - Vy, set VF = NOT borrow.
#define OPCODE_8XY5 0x0005
//! 0x8006 Set Vx = Vx SHR 1.
#define OPCODE_8XY6 0x0006
//! 0x8007 Set Vx = Vy - Vx, set VF = NOT borrow.
#define OPCODE_8XY7 0x0007
//! 0x800E Set Vx = Vx SHL 1.
#define OPCODE_8XYE 0x000E

//! 0x9000  Skip next instruction if Vx != Vy.
#define OPCODE_9XYK 0x9000

//! 0xB000  Jump to location nnn + V0.
#define OPCODE_BNNN 0xB000

//! 0xC000  Set Vx = random byte AND kk.
#define OPCODE_CXKK 0xC000

//! 0xD000 Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
#define OPCODE_DXYN 0xD000

//! 0xF opcodes
#define OPCODE_F 0xF000
//! 0xF015 Set delay timer = Vx. DT is set equal to the value of Vx.
#define OPCODE_FX15 0x0015
//! 0xF029 Set I = location of sprite for digit Vx.
//! The value of I is set to the location for the hexadecimal sprite corresponding
//! to the value of Vx. See section 2.4, Display, for more information on the Chip-8
//! hexadecimal font.
#define OPCODE_FX29 0x0029


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

    void opcode8();
};


#endif //CHIP8_CHIP8_H
