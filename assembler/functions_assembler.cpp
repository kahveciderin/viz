#include "definitions.hpp"
#include "switch.hpp"
#include <algorithm>
#include <array>
#include <bits/stdint-uintn.h>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
#include <string>
#include <vector>
std::array<uint16_t, 4> convert(std::string line) {

  const std::map<char, int> addrmodeencoding = {
      {'#', 0}, {'$', 1 << 4}, {'&', 2 << 4}, {'!', 3 << 4}, {'?', 4 << 4}};
  const std::map<char, int> registerencoding = {
      {'A', 0},  {'B', 1},  {'X', 2},  {'Y', 3},  {'Z', 4},  {'F', 5},
      {'H', 6},  {'I', 7},  {'N', 8},  {'C', 9},  {'a', 10}, {'b', 11},
      {'z', 12}, {'h', 13}, {'n', 14}, {'c', 15},
  };
  std::array<uint16_t, 4> data = {0, 0, 0, 0};
  /*
   * (As hex)
   * First four digits are opcodes
   * Next two digits are addressing modes
   * Next two digits are register select (in which register the result will be)
   * Next eight digits are data (little endian)
   */
  std::string cmd;
  cmd += line[0];
  cmd += line[1];
  cmd += line[2];

  /*
   * OPCODES:
   *
   */

  /*
   * ADDRESSING MODES (IN HEX):
   * 0 value      #
   * 1 x indexed  $
   * 2 y indexed  &
   * 3 xy indexed !
   * 4 yx indexed ?
   */

  /*
   * REGISTER SELECT (IN HEX):
   * 0 A
   * 1 B
   * 2 X
   * 3 Y
   * 4 Z
   * 5 (F)COLOR
   * 6 H
   * 7 (I)INSTRUCTION POINTER
   * 8 (N)FIXED
   */

  /*
   * ADD$_A 000000FF ;adds 0xFF to the register A
   *
   */

  data[0] = opcode_to_code(cmd);
  if (addrmodeencoding.count(line[3]) > 0) {
    data[1] = addrmodeencoding.at(line[3]);
  } else {
    std::cerr << "Instruction \"" << line
              << "\" cannot be converted: bad addressing mode\n";
    std::exit(-1);
  }
  if (registerencoding.count(line[4]) > 0) {
    data[1] |= registerencoding.at(line[4]);
  } else {
    std::cerr << "Instruction \"" << line
              << "\" cannot be converted: bad left hand register\n";
    std::exit(-1);
  }

  data[1] = data[1] << 4;

  if (registerencoding.count(line[5]) > 0) {
    data[1] |= registerencoding.at(line[4]);
  } else {
    std::cerr << "Instruction \"" << line
              << "\" cannot be converted: bad right hand register\n";
    std::exit(-1);
  }

  if (line[6] == ' ') {
    cmd = line[7];
    cmd += line[8];
    cmd += line[9];
    cmd += line[10];

    data[2] = std::stoi(cmd, nullptr, 16);

    cmd = line[12];
    cmd += line[13];
    cmd += line[14];
    cmd += line[15];

    data[3] = std::stoi(cmd, nullptr, 16);
  }
  return data;
}
std::vector<uint16_t> compile(std::string code, uint16_t *data_size) {
  std::vector<uint16_t> data;
  uint16_t g = 0;

  std::array<label, 0x10000> labels;

  int q = 1;
  labels[0].name = std::string("");
  labels[0].addr = 0x0000;
  for (int i = 0; i < code.length(); i++) {
    std::string line;
    std::string check_line;

    while (code[i] != TERMINATOR) {
      std::string s;
      s = code[i];
      line.append(s);

      i++;
    }

    check_line = line;
    check_line.erase(std::remove(check_line.begin(), check_line.end(), ' '),
                     check_line.end());

    if (check_line.empty())
      continue;
    if (line[0] == '@') {
      if (line[1] == '!') {
        g += stoi(line.substr(2, 6), nullptr, 16);

      } else {
        g = stoi(line.substr(1, 5), nullptr, 16);
      }
      g -= 4;
    }

#ifdef VIZ4WEB
    if (line[0] != '#' && line[0] != ':' && line[0] != '+') {
#else
    else if (line[0] != '#' && line[0] != ':') {
#endif

      g += 4;
    }

    if (line[0] == '$') {
      g += strlen(line.c_str());
      g -= 4;
    }

    else if (line[0] == ':') {
      labels[q].name = line;
      labels[q].name.erase(0, 1);
      labels[q].addr = g;
#ifdef DEBUG
      printf("Label: %s %x\n", labels[q].name, labels[q].addr);
#endif
      q++;
    }
  }

  g = 0;
  for (int v = 0; v < q; v++) {
    std::string dot = ".";
    std::string fromf = dot.append(labels[v].name);
    std::stringstream loop;
    loop << std::hex << std::setfill('0') << std::setw(4) << labels[v].addr;
    const std::string &tof(loop.str());
    int index = 0;
    while ((index = code.find(fromf + " ")) != std::string::npos) {
      code.replace(index, fromf.length(),
                   tof); // remove and replace from that position
    }
    while ((index = code.find(fromf + "\n")) != std::string::npos) {
      code.replace(index, fromf.length(),
                   tof); // remove and replace from that position
    }
  }

  for (int i = 0; i < code.length(); i++) {
    std::string line;
    std::string check_line;

    while (code[i] != TERMINATOR) {
      std::string s;
      s = code[i];
      line.append(s);

      i++;
    }

    check_line = line;
    check_line.erase(std::remove(check_line.begin(), check_line.end(), ' '),
                     check_line.end());

    if (check_line.empty())
      continue;

    if (line[0] == '@') {
      if (line[1] == '!') {
        g += stoi(line.substr(2, 6), nullptr, 16);
      } else {
        g = stoi(line.substr(1, 5), nullptr, 16);
      }
    } else if (line[0] == '$') {
      for (int f = 1; f <= strlen(line.c_str()) - 1; f++) {
        data.resize(g + 1);
        data[g] = static_cast<unsigned char>(line[f]);
        g++;
      }
      data.resize(g + 1);
      data[g] = 0;
      g++;
    } else if (line[0] != '#' && line[0] != ':') {

#ifdef DEBUG
      std::cout << line.c_str() << "\n";
#endif

      std::array<uint16_t, 4> compiled = convert(line);
      if (compiled[0] == 0 && compiled[1] == 0 && compiled[2] == 0 &&
          compiled[3] == 0) {
        continue;
      }
      data.resize(g + 4);
      data[g] = compiled[0];
      g++;
      data[g] = compiled[1];
      g++;
      data[g] = compiled[2];
      g++;
      data[g] = compiled[3];
      g++;
#ifdef DEBUG
      std::cout << "\n";
#endif
    }
  }
  *data_size = g;
  return data;
}
