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

#pragma once
#include "definitions.hpp"
#include <array>
#include <bits/stdint-uintn.h>
#include <string>
#include <vector>
std::array<uint16_t, 4> convert(std::string line);
std::vector<uint16_t> compile(std::string code, uint16_t* data_size);
