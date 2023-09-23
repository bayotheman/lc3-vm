//
// Created by Adebayo  on 06/09/2023.
//

#ifndef VIRTUAL_MACHINE_REGISTER_H
#define VIRTUAL_MACHINE_REGISTER_H

#include <stdint.h>

enum{
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC, /* program counter */
    R_COND,
    R_COUNT
};

uint16_t reg[R_COUNT];




#endif //VIRTUAL_MACHINE_REGISTER_H
