//
// Created by Adebayo  on 06/09/2023.
//

#ifndef VIRTUAL_MACHINE_MEMORY_H
#define VIRTUAL_MACHINE_MEMORY_H

#include <stdint.h>

#define MEMORY_MAX (1 << 16)

uint16_t memory[MEMORY_MAX];

uint16_t mem_read(uint16_t i);
void mem_write(uint16_t addr, uint16_t sr);

#endif //VIRTUAL_MACHINE_MEMORY_H
