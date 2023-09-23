
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "component/instruction.h"
#include "component/memory.h"
#include "component/register.h"
#include "component/trap.h"


uint16_t mem_read(uint16_t i) {
    return 0;
}

void update_flags(uint16_t r)
{
    if (reg[r] == 0)
    {
        reg[R_COND] = FL_ZRO;
    }
    else if (reg[r] >> 15) /* a 1 in the left-most bit indicates negative */
    {
        reg[R_COND] = FL_NEG;
    }
    else
    {
        reg[R_COND] = FL_POS;
    }
}

uint16_t sign_extend(uint16_t x, int bit_count){
    if((x >> (bit_count - 1)) & 1){
        x |= (0xFFFF << bit_count);
    }
    return x;
}

bool read_image(const char *string) {
    return 1;
}

void mem_write(uint16_t addr, uint16_t sr) {
    memory[addr] = sr;
}

uint16_t zero_extend(uint16_t vector, int i) {
    return 0;
}

int main(int argc, const char* argv[]) {

    if(argc < 2){
        /* show usage string */
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }

    for (int j = 1; j < argc; ++j){
        if(!read_image(argv[j])){
            printf("failed to load image: %s\n", argv[j]);
            exit(1);
        }
    }

    /* since exactly one condition flag should be set at any given time, set the Z flag */
    reg[R_COND] = FL_ZRO;

    /* set the PC to starting position */
    /* 0x3000 is the default */
    enum{ PC_START = 0x3000 };
    reg[R_PC] = PC_START;

    int running = 1;

    while(running){
        uint16_t instruction = mem_read(reg[R_PC]++);
        uint16_t opcode = instruction >> 12;
        switch(opcode){
            case OP_ADD:
                op_add(&instruction);
                break;
            case OP_AND:
                op_and(&instruction);
                break;
            case OP_NOT:
                op_not(&instruction);
                break;
            case OP_BR:
                op_br(&instruction);
                break;
            case OP_JMP:
                op_jmp(&instruction);
                break;
            case OP_JSR:
                op_jsr(&instruction);
                break;
            case OP_LD:
                op_ld(&instruction);
                break;
            case OP_LDI:
                op_ldi(&instruction);
                break;
            case OP_LDR:
                op_ldr(&instruction);
                break;
            case OP_LEA:
                op_lea(&instruction);
                break;
            case OP_ST:
                op_st(&instruction);
                break;
            case OP_STI:
                op_sti(&instruction);
                break;
            case OP_STR:
                op_str(&instruction);
                break;
            case OP_TRAP:{
                uint16_t trap_vector = instruction & 0xFF;
                reg[R_R7] = reg[R_PC];
                switch(trap_vector){
                    case TRAP_GETC:{
                        reg[R_R0] = (uint16_t) getchar();
                        update_flags(R_R0);
                    }
                        break;
                    case TRAP_OUT:{
//                        putchar(((char)reg[R_R0])& 0x7F);
                        putchar((char)reg[R_R0]);
                        fflush(stdout);
                    }
                        break;
                    case TRAP_PUTS:
                    {
                        /* one char per word */
                        uint16_t* c = memory + reg[R_R0];
                        while(*c){
//                            putc((char)*c, stdout);
                            putchar((char)*c);
                            ++c;
                        }
                        fflush(stdout);
                    }
                        break;
                    case TRAP_IN:{

                    }
                        break;
                    case TRAP_PUTSP:
                        break;
                    case TRAP_HALT:
                        break;
                }
            }
                break;
            case OP_RES:
            case OP_RTI:
                abort();
            default:
                break;
        }

    }
    return 0;
}
