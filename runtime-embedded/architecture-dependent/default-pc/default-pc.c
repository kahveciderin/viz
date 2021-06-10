#include "../architecture-dependent.h"
#include <stdint.h>
#include <stdlib.h>
uint16_t *init_memspace() {
    return malloc(sizeof(uint16_t) * 0x10000);
}
void load_program(uint16_t *memspace) {
    
}