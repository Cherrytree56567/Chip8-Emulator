/*
    Copyright (c) 2024-2024 Ronit D'silva

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    REFERENCES:
    https://austinmorlan.com/posts/chip8_emulator/
    http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

*/
#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdint>
#include <functional>
#include "Logging.h"

struct Range {
    Range(size_t s, size_t e) : start(s), end(e) {}
    size_t start;
    size_t end;
};

class Chip8 {
    public:
        Chip8();

        void LoadROM(char const* filename);
        void Loop();

        void OP_00E0();
        void OP_00EE();
        void OP_1nnn();
        void OP_2nnn();
        void OP_3xkk();
        void OP_4xkk();

    private:
        /*
         * Memory
        */
        uint8_t Memory[4096]; // 4K of Memory
        Range InterpreterMemory{0x000, 0x1ff}; // Originally reserved for the CHIP-8 interpreter
        Range FontMemory{0x050, 0x0A0}; // Storage space for the 16 built-in characters
        Range ProgramMemory{0x200, 0xFFF}; // Instructions from the ROM will be stored starting at 0x200
        uint8_t VideoMemory[32][64];

        /*
         * Registers
        */
        uint8_t Registers[16];
        uint16_t IndexRegister;
        uint16_t ProgramCounter = ProgramMemory.start;
        uint8_t StackPointer;
        uint16_t opcode;

        /*
         * Timers
        */
        uint8_t DelayTimer;
        uint8_t SoundTimer;

        /*
         * Keyboards
        */
        uint8_t keyboard[16];

        /*
         * Stack
        */
        uint16_t stack[16];

        std::vector<std::function<void()>> FuncTable;
        std::vector<std::function<void()>> FuncTable0;
        std::vector<std::function<void()>> FuncTable8;
        std::vector<std::function<void()>> FuncTableE;
        std::vector<std::function<void()>> FuncTableF;

        Logging log;
};