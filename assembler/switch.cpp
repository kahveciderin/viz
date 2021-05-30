#include <string>
#include "functions_assembler.hpp"
uint16_t opcode_to_code(std::string cmd) {
  uint16_t retval = 0x0;
  switch (str2int(cmd.c_str())) {
    case str2intc("NOP"):
      retval = 0x0;
      break;
    case str2intc("ADD"):
      retval = 0x1;
      break;
    case str2intc("SUB"):
      retval = 0x2;
      break;
    case str2intc("MUL"):
      retval = 0x3;
      break;
    case str2intc("DIV"):
      retval = 0x4;
      break;
    case str2intc("CMP"):
      retval = 0x5;
      break;
    case str2intc("JMP"):
      retval = 0x6;
      break;
    case str2intc("GFX"):
      retval = 0x7;
      break;
    case str2intc("AND"):
      retval = 0x8;
      break;
    case str2intc("NOT"):
      retval = 0x9;
      break;
    case str2intc("OOR"):
      retval = 0xa;
      break;
    case str2intc("XOR"):
      retval = 0xb;
      break;
    case str2intc("INP"):
      retval = 0xc;
      break;
    case str2intc("OUT"):
      retval = 0xd;
      break;
    case str2intc("RSH"):
      retval = 0xe;
      break;
    case str2intc("LSH"):
      retval = 0xf;
      break;
    case str2intc("SET"):
      retval = 0x10;
      break;
    case str2intc("GET"):
      retval = 0x11;
      break;
    case str2intc("JOZ"):
      retval = 0x12;
      break;
    case str2intc("RND"):
      retval = 0x13;
      break;
    case str2intc("MOV"):
      retval = 0x14;
      break;
    case str2intc("PSH"):
      retval = 0x15;
      break;
    case str2intc("POP"):
      retval = 0x16;
      break;
    case str2intc("MOD"):
      retval = 0x17;
      break;
    case str2intc("HLT"):
      retval = 0x18;
      break;
    case str2intc("JNZ"):
      retval = 0x19;
      break;
    case str2intc("POW"):
      retval = 0x1A;
      break;
    case str2intc("CAL"):
      retval = 0x1B;
      break;
    case str2intc("RET"):
      retval = 0x1C;
      break;
    case str2intc("CON"):
      retval = 0x1D;
      break;
    case str2intc("DCN"):
      retval = 0x1E;
      break;
  }

  return retval;
}