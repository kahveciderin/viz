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
#include "functions_assembler.h"
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
    std::string infile;
    std::string outfile;
    if (argc < 2) {    
        std::cout << "Enter input file name: ";
        std::cin >> infile;
    } else {
        infile = argv[1];
    }
    std::ifstream file(infile);
    if (!file) {
        std::cerr << "Input file failed to open!\n";
        return -1;
    }
    if (argc < 3) {
        std::cout << "Enter output file name: ";
        std::cin >> outfile;
    } else {
        outfile = argv[2];
    }
    std::string line;
    while (getline(file, line)) {
#ifdef VIZ4WEB
        regex_t regex;
        int reti;
        reti = regcomp(&regex, "(?<=^>>).*", REG_EXTENDED);
        reti = regexec(&regex, "abc", 0, NULL, 0);
        if (!reti) {
            char *code = new char[128];
            sprintf(code, "%.*s", (int)line.length() - 2, line.c_str() + 2);

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
    char *fbuff = new char[datasize * 2];
    std::ofstream output_file(outfile);
    for (uint32_t i = 0; i < datasize; i++) {
        fbuff[2 * i] = a[i] >> 8;
        fbuff[1 + (2 * i)] = a[i] & 0xFF;
    }
    output_file.write(fbuff, datasize * 2);
    return 0;
}