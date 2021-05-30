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

#include <array>
#include <bits/stdint-uintn.h>
#include <cstdint>
#include <map>

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
  uint8_t sp = ~static_cast<uint8_t>(0x00);
  std::array<uint16_t, 0x10000> addrspace=std::array<uint16_t, 0x10000>();
  uint16_t tmpstack=0;
  bool push=false;
  uint16_t null=0;
  uint16_t fixed0=0;
  uint16_t fixed1=0;
  bool halt=false;
  std::map<uint16_t, device*> devices = {};
};

class device {
  private:
  std::array<uint16_t, 256> databuffer=std::array<uint16_t, 256>();
  uint8_t datap=0;
  virtual uint16_t run();
  uint16_t outbuff=0;
  virtualmachine *machine=nullptr;
  public:

  void init(virtualmachine *mach);
 
  virtual void in(uint16_t data);

 
  virtual uint16_t out();

  static void terminate();
};