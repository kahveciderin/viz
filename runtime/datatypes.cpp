/*
  VIZ Runtime Kit
  Copyright (C) 2021 Derin İlkcan Karakoç, trashcognito

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

#include "datatypes.hpp"

#include <cstdint>
#ifdef DEBUG
#include <iomanip>
#include <iostream>
#endif
void device::init(virtualmachine *mach) {
  machine = mach;
}

void device::in(uint16_t data) {
  if (data == 0 && datap > 2) {
    datap = 0;
#ifdef DEBUG
    std::cout << std::hex << std::setfill('0') << std::setw(4) << databuffer[0] << " "
    << databuffer[1] << " "
    << databuffer[2] << " "
    << databuffer[3] << "\n" << std::dec;
#endif
    outbuff = run();
  } else {
    databuffer[datap] = data;
#ifdef DEBUG
    std::cout << std::hex << std::setfill('0') << std::setw(4) << databuffer[datap] << std::dec;
    std::cout << " to " << datap;
#endif
    datap++;
  }
}

uint16_t device::out() {
  return outbuff;
}

uint16_t device::run() {
  return 0;
}

void device::terminate() {
  
}