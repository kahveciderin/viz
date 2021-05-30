#include "datatypes.hpp"

#include <ios>
#include <iostream>
#include <cmath>
bool run(virtualmachine *machine) {
  uint16_t opcode = machine->addrspace[machine->pc];

  // extract instruction data
  uint16_t tmppc = machine->pc;
  bool pull = false;
  uint8_t addrmode = (machine->addrspace[machine->pc + 1] & 0xFF00) >> 8;
  uint8_t registers = (machine->addrspace[machine->pc + 1] & 0xFF);

  machine->fixed0 = machine->addrspace[machine->pc + 2];
  machine->fixed1 = machine->addrspace[machine->pc + 3];

  uint16_t *out0;
#ifdef DEBUG
  char reg0 = 'A';
  char reg1 = 'A';
#endif
  switch (registers >> 4) {
  case 0:
    out0 = &(machine->regA);
    break;
  case 1:
    out0 = &(machine->regB);
#ifdef DEBUG
    reg0 = 'B';
#endif
    break;
  case 2:
    out0 = &(machine->regX);
#ifdef DEBUG
    reg0 = 'X';
#endif
    break;
  case 3:
    out0 = &(machine->regY);
#ifdef DEBUG
    reg0 = 'Y';
#endif
    break;
  case 4:
    out0 = &(machine->regZ);
#ifdef DEBUG
    reg0 = 'Z';
#endif
    break;
  case 5:
    out0 = &(machine->regF);
#ifdef DEBUG
    reg0 = 'F';
#endif
    break;
  case 6:
    out0 = &(machine->regH);
#ifdef DEBUG
    reg0 = 'H';
#endif
    break;
  case 7:
    out0 = &(machine->pc);
#ifdef DEBUG
    reg0 = 'I';
#endif
    break;
  case 8:
    out0 = &(machine->fixed0);
#ifdef DEBUG
    reg0 = 'N';
#endif
    break;
  case 9:
    out0 = &(machine->regC);
#ifdef DEBUG
    reg0 = 'C';
#endif
    break;
  case 0xA:
    out0 = &(machine->addrspace[machine->regA]);
#ifdef DEBUG
    reg0 = 'a';
#endif
    break;
  case 0xB:
    out0 = &(machine->addrspace[machine->regB]);
#ifdef DEBUG
    reg0 = 'b';
#endif
    break;
  case 0xC:
    out0 = &(machine->addrspace[machine->regZ]);
#ifdef DEBUG
    reg0 = 'z';
#endif
    break;
  case 0xD:
    out0 = &(machine->addrspace[machine->regH]);
#ifdef DEBUG
    reg0 = 'a';
#endif
    break;
  case 0xE:
    out0 = &(machine->addrspace[machine->fixed0]);
#ifdef DEBUG
    reg0 = 'n';
#endif
    break;
  case 0xF:
    out0 = &(machine->addrspace[machine->regC]);
#ifdef DEBUG
    reg0 = 'c';
#endif
  }

  uint16_t *out1;
  switch (registers & 0xF) {
  case 0:
    out1 = &(machine->regA);
    break;
  case 1:
    out1 = &(machine->regB);
#ifdef DEBUG
    reg1 = 'B';
#endif
    break;
  case 2:
    out1 = &(machine->regX);
#ifdef DEBUG
    reg1 = 'X';
#endif
    break;
  case 3:
    out1 = &(machine->regY);
#ifdef DEBUG
    reg1 = 'Y';
#endif
    break;
  case 4:
    out1 = &(machine->regZ);
#ifdef DEBUG
    reg1 = 'Z';
#endif
    break;
  case 5:
    out1 = &(machine->regF);
#ifdef DEBUG
    reg1 = 'F';
#endif
    break;
  case 6:
    out1 = &(machine->regH);
#ifdef DEBUG
    reg1 = 'H';
#endif
    break;
  case 7:
    out1 = &(machine->pc);
#ifdef DEBUG
    reg1 = 'I';
#endif
    break;
  case 8:
    out1 = &(machine->fixed1);
#ifdef DEBUG
    reg1 = 'N';
#endif
    break;
  case 9:
    out1 = &(machine->regC);
#ifdef DEBUG
    reg1 = 'C';
#endif
    break;
  case 0xA:
    out1 = &(machine->addrspace[machine->regA]);
#ifdef DEBUG
    reg1 = 'a';
#endif
    break;
  case 0xB:
    out1 = &(machine->addrspace[machine->regB]);
#ifdef DEBUG
    reg1 = 'b';
#endif
    break;
  case 0xC:
    out1 = &(machine->addrspace[machine->regZ]);
#ifdef DEBUG
    reg1 = 'z';
#endif
    break;
  case 0xD:
    out1 = &(machine->addrspace[machine->regH]);
#ifdef DEBUG
    reg1 = 'a';
#endif
    break;
  case 0xE:
    out1 = &(machine->addrspace[machine->fixed1]);
#ifdef DEBUG
    reg1 = 'n';
#endif
    break;
  case 0xF:
    out1 = &(machine->addrspace[machine->regC]);
#ifdef DEBUG
    reg1 = 'c';
#endif
    break;
  }

#ifdef DEBUG
  char adrdbg = '#';
#endif
  uint16_t data0 = *out0;
  uint16_t data1 = *out1;

  switch (addrmode) {
  case 0:
    break;

  case 1:
    data1 += machine->regX;
#ifdef DEBUG
    adrdbg = '$';
#endif
    break;

  case 2:
    data1 += machine->regY;
#ifdef DEBUG
    adrdbg = '&';
#endif
    break;

  case 3:
    data1 += machine->regX;
    data0 += machine->regY;
#ifdef DEBUG
    adrdbg = '!';
#endif
    break;

  case 4:
    data1 += machine->regY;
    data0 += machine->regX;
#ifdef DEBUG
    adrdbg = '?';
#endif
    break;
  }

#ifdef DEBUG

  printf("\n\nProgram Counter: %d\nOPCODE: %s%c%c%c %04X %04X\nA: 0x%x\nB: "
         "0x%x\nC: 0x%x\nX: 0x%x\nY: 0x%x\nZ: 0x%x\nF: 0x%x\nH: 0x%x\n\nEcho: ",
         machine->pc, commands[opcode].c_str(), adrdbg, reg0, reg1, data0,
         data1, machine->regA, machine->regB, machine->regC, machine->regX,
         machine->regY, machine->regZ, machine->regF, machine->regH);
  fflush(stdout);
#endif
  uint16_t data2 = machine->regF;

  bool inc = true;

  /*
   * We have:
   * opcode
   * data0
   * data1
   * data2 (regF)
   * out0
   * out1
   */
  // start program execution

  // left => 0
  // right => 1

  uint16_t tmp0;
  switch (opcode) {
  case 0x0000:
    break;

  case 0x0001: // ADD: add first value to the second and write to second
    data0 += data1;
    *out0 = data0;
    break;

  case 0x0002: // SUB: subtract first value from the second and write to the
               // second
    data0 -= data1;
    *out0 = data0;
    break;

  case 0x0003: // MUL: multiply both values and write to the second
    data0 *= data1;
    *out0 = data0;
    break;

  case 0x0004: // DIV: divide values and write to the second
    if (data1 == 0) {
      std::cerr << "Division by zero at pc:" << std::hex << machine->pc << std::dec << "\n";
      machine->halt = true;
      break;
    }
    data0 /= data1;
    *out0 = data0;
    break;

  case 0x0005: // CMP: compare two values (ffff if first is bigger, 1 if second
               // is bigger, 0 if equal)
    tmp0 = data0 > data1 ? 0xffff : 0x0;
    data1 = data0 < data1 ? 0x1 : tmp0;
    *out1 = data1;
    break;

  case 0x0006: // JMP: jump to an address (second is the base)
    inc = false;
    machine->pc = data1;
    break;

  case 0x0007: // GFX: open a graphics window (WIP)

    break;

  case 0x0008: // AND: and two values and write to the second
    data1 = data1 & data0;
    *out1 = data1;
    break;

  case 0x0009: // NOT: invert every single bit
    data1 = !data1;
    data0 = !data0;

    *out1 = data1;
    *out0 = data0;
    break;

  case 0x000A: // OOR: OR two values and write to the second
    data1 = data1 | data0;
    *out1 = data1;
    break;

  case 0x000B: // XOR: XOR two values and write to the second
    data1 = data1 ^ data0;
    *out1 = data1;
    break;

  case 0x000C: // INP: get a value

    if (data0 == 0)
      scanf("%c", (char *)&data1);
    else {
      data1 = machine->devices[data0]->out();
    }
    *out1 = data1;
    break;

  case 0x000D: // OUT: send a value

    if (data0 == 0)
      printf("%c", data1);
    else {
      machine->devices[data0]->in(data1);
    }

    break;

  case 0x000E: // RSH: binary right shift second value by first value and write
               // to the second
    data1 = data1 >> data0;
    *out1 = data1;
    break;

  case 0x000F: // LSH: binary left shift second value by first value and write
               // to the second
    data1 = data1 << data0;
    *out1 = data1;
    break;

  case 0x0010: // SET: set first address second value
    machine->addrspace[data0] = data1;
    break;

  case 0x0011: // GET: get first address to the second
    data1 = machine->addrspace[data0];
    *out1 = data1;
    break;

  case 0x0012: // JOZ: jump to second address if first is zero
    machine->pc = data0 == 0 ? data1 : machine->pc;

    inc = data0 != 0;
    break;

  case 0x0013: // RND: random number
    *out0 = rand() % 0xFFFF + 1;
    *out1 = rand() % 0xFFFF + 1;
    break;

  case 0x0014:
    *out1 = data0;
    break;

  case 0x0015:
    machine->addrspace[0xFF00 + machine->sp] = data0;
    machine->sp--;

    break;

  case 0x0016:
    machine->sp++;
    *out1 = machine->addrspace[0xFF00 + machine->sp];
    break;

  case 0x0017:
    data0 = data0 % data1;
    *out0 = data0;
    break;

  case 0x0018:
    machine->halt = true;
    break;

  case 0x0019: // JNZ: jump to second address if first is not zero
    machine->pc = data0 != 0 ? data1 : machine->pc;
    inc = data0 != 0;
    break;
  case 0x001A: // POW: first pow second to first
    data0 = pow(data0, data1);
    *out0 = data0;
    break;
  case 0x001B: // CAL: call function
    machine->addrspace[0xFF00 + machine->sp] = machine->pc + 4;
    machine->sp--;
    machine->pc = data1;
    inc = false;
    break;
  case 0x001C: // RET: return from function
    machine->sp++;
    machine->pc = machine->addrspace[0xFF00 + machine->sp];
    inc = false;
    break;
  case 0x001D: // CON
    switch (data1) {
      // device connections here
    }
    break;
  case 0x001E: // DCN
    free(machine->devices[data0]);
    machine->devices[data0] = (device *)0;
    break;
  }

  // end program execution

  if ((out0 == &(machine->pc) || out1 == &(machine->pc)) &&
      machine->pc != tmppc) {
    inc = false;
  }
  machine->pc += inc ? 4 : 0;
  return 0;
}
bool check(virtualmachine *machine) {
  if (machine->pc > 0xFFFF)
    machine->pc = 0;

  machine->null = 0;
  return 0;
}