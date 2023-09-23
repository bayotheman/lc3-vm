//
// Created by Adebayo  on 06/09/2023.
//

#ifndef VIRTUAL_MACHINE_HARDWARE_H
#define VIRTUAL_MACHINE_HARDWARE_H
#include <stdint.h>


/**
 * Based on the LC-3 architecture
 */



#define MEMORY_MAX (1 << 16)
uint16_t memory[MEMORY_MAX];

/* R_R0 to R_R7 are general purpose registers */
enum Registers {
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

/**
 * Instruction set
 */
enum Opcodes{
    OP_BR = 0,  /* branch */
    OP_ADD,     /* add */
    OP_LD,      /* load */
    OP_ST,      /* store */
    OP_JSR,     /* jump register */
    OP_AND,     /* bitwise and */
    OP_LDR,     /* load register */
    OP_STR,     /* store register */
    OP_RTI,     /* unused */
    OP_NOT,     /* bitwise not */
    OP_LDI,     /* load indirect */
    OP_STI,     /* store indirect */
    OP_JMP,     /* jump */
    OP_RES,    /* reserved (unused) */
    OP_LEA,    /* load effective address */
    OP_TRAP    /* execute trap */

};

/* Condition flags */
enum Flags{
    FL_POS = 1 << 0, /* P */
    FL_ZRO = 1 << 1, /* Z */
    FL_NEG = 1 << 2, /* N */
};

#endif //VIRTUAL_MACHINE_HARDWARE_H
