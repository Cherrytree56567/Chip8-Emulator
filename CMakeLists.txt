cmake_minimum_required(VERSION 3.1...3.29)

set (CMAKE_CXX_STANDARD 20)

project(
  Chip8Emu
  VERSION 1.0
  LANGUAGES CXX)

add_executable(Chip8Emu.elf main.cpp Chip8.cpp)