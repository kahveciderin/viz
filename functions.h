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
#include "datatypes.h"

#include <math.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <string>

using namespace std;

unsigned int str2int(const char* str, int h = 0);
constexpr unsigned int str2intc(const char* str, int h = 0){
  return !str[h] ? 5381 : (str2intc(str, h + 1) * 33) ^ str[h];
}

uint16_t* convert(string line);
uint16_t* compile(string code);

bool run(virtualmachine* machine);
bool check(virtualmachine* machine);