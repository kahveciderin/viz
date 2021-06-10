#include "../architecture-dependent.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
uint16_t *init_memspace() {
    return malloc(sizeof(uint16_t) * 0x10000);
}
void load_program(uint16_t *memspace) {
    printf("Enter VIZ program path: ");
    char filepath[128];
    scanf("%127s", filepath);
    FILE *infile = fopen(filepath, "r");
    fread(memspace, sizeof(uint16_t), 0x10000, infile);
    fclose(infile);
}
uint16_t in(uint16_t port) {
    uint16_t out = 0;
    if (port == 0) {
        scanf("%c", &out);
    } else {
        printf("PORT %d INPUT: ", port);
        scanf("%ud", &out);
    }
    return out;
}
void out(uint16_t data, uint16_t port) {
    if (port == 0) {
        putchar(data);
    } else {
        printf("PORT %d DATA %x\n", port, data);
    }
}
uint16_t pow16(uint16_t x, uint16_t e) {
    return pow(x, e);
}