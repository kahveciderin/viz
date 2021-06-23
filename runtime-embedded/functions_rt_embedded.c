#include "types.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "architecture-dependent/architecture-dependent.h"
bool do_cycle(virtualmachine_t *vm) {
    uint16_t opcode = vm->addrspace[vm->pc];
    uint8_t addrmode = (vm->addrspace[vm->pc + 1] & 0xFF00) >> 8;
    uint8_t registers = (vm->addrspace[vm->pc + 1] & 0xFF);
    vm->fixed0 = vm->addrspace[vm->pc + 2];
    vm->fixed1 = vm->addrspace[vm->pc + 3];
    uint16_t *regmap[16] = {
        &(vm->regA),
        &(vm->regB),
        &(vm->regX),
        &(vm->regY),
        &(vm->regZ),
        &(vm->regF),
        &(vm->regH),
        &(vm->pc),
        &(vm->fixed0),
        &(vm->regC),
        &(vm->addrspace[vm->regA]),
        &(vm->addrspace[vm->regB]),
        &(vm->addrspace[vm->regZ]),
        &(vm->addrspace[vm->regH]),
        &(vm->addrspace[vm->fixed0]),
        &(vm->addrspace[vm->regC])
    };
    uint16_t *out0 = regmap[registers >> 4];
    regmap[8] = &(vm->fixed1);
    regmap[14] = &(vm->addrspace[vm->fixed1]);
    uint16_t *out1 = regmap[registers & 0xF];
    uint16_t data0 = *out0;
    uint16_t data1 = *out1;
    switch (addrmode) {
        case 0:
        break;
        case 1:
            data1 += vm->regX;
        break;
        case 2:
            data1 += vm->regY;
        break;
        case 3:
            data1 += vm->regX;
            data0 += vm->regY;
        break;
        case 4:
            data1 += vm->regY;
            data0 += vm->regX;
        break;
        default:
        break;
    }
    bool inc = true;
    uint16_t tmp0 = 0;

    switch (opcode) {
    case 0x0000:
        break;

    case 0x0001: // ADD: add first value to the second and write to second
        data0 += data1;
        *out0 = data0;
        break;

    case 0x0002: // SUB: subtract first value from the second and write to the
                // second
        data0 -= data1;
        *out0 = data0;
        break;

    case 0x0003: // MUL: multiply both values and write to the second
        data0 *= data1;
        *out0 = data0;
        break;

    case 0x0004: // DIV: divide values and write to the second
        if (data1 == 0) {
            vm->halt = true;
        break;
        }
        data0 /= data1;
        *out0 = data0;
        break;

    case 0x0005: // CMP: compare two values (ffff if first is bigger, 1 if second
                // is bigger, 0 if equal)
        tmp0 = data0 > data1 ? 0xffff : 0x0;
        data1 = data0 < data1 ? 0x1 : tmp0;
        *out1 = data1;
        break;

    case 0x0006: // JMP: jump to an address (second is the base)
        inc = false;
        vm->pc = data1;
        break;

    case 0x0007: // GFX: open a graphics window (WIP)

        break;

    case 0x0008: // AND: and two values and write to the second
        data1 = data1 & data0;
        *out1 = data1;
        break;

    case 0x0009: // NOT: invert every single bit
        data1 = ~data1;
        data0 = ~data0;

        *out1 = data1;
        *out0 = data0;
        break;

    case 0x000A: // OOR: OR two values and write to the second
        data1 = data1 | data0;
        *out1 = data1;
        break;

    case 0x000B: // XOR: XOR two values and write to the second
        data1 = data1 ^ data0;
        *out1 = data1;
        break;

    case 0x000C: // INP: get a value
        data1 = in(data0);
        *out1 = data1;
        break;

    case 0x000D: // OUT: send a value
        out(data1, data0);
        break;

    case 0x000E: // RSH: binary right shift second value by first value and write
                // to the second
        data1 = data1 >> data0;
        *out1 = data1;
        break;

    case 0x000F: // LSH: binary left shift second value by first value and write
                // to the second
        data1 = data1 << data0;
        *out1 = data1;
        break;

    case 0x0010: // SET: set first address second value
        vm->addrspace[data0] = data1;
        break;

    case 0x0011: // GET: get first address to the second
        data1 = vm->addrspace[data0];
        *out1 = data1;
        break;

    case 0x0012: // JOZ: jump to second address if first is zero
        vm->pc = data0 == 0 ? data1 : vm->pc;

        inc = data0 != 0;
        break;

    case 0x0013: // RND: random number
        *out0 = entropy();
        *out1 = entropy();
        break;

    case 0x0014:
        *out1 = data0;
        break;

    case 0x0015:
        vm->addrspace[0xFF00 + vm->sp] = data0;
        vm->sp--;

        break;

    case 0x0016:
        vm->sp++;
        *out1 = vm->addrspace[0xFF00 + vm->sp];
        break;

    case 0x0017:
        data0 = data0 % data1;
        *out0 = data0;
        break;

    case 0x0018:
        return false;
        break;

    case 0x0019: // JNZ: jump to second address if first is not zero
        vm->pc = data0 != 0 ? data1 : vm->pc;
        inc = data0 != 0;
        break;
    case 0x001A: // POW: first pow second to first
        data0 = pow16(data0, data1);
        *out0 = data0;
        break;
    case 0x001B: // CAL: call function
        vm->addrspace[0xFF00 + vm->sp] = vm->pc + 4;
        vm->sp--;
        vm->pc = data1;
        inc = false;
        break;
    case 0x001C: // RET: return from function
        vm->sp++;
        vm->pc = vm->addrspace[0xFF00 + vm->sp];
        inc = false;
        break;
    default:
        break;
    }
    if (inc) {
        vm->pc += 4;
    }
    return true;
}