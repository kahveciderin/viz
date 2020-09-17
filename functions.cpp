


unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

constexpr unsigned int str2intc(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2intc(str, h+1) * 33) ^ str[h];
}



uint16_t* convert(string line){
    static uint16_t data[4];
    /* 
     * (As hex)
     * First four digits are opcodes
     * Next two digits are addressing modes
     * Next two digits are register select (in which register the result will be)
     * Next eight digits are data (little endian)
     */ 
    string cmd;
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
     * 7 (S)STACK
     * 8 (N)FIXED
     */


    /*
     * ADD$_A 000000FF ;adds 0xFF to the register A
     * 
     */
    
    #include "switch.h"


    switch(line[3]){

        case '#':
        data[1] = 0x00;
        break;
        case '$':
        data[1] = 0x01;
        break;
        case '&':
        data[1] = 0x02;
        break;
        case '!':
        data[1] = 0x03;
        break;
        case '?':
        data[1] = 0x04;
        break;
        
    }

    
    data[1] = data[1] << 4;
    
    
    switch(line[4]){
        case 'A':
        data[1] += 0;
        break;
        case 'B':
        data[1] += 1;
        break;
        case 'X':
        data[1] += 2;
        break;
        case 'Y':
        data[1] += 3;
        break;
        case 'Z':
        data[1] += 4;
        break;
        case 'F':
        data[1] += 5;
        break;
        case 'H':
        data[1] += 6;
        break;
        case 'S':
        data[1] += 7;
        break;
        case 'N':
        data[1] += 8;
        break;

    }
    
    
    data[1] = data[1] << 4;
    

    switch(line[5]){
        case 'A':
        data[1] += 0;
        break;
        case 'B':
        data[1] += 1;
        break;
        case 'X':
        data[1] += 2;
        break;
        case 'Y':
        data[1] += 3;
        break;
        case 'Z':
        data[1] += 4;
        break;
        case 'F':
        data[1] += 5;
        break;
        case 'H':
        data[1] += 6;
        break;
        case 'S':
        data[1] += 7;
        break;
        case 'N':
        data[1] += 8;
        break;

    }


    if(line[6] == ' '){

        cmd = line[7];
        cmd += line[8];
        cmd += line[9];
        cmd += line[10];

        data[2] = stoi(cmd, 0, 16);
        
        cmd = line[11];
        cmd += line[12];
        cmd += line[13];
        cmd += line[14];

        data[3] = stoi(cmd, 0, 16);
    }
    return data;
}



uint16_t* compile(string code){
    static uint16_t data[65535];
    int g = 0;
    for(int i = 0; i < code.length(); i++){

        string line;
        
        while(code[i] != TERMINATOR){
            string s;
            s = code[i]; 
            line.append(s); 
            
            i++;
        }
        
        #ifdef DEBUG
        printf("%s",line.c_str());
        #endif 

        uint16_t* compiled = convert(line);
        data[g] = compiled[0];
        g++;
        data[g] = compiled[1];
        g++;
        data[g] = compiled[2];
        g++;
        data[g] = compiled[3];
        g++;
        #ifdef DEBUG
        printf("\n");
        #endif 
    }

    return data;
    
}



bool run(virtualmachine* machine){
    
    uint16_t opcode = machine->addrspace[machine->pc];
    
    #ifdef DEBUG
    printf("%x",opcode);
    #endif


    //extract instruction data


    uint8_t addrmode = (machine->addrspace[machine->pc + 1] & 0xFF00) >> 8;
    uint8_t registers = (machine->addrspace[machine->pc + 1] & 0xFF);

    machine->fixed0 = machine->addrspace[machine->pc + 2];
    machine->fixed1 = machine->addrspace[machine->pc + 3];

    
    
    uint16_t* out0;
    switch(registers >> 4){

        case 0:
        out0 = &(machine->regA);
        break;
        case 1:
        out0 = &(machine->regB);
        break;
        case 2:
        out0 = &(machine->regX);
        break;
        case 3:
        out0 = &(machine->regY);
        break;
        case 4:
        out0 = &(machine->regZ);
        break;
        case 5:
        out0 = &(machine->regF);
        break;
        case 6:
        out0 = &(machine->regH);
        break;
        case 7:
        machine->push = true;
        out0 = &(machine->tmpstack);
        break;
        case 8:
        out0 = &(machine->fixed0);
        break;


    }


    uint16_t* out1;
    switch(registers & 0xF){

        case 0:
        out1 = &(machine->regA);
        break;
        case 1:
        out1 = &(machine->regB);
        break;
        case 2:
        out1 = &(machine->regX);
        break;
        case 3:
        out1 = &(machine->regY);
        break;
        case 4:
        out1 = &(machine->regZ);
        break;
        case 5:
        out1 = &(machine->regF);
        break;
        case 6:
        out1 = &(machine->regH);
        break;
        case 7:
        machine->push = true;
        out1 = &(machine->tmpstack);
        break;
        case 8:
        out1 = &(machine->fixed1);
        break;


    }


    uint16_t data0 = *out0;
    uint16_t data1 = *out1;


    switch(addrmode){

        case 0:
        break;

        case 1:
        data0 += machine->regX;
        break;

        case 2:
        data0 += machine->regY;
        break;

        case 3:
        data0 += machine->regX;
        data1 += machine->regY;
        break;

        case 4:
        data0 += machine->regY;
        data1 += machine->regX;
        break;
    }


    uint16_t data2 = machine->regF;

    bool inc = true;

    /* 
     * We have:
     * opcode
     * data0
     * data1
     * data2 (regF)
     * out0
     * out1
     */
    //start program execution

    uint16_t tmp0;
    switch(opcode){
        case 0x0000:
        break;

        case 0x0001: //ADD: add first value to the second and write to second
            data1 += data0;
            *out1 = data1;
        break;

        case 0x0002: //SUB: subtract first value from the second and write to the second
            data1 -= data0;
            *out1 = data1;
        break;

        case 0x0003: //MUL: multiply both values and write to the second
            data1 *= data0;
            *out1 = data1;
        break;

        case 0x0004: //DIV: divide values and write to the second
            data1 = data1 / data0;
            *out1 = data1;
        break;

        case 0x0005: //CMP: compare two values (ffff if first is bigger, 1 if second is bigger, 0 if equal)
            tmp0 = data0 > data1 ? 0xffff : 0x0;
            data1 = data0 < data1 ? 0x1 : tmp0;
            *out1 = data1;
        break;

        case 0x0006: //JMP: jump to an address (first is the base)
            inc = false;
            machine->pc = data0;
        break;

        case 0x0007: //GFX: open a graphics window (WIP)
        
        break;

        case 0x0008: //AND: and two values and write to the second
            data1 = data1 & data0;
            *out1 = data1;
        break;

        case 0x0009: //NOT: invert every single bit
            data1 = !data1;
            data0 = !data0;

            *out1 = data1;
            *out0 = data0;
        break;

        case 0x000A: //OOR: OR two values and write to the second
            data1 = data1 | data0;
            *out1 = data1;
        break;

        case 0x000B: //XOR: XOR two values and write to the second
            data1 = data1 ^ data0;
            *out1 = data1;
        break;

        case 0x000C: //INP: get one character from user and write to the second
            scanf("%c", &data1);
            *out1 = data1;
        break;

        case 0x000D: //OUT: send two characters to the user
            printf("%c", data0);
            printf("%c", data1);
        break;

        case 0x000E: //RSH: binary right shift second value by first value and write to the second
            data1 = data1 >> data0;
            *out1 = data1;
        break;

        case 0x000F: //LSH: binary left shift second value by first value and write to the second
            data1 = data1 << data0;
            *out1 = data1;
        break;

        case 0x0010: //SET: set first address second value
            machine->addrspace[data1] = data0;
        break;

        case 0x0011: //GET: get first address to the second
            data0 = machine->addrspace[data1];
            *out0 = data0;
        break;

        case 0x0012: //JOZ: jump to second address if first is zero
            inc = false;
            machine->pc = data1 == 0 ? data0 : machine->pc;
        break;

        case 0x0013: //RND: random number
            *out1 = rand() % 0xFFFF + 1;
        break;

        case 0x0014:
            *out1 = data0;
        break;
        
    }


    //end program execution
    machine->pc += inc ? 4 : 0;
    return 0;
}


bool check(virtualmachine* machine){
    if(machine->pc > 0xFFFE)    machine->pc = 0;

    //stack 
    if(machine->push){
        machine->addrspace[0xFF00 + machine->sp] = machine->tmpstack;
        if(machine->sp == 0) machine->sp = 0xFF;
        else machine->sp--;
    }
    machine->null = 0;
    return 0;
}