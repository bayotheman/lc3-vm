cmake_minimum_required(VERSION 3.24)
project(virtual_machine C)

set(CMAKE_C_STANDARD 11)

add_executable(virtual_machine vm.c hardware/memory.h hardware/register.h hardware/hardware.h hardware/instruction.h hardware/instruction.c hardware/trap.c hardware/trap.h)
