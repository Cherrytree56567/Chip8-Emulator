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
#include <iostream>
#include <fstream>

struct Range {
    Range(size_t s, size_t e) : start(s), end(e) {}
    size_t start;
    size_t end;
};

const unsigned int FONTSET_SIZE = 80;

uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

class Chip8 {
    public:
        Chip8();

        void LoadROM(char const* filename);

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
        uint16_t PCRegister = ProgramMemory.start;
        uint8_t SPRegister;

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
};