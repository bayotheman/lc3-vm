cmake_minimum_required(VERSION 3.24)
project(virtual_machine C)

set(CMAKE_C_STANDARD 11)

add_executable(virtual_machine main.c hardware/memory.h hardware/register.h hardware/hardware.h lc3.c hardware/instruction.h hardware/instruction.c)
