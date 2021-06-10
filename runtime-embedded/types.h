#pragma once
#include <stdint.h>
#include <stdbool.h>
typedef struct virtualmachine {
  uint16_t pc;
  uint16_t regA;
  uint16_t regB;
  uint16_t regC;
  uint16_t regX;
  uint16_t regY;
  uint16_t regZ;
  uint16_t regF;
  uint16_t regH;
  uint8_t sp;
  uint16_t tmpstack;
  bool push;
  uint16_t null;
  uint16_t fixed0;
  uint16_t fixed1;
  bool halt;
  uint16_t *addrspace;
} virtualmachine_t;
void init_machine(virtualmachine_t *);