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

#include "definitions.h"
#include "functions.h"
#include <cstdint>
#include <fstream>
#include <string>
#ifdef VIZ4WEB
#include <regex.h>
#endif
using namespace std;
int main(int argc, char *argv[]) {
  srand(time(NULL));
  string data;
  virtualmachine machinestate;
  if (argc < 2)
    return printf("No input file given\n");
  ifstream file(argv[1]);

#ifdef VIZ4WEB
  regex_t regex;
  int reti;
  reti = regcomp(&regex, "(?<=^>>).*", REG_EXTENDED);
#endif

#ifdef ASSEMBLER
  if (argc < 3)
    return printf("No output file given\n");

  string line;
  while (getline(file, line)) {
#ifdef VIZ4WEB
    reti = regexec(&regex, "abc", 0, NULL, 0);
    if (!reti) {
      char *code = new char[128];
      sprintf(code, "%.*s", line.length() - 2, line.c_str() + 2);

      data += code;
      data += "\n";
      delete[] code;
    } else if (reti == REG_NOMATCH) {
      data += "+";
      data += line;
      data += "\n";
    }
#else
    data += line;
    data += "\n";
#endif
  }
  uint16_t datasize;
  uint16_t *a = compile(data + "\n", &datasize);
  // char *fbuff = new char[*datasize * 2];
  char *fbuff = new char[datasize * 2];
  ofstream output_file(argv[2]);
  for (uint32_t i = 0; i < datasize; i++) {
    fbuff[2 * i] = a[i] >> 8;
    fbuff[1 + (2 * i)] = a[i] & 0xFF;
  }
  output_file.write(fbuff, datasize * 2);
#endif

#ifdef RUNTIME
  ifstream infile(argv[1]);
  infile.seekg(0, ios::end);
  int len = infile.tellg();
  char *mem_8bit = new char[len];
  infile.seekg(0, ios::beg);
  infile.read(mem_8bit, len);

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
#endif

  return 0;
}