//
// Created by Adebayo  on 09/09/2023.
//

#include <stdint.h>

#ifndef VIRTUAL_MACHINE_INSTRUCTION_H
#define VIRTUAL_MACHINE_INSTRUCTION_H

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

enum Flag
{
    FL_POS = 1 << 0, /* P */
    FL_ZRO = 1 << 1, /* Z */
    FL_NEG = 1 << 2, /* N */
} ;
void update_flags(uint16_t r);
uint16_t sign_extend(uint16_t x, int bit_count);
uint16_t zero_extend(uint16_t vector, int i);

void op_br(uint16_t instruction );
void op_add(uint16_t instruction );
void op_ld( uint16_t instruction );
void op_st( uint16_t instruction );
void op_jsr(uint16_t instruction );
void op_and(uint16_t instruction );
void op_ldr( uint16_t instruction );
void op_str( uint16_t instruction );
void op_rti( uint16_t instruction );
void op_not( uint16_t instruction );
void op_ldi( uint16_t instruction );
void op_sti( uint16_t instruction );
void op_jmp( uint16_t instruction );
void op_res( uint16_t instruction );
void op_lea( uint16_t instruction );

/**
 * </br>
 * <p>First R7 is loaded with the incremented PC. (This enables a return to the instruction physically following the TRAP
 * instruction in the original program after the service routine has completed execution.).
 * Then the PC is loaded with the starting address of the system call specified by trapvector8.
 * The starting address is contained in the memory location whose address is obtained by zero-extending trapvector8 to
 * 16 bits. </p>
 * See https://www.jmeiners.com/lc3-vm/supplies/lc3-isa.pdf
 *
 * @param instruction lc3 instruction.
 */
void op_trap( uint16_t instruction );
#endif //VIRTUAL_MACHINE_INSTRUCTION_H
