//
// Created by Adebayo  on 10/09/2023.
//
#include "instruction.h"
#include "register.h"
#include "memory.h"



void op_br( uint16_t instr ){
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
    uint16_t cond_flag = (instr >> 9) & 0x7;
    if (cond_flag & reg[R_COND])
    {
        reg[R_PC] += pc_offset; //PC-relative addressing mode
    }

}

void op_add( uint16_t instr ){
    uint16_t  dest_r = (instr >> 9) & 0x7;
    uint16_t  src_r1 = (instr >> 6) & 0x7;
    /* whether we are in immediate mode */
    uint16_t imm_flag = (instr >> 5) & 0x1;

    if(imm_flag){
        uint16_t imm5 = sign_extend(instr & 0x1F, 5);
        reg[dest_r] = reg[src_r1] + imm5;
    }
    else
    {
        uint16_t  src_r2 = instr & 0x7;
        reg[dest_r] = reg[src_r1] + reg[src_r2];
    }

    update_flags(dest_r);
}

void op_ld( uint16_t instr){
    uint16_t r0 = (instr  >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
    reg[r0] = mem_read(reg[R_PC] + pc_offset);
    update_flags(r0);
}
void op_st( uint16_t instr ){
    uint16_t  r0 = (instr >> 9) & 0x7;
    uint16_t offset = sign_extend(instr & 0x1FF, 9);
    mem_write(reg[R_PC] + offset, reg[r0]);
}

void op_jsr(uint16_t instr ){
    uint16_t flag = (instr >> 11) & 0x1;
    reg[R_R7] = reg[R_PC];
    if(flag){
        uint16_t pc_offset = sign_extend(instr & 0x7FF, 11);
        reg[R_PC] += pc_offset; /* JSR */
    }else{
        uint16_t base_r = (instr >> 6) & 0x7 ;
        reg[R_PC] = reg[base_r]; /* JSRR */

    }
}
void op_and( uint16_t instr ){
    uint16_t dest_r = (instr >> 9) & 0x7 ;
    uint16_t src_r1 = (instr >> 6) & 0x7;
    uint16_t imm_flag = (instr >> 5) & 0x1;
    if(imm_flag){
        uint16_t  imm5 = sign_extend(instr & 0x1F, 5);
        reg[dest_r] = reg[src_r1] & imm5;
    }else{
        uint16_t src_r2 = instr & 0x7;
        reg[dest_r] = reg[src_r1] & reg[src_r2];
    }
    update_flags(dest_r);
}
void op_ldr( uint16_t instr ){
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t base_r = (instr >> 6) & 0x7;
    uint16_t offset = sign_extend(instr & 0x3F, 6);
    reg[r0] = mem_read(reg[base_r] + offset);
    update_flags(r0);
}
void op_str( uint16_t instr ){
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t base_r = (instr >> 6 ) & 0x7;
    uint16_t offset = sign_extend(instr & 0x3F, 6);
    mem_write(reg[base_r] + offset, r0);
}

void op_rti( uint16_t instruction ){

}

void op_not( uint16_t instr ){
    uint16_t r0 = (instr >> 9) & 0x7;
    uint16_t r1 = (instr >> 6) & 0x7;
    reg[r0] = ~reg[r1];
    update_flags(r0);
}
void op_ldi(uint16_t instr ){
    uint16_t dest_r = (instr >> 9) & 0x7;
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
    reg[dest_r] = mem_read(mem_read(reg[R_PC] + pc_offset ));
    update_flags(dest_r);
}

void op_sti( uint16_t instr){
    uint16_t  src_r = (instr >> 9) & 0x7;
    uint16_t offset = sign_extend(instr & 0x1FF, 9);
    mem_write(mem_read(reg[R_PC] + offset), reg[src_r]);
}

void op_jmp(uint16_t instr ){
    uint16_t base_r = (instr >> 6) & 0x7;
    reg[R_PC] = reg[base_r];
}

void op_res(uint16_t instruction ){}

void op_lea(uint16_t instr ){
    uint16_t dest_r = (instr >> 9) & 0x7;
    uint16_t offset = sign_extend(instr & 0x1FF, 9);
    reg[dest_r] = reg[R_PC] + offset;
    update_flags(dest_r);
}

void op_trap( uint16_t instruction ){
    uint16_t trap_vector = instruction & 0xFF;
    reg[R_R7] = reg[R_PC];
    reg[R_PC] = mem_read(zero_extend(trap_vector, 8));
}
