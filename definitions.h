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
#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <math.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <string>

using namespace std;

#define TERMINATOR '\n'

#ifdef DEBUG
string commands[] = {"NOP", "ADD", "SUB", "MUL", "DIV", "CMP", "JMP", "GFX", "AND", "NOT", "OOR", "XOR", "INP", "OUT", "RSH", "LSH", "SET", "GET", "JOZ", "RND", "MOV", "PSH", "POP", "MOD", "HLT", "JNZ", "POW", "CAL", "RET", "CON", "DCN"};
#endif
#endif
