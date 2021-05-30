/*
  VIZ Runtime Kit
  Copyright (C) 2021 Derin İlkcan Karakoç

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
#include "functions_runtime.h"
#include <bits/stdint-uintn.h>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#ifdef VIZ4WEB
#include <regex.h>
#endif
int main(int argc, char *argv[]) {
  srand(time(NULL));
  std::string data;
  virtualmachine machinestate;
  std::string infile;
  if (argc < 2) {
      std::cout << "Enter input file name:";
      std::cin >> infile;
  } else {
    infile = argv[1];
  }
  std::ifstream file(infile, std::ios::binary);
#ifdef VIZ4WEB
  regex_t regex;
  int reti;
  reti = regcomp(&regex, "(?<=^>>).*", REG_EXTENDED);
#endif
  file.seekg(0, std::ios::end);
  int len = file.tellg();
  char *mem_8bit = new char[len];
  file.seekg(0, std::ios::beg);
  file.read(mem_8bit, len);

  uint16_t *memcontents = new uint16_t[0x10000];
  for(int i = 0; i < 0x10000; i++){
    if(i < len) memcontents[i] = (mem_8bit[2 * i] << 8) | mem_8bit[1 + (2 * i)];
    else memcontents[i] = 0;
  }
  
  machinestate.push = false;
  machinestate.halt = false;
  machinestate.addrspace = memcontents;
#ifdef DEBUG
  unsigned long tinstrun = 0;
#endif
  while (true) {
    run(&machinestate);
    check(&machinestate);
    if (machinestate.halt)
      break;
#ifdef DEBUG
    tinstrun++;
#endif
  }
#ifdef DEBUG
  printf("\n\nTotal instructions ran: %lu\n", tinstrun);
#else
  printf("\n");
#endif
return 0;
}