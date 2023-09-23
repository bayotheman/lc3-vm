cmake_minimum_required(VERSION 3.24)
project(virtual_machine C)

set(CMAKE_C_STANDARD 11)

add_executable(virtual_machine vm.c component/memory.h component/register.h component/hardware.h component/instruction.h component/instruction.c component/trap.c component/trap.h)
