
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hardware/hardware.h"


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
//    if(addr > (uint16_t)MEMORY_MAX){
//        exit(EXIT_FAILURE);
//    }
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
        uint16_t instr = mem_read(reg[R_PC]++);
        uint16_t op = instr >> 12;
        switch(op){
            case OP_ADD:{
                /* destination register (DR) */
                uint16_t  r0 = (instr >> 9) & 0x7;
                /* first operand (SR1) */
                uint16_t  r1 = (instr >> 6) & 0x7;
                /* whether we are in immediate mode */
                uint16_t imm_flag = (instr >> 5) & 0x1;

                if(imm_flag){
                    uint16_t imm5 = sign_extend(instr & 0x1F, 5);
                    reg[r0] = reg[r1] + imm5;
                }
                else
                {
                    uint16_t  r2 = instr & 0x7;
                    reg[r0] = reg[r1] + reg[r2];
                }

                update_flags(r0);
                 }
                break;
            case OP_AND:{
                /* destination register */
                uint16_t r0 = (instr >> 9) & 0x7 ;
                /* source register 1 */
                uint16_t r1 = (instr >> 6) & 0x7;
                uint16_t imm_flag = (instr >> 5) & 0x1;
                if(imm_flag){
                    uint16_t  imm5 = sign_extend(instr & 0x1F, 5);
                    reg[r0] = reg[r1] & imm5;
                }else{
                    uint16_t r2 = instr & 0x7;
                    reg[r0] = reg[r1] & reg[r2];
                }
                update_flags(r0);
            }
                break;
            case OP_NOT:{
                uint16_t r0 = (instr >> 9) & 0x7;
                uint16_t r1 = (instr >> 6) & 0x7;
                reg[r0] = ~reg[r1];
                update_flags(r0);
            }
                break;
            case OP_BR:{

//                {
//                    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
//                    uint16_t cond_flag = (instr >> 9) & 0x7;
//                    if (cond_flag & reg[R_COND])
//                    {
//                        reg[R_PC] += pc_offset;
//                    }
//                }
                uint16_t n = (instr >> 11) & 0x1;
                uint16_t z = (instr >> 10) & 0x1;
                uint16_t p = (instr >> 9) & 0x1;
                if(n || z || p){
                    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
                    reg[R_PC] = reg[R_PC] + pc_offset;
                }
            }
                break;
            case OP_JMP:{
                uint16_t base_r = (instr >> 6) & 0x7;
                reg[R_PC] = reg[base_r];
//                if(base_r == 0x7){
//                    reg[R_PC] = reg[R_R7];
//                }else{
//                    reg[R_PC] = reg[base_r];
//                }
            }
                break;
            case OP_JSR:{
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
                break;
            case OP_LD:{
                uint16_t r0 = (instr  >> 9) & 0x7;
                uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
                reg[r0] = mem_read(reg[R_PC] + pc_offset);
                update_flags(r0);
            }
                break;
            case OP_LDI:{
                /* destination register */
                uint16_t r0 = (instr >> 9) & 0x7;
                /* PCoffset9 */
                uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
                /* add pc_offset to the current PC,
                 * look at that memory location to get the final address */
                reg[r0] = mem_read(mem_read(reg[R_PC] + pc_offset ));

                update_flags(r0);
            }
                break;
            case OP_LDR:{
                uint16_t r0 = (instr >> 9) & 0x7;
                uint16_t base_r = (instr >> 6) & 0x7;
                uint16_t offset = sign_extend(instr & 0x3F, 6);
                reg[r0] = mem_read(reg[base_r] + offset);
                update_flags(r0);
            }
                break;
            case OP_LEA:{
                uint16_t r0 = instr >> 9;
                uint16_t offset = sign_extend(instr & 0x1FF, 9);
                reg[r0] = reg[R_PC] + offset;
                update_flags(r0);
            }
                break;
            case OP_ST:{
                uint16_t  r0 = (instr >> 9) & 0x7;
                uint16_t offset = sign_extend(instr & 0x1FF, 9);
                mem_write(reg[R_PC] + offset, reg[r0]);

            }
                break;
            case OP_STI:{
                uint16_t  r0 = (instr >> 9) & 0x7;
                uint16_t offset = sign_extend(instr & 0x1FF, 9);
                mem_write(mem_read(reg[R_PC] + offset), reg[r0]);
            }
                break;
            case OP_STR:{
                uint16_t r0 = (instr >> 9) & 0x7;
                uint16_t base_r = (instr >> 6 ) & 0x7;
                uint16_t offset = sign_extend(instr & 0x3F, 6);
                mem_write(reg[base_r] + offset, r0);
            }
                break;
            case OP_TRAP:{
                uint16_t trap_vector = instr & 0xFF;
                reg[R_R7] = reg[R_PC];
                reg[R_PC] = mem_read(zero_extend(trap_vector, 8));
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
