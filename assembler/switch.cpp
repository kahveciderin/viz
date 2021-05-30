#include "functions_assembler.hpp"
#include <bits/stdint-uintn.h>
#include <map>
#include <string>

uint16_t opcode_to_code(const std::string& cmd) {
  const std::map<std::string, uint16_t> opcode_to_code_map = {
    {"NOP",0},
    {"ADD",1},
    {"SUB",2},
    {"MUL",3},
    {"DIV",4},
    {"CMP",5},
    {"JMP",6},
    {"GFX",7},
    {"AND",8},
    {"NOT",9},
    {"OOR",10},
    {"XOR",11},
    {"INP",12},
    {"OUT",13},
    {"RSH",14},
    {"LSH",15},
    {"SET",16},
    {"GET",17},
    {"JOZ",18},
    {"RND",19},
    {"MOV",20},
    {"PSH",21},
    {"POP",22},
    {"MOD",23},
    {"HLT",24},
    {"JNZ",25},
    {"POW",26},
    {"CAL",27},
    {"RET",28},
    {"CON",29},
    {"DCN",30}
  };
  uint16_t retval = 0x0;

  if (opcode_to_code_map.count(cmd) > 0) {
    retval = opcode_to_code_map.at(cmd);
  }

  return retval;
}