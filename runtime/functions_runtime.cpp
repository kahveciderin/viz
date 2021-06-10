#include "datatypes.hpp"
#include "modules_enable.hpp"

#include <bits/stdint-uintn.h>
#include <cmath>
#include <ios>
#include <iostream>
#include <map>
#include <random>
#ifdef DEBUG
#include <iomanip>
const std::array<char, 16> regnames = {'A', 'B', 'X', 'Y', 'Z', 'F', 'H', 'I',
                                       'N', 'C', 'a', 'b', 'c', 'h', 'n', 'z'};
const std::array<char, 5> addrmodenames = {'#', '$', '&', '!', '?'};
#endif
bool run(virtualmachine *machine) {
  std::random_device randev;
  std::mt19937 rng(randev.entropy());
  uint16_t opcode = machine->addrspace[machine->pc];

  // extract instruction data
  uint16_t tmppc = machine->pc;
  bool pull = false;
  uint8_t addrmode = (machine->addrspace[machine->pc + 1] & 0xFF00) >> 8;
  uint8_t registers = (machine->addrspace[machine->pc + 1] & 0xFF);

  machine->fixed0 = machine->addrspace[machine->pc + 2];
  machine->fixed1 = machine->addrspace[machine->pc + 3];

#ifdef DEBUG
  char reg0 = 'A';
  char reg1 = 'A';
#endif
  std::array<uint16_t *, 16> regmap = {&(machine->regA),
                                       &(machine->regB),
                                       &(machine->regX),
                                       &(machine->regY),
                                       &(machine->regZ),
                                       &(machine->regF),
                                       &(machine->regH),
                                       &(machine->pc),
                                       &(machine->fixed0),
                                       &(machine->regC),
                                       &(machine->addrspace[machine->regA]),
                                       &(machine->addrspace[machine->regB]),
                                       &(machine->addrspace[machine->regZ]),
                                       &(machine->addrspace[machine->regH]),
                                       &(machine->addrspace[machine->fixed0]),
                                       &(machine->addrspace[machine->regC])};
  uint16_t *out0 = regmap[registers >> 4];
  regmap[8] = &(machine->fixed1);
  regmap[14] = &(machine->addrspace[machine->fixed1]);

#ifdef DEBUG
  reg0 = regnames[registers >> 4];
#endif
  uint16_t *out1 = regmap[registers & 0xF];
#ifdef DEBUG
  reg1 = regnames[registers & 0xFF];
#endif
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
    break;

  case 2:
    data1 += machine->regY;
    break;

  case 3:
    data1 += machine->regX;
    data0 += machine->regY;
    break;

  case 4:
    data1 += machine->regY;
    data0 += machine->regX;
    break;
  default:
    break;
  }

#ifdef DEBUG
  if (addrmode < 5) {
    adrdbg = addrmodenames[addrmode];
  }
  const std::array<std::string, 31> commands = {
      "NOP", "ADD", "SUB", "MUL", "DIV", "CMP", "JMP", "GFX",
      "AND", "NOT", "OOR", "XOR", "INP", "OUT", "RSH", "LSH",
      "SET", "GET", "JOZ", "RND", "MOV", "PSH", "POP", "MOD",
      "HLT", "JNZ", "POW", "CAL", "RET", "CON", "DCN"};
  std::cout << "\n\nProgram Counter: " << std::dec << machine->pc << "\n"
            << "OPCODE:" << commands[opcode] << adrdbg << reg0 << reg1
            << std::hex << std::setfill('0') << std::setw(4) << " " << data0
            << " " << data1 << "\n"
            << "A: 0x" << machine->regA << "(" << machine->addrspace[machine->regA] << ")" << "\n"
            << "B: 0x" << machine->regB << "(" << machine->addrspace[machine->regB] << ")" << "\n"
            << "C: 0x" << machine->regC << "(" << machine->addrspace[machine->regC] << ")" << "\n"
            << "X: 0x" << machine->regX << "(" << machine->addrspace[machine->regX] << ")" << "\n"
            << "Y: 0x" << machine->regY << "(" << machine->addrspace[machine->regY] << ")" << "\n"
            << "Z: 0x" << machine->regZ << "(" << machine->addrspace[machine->regZ] << ")" << "\n"
            << "F: 0x" << machine->regF << "(" << machine->addrspace[machine->regF] << ")" << "\n"
            << "H: 0x" << machine->regH << "(" << machine->addrspace[machine->regH] << ")" << "\n";
  std::flush(std::cout);
#endif
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

  uint16_t tmp0 = 0;
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
      std::cerr << "Division by zero at pc:" << std::hex << machine->pc
                << std::dec << "\n";
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
    data1 = ~data1;
    data0 = ~data0;

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
    data1 = machine->devices[data0]->out();
    *out1 = data1;
    break;

  case 0x000D: // OUT: send a value
    machine->devices[data0]->in(data1);
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
    *out0 = rng() % 0xFFFF + 1;
    *out1 = rng() % 0xFFFF + 1;
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
    case 0:
      machine->devices.insert({data0, (device*)new device_type::console});
      break;
    default:
      break;
    }
    break;
  case 0x001E: // DCN
    machine->devices.erase(data0);
    break;
  default:
    break;
  }

  // end program execution

  if ((out0 == &(machine->pc) || out1 == &(machine->pc)) &&
      machine->pc != tmppc) {
    inc = false;
  }
  machine->pc += inc ? 4 : 0;
  return false;
}
bool check(virtualmachine *machine) {
  if (machine->pc > 0xFFFF) {
    machine->pc = 0;
  }

  machine->null = 0;
  return false;
}