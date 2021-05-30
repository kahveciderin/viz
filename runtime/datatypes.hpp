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

#pragma once

#include <stdint.h>

#ifdef DEBUG
#include <string>
inline const std::string commands[] = {"NOP", "ADD", "SUB", "MUL", "DIV", "CMP", "JMP", "GFX", "AND", "NOT", "OOR", "XOR", "INP", "OUT", "RSH", "LSH", "SET", "GET", "JOZ", "RND", "MOV", "PSH", "POP", "MOD", "HLT", "JNZ", "POW", "CAL", "RET", "CON", "DCN"};
#endif

class device;
class virtualmachine {
 public:
  uint16_t pc = 0;
  uint16_t regA = 0;
  uint16_t regB = 0;
  uint16_t regC = 0;
  uint16_t regX = 0;
  uint16_t regY = 0;
  uint16_t regZ = 0;
  uint16_t regF = 0;
  uint16_t regH = 0;
  uint8_t sp = 0xFF;
  uint16_t *addrspace;
  uint16_t tmpstack;
  bool push;
  uint16_t null;
  uint16_t fixed0;
  uint16_t fixed1;
  bool halt;
  device *devices[1];
};

class device {
 public:
  uint16_t databuffer[256];
  uint8_t datap;
  virtual uint16_t run();
  virtual ~device();
  uint16_t outbuff;

 public:
  virtualmachine *machine;
  void init(virtualmachine *mach);

 public:
  void in(uint16_t data);

 public:
  uint16_t out();
};