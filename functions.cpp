


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
     * 7 (I)INSTRUCTION POINTER
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
        case 'C':
        data[1] += 9;
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
        case 'I':
        data[1] += 7;
        break;
        case 'N':
        data[1] += 8;
        break;
        case 'C':
        data[1] += 9;
        break;

    }


    if(line[6] == ' '){

        cmd = line[7];
        cmd += line[8];
        cmd += line[9];
        cmd += line[10];

        data[2] = stoi(cmd, 0, 16);
        
        cmd = line[12];
        cmd += line[13];
        cmd += line[14];
        cmd += line[15];

        data[3] = stoi(cmd, 0, 16);
    }
    return data;
}



uint16_t* compile(string code){
    static uint16_t data[65535];
    int g = 0;

    label labels[65535];

    int q = 1;
    memcpy(labels[0].name, "", 0);
    labels[0].addr = 0x0000;
    for(int i = 0; i < code.length(); i++){

        string line;
        
        while(code[i] != TERMINATOR){
            string s;
            s = code[i]; 
            line.append(s); 
            
            i++;
        }

        
        if(line[0] == '@'){
            if(line[1] == '!'){
                g += stoi(line.substr(2,6), 0, 16);
            }else{
                g = stoi(line.substr(1,5), 0, 16);
            }
        }


        if(line[0] != '#' && line[0] != ':'){
            g+=4;

        }
        if(line[0] == '$'){

            //printf("%d", g);
            g+=strlen(line.c_str());
            g-=4;
            //printf(" %d\n", g);
        }

        if(line[0] == ':'){
            memcpy(labels[q].name, line.c_str()+1, strlen(line.c_str()) - 1);
            labels[q].addr = g;
            #ifdef DEBUG
            printf("Label: %s %x\n", labels[q].name, labels[q].addr);
            #endif
            q++;
        }

    }
    
    g = 0;
    for(int v = 0; v < q; v++){ 
        string fromf(labels[v].name);

        uint16_t tmpdbg = labels[v].addr;
        string dot = ".";
        fromf = dot.append(fromf);
        char val[32];
        //printf("%s\n", fromf.c_str());
        if(tmpdbg & 0x000F)
        sprintf(val, "000%X", tmpdbg);
        if(tmpdbg & 0x00F0)
        sprintf(val, "00%X", tmpdbg);
        if(tmpdbg & 0x0F00)
        sprintf(val, "0%X", tmpdbg);
          
        if(tmpdbg == 0)
        sprintf(val, "000%X", tmpdbg);
        
            
        string tof(val);
        //printf("Label: %s %x (%s)\n", fromf.c_str(), labels[v].addr, tof.c_str());
        int index;
        while((index = code.find(fromf + " ")) != string::npos) {
            //code.erase(index, tof.length());
            code.replace(index, fromf.length(), tof); //remove and replace from that position
        }
        index = 0;
        while((index = code.find(fromf + "\n")) != string::npos) {
            //code.erase(index, tof.length());
            code.replace(index, fromf.length(), tof); //remove and replace from that position
        }

            
            //printf("*\n");
    }
    //printf("%s\n", code.c_str());

    for(int i = 0; i < code.length(); i++){

        string line;
        
        while(code[i] != TERMINATOR){
            string s;
            s = code[i]; 
            line.append(s); 
            
            i++;
        }

        if(line[0] == '@'){
            if(line[1] == '!'){
                g += stoi(line.substr(2,6), 0, 16);
            }else{
                g = stoi(line.substr(1,5), 0, 16);
            }
        } else if(line[0] == '$'){


            for(int f = 1; f <= strlen(line.c_str()) - 1; f++){
                data[g] = line[f];
                //printf("%c\n", data[g]);
                g++;
            }

            data[g] = 0;
            g++;
        }
        else if(line[0] != '#' && line[0] != ':'){
        //printf("*\n");

        //printf("Line: %s\n\n", line.c_str());


        #ifdef DEBUG
        printf("%s\n", line.c_str());
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
        

    }


    
    return data;
    
}



bool run(virtualmachine* machine){
    
    uint16_t opcode = machine->addrspace[machine->pc];
    
    #ifdef DEBUG
    
    printf("\n\nProgram Counter: %d\nOPCODE: %s\nA: 0x%x\nB: 0x%x\nC: 0x%x\nX: 0x%x\nY: 0x%x\nZ: 0x%x\nF: 0x%x\nH: 0x%x\n\nEcho: ", machine->pc, commands[opcode].c_str(),machine->regA, machine->regB, machine->regC, machine->regX, machine->regY, machine->regZ, machine->regF, machine->regH);
    fflush(stdout);
    #endif

    
    //extract instruction data
    uint16_t tmppc = machine->pc;
    bool pull = false;
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
        out0 = &(machine->pc);
        break;
        case 8:
        out0 = &(machine->fixed0);
        break;
        case 9:
        out0 = &(machine->regC);
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
        out1 = &(machine->pc);
        break;
        case 8:
        out1 = &(machine->fixed1);
        break;
        case 9:
        out1 = &(machine->regC);
        break;


    }


    uint16_t data0 = *out0;
    uint16_t data1 = *out1;


    switch(addrmode){

        case 0:
        break;

        case 1:
        data1 += machine->regX;
        break;

        case 2:
        data1 += machine->regY;
        break;

        case 3:
        data1 += machine->regX;
        data0 += machine->regY;
        break;

        case 4:
        data1 += machine->regY;
        data0 += machine->regX;
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



    //left => 0
    //right => 1

    uint16_t tmp0;
    switch(opcode){
        case 0x0000:
        break;

        case 0x0001: //ADD: add first value to the second and write to second
            data0 += data1;
            *out0 = data0;
        break;

        case 0x0002: //SUB: subtract first value from the second and write to the second
            data0 -= data1;
            *out0 = data0;
        break;

        case 0x0003: //MUL: multiply both values and write to the second
            data0 *= data1;
            *out0 = data0;
        break;

        case 0x0004: //DIV: divide values and write to the second
            data0 /= data1;
            *out0 = data0;
        break;

        case 0x0005: //CMP: compare two values (ffff if first is bigger, 1 if second is bigger, 0 if equal)
            tmp0 = data0 > data1 ? 0xffff : 0x0;
            data1 = data0 < data1 ? 0x1 : tmp0;
            *out1 = data1;
        break;

        case 0x0006: //JMP: jump to an address (second is the base)
            inc = false;
            machine->pc = data1;
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
            //data1 = scanf();
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
            machine->addrspace[data0] = data1;
        break;

        case 0x0011: //GET: get first address to the second
            data1 = machine->addrspace[data0];
            *out1 = data1;
        break;

        case 0x0012: //JOZ: jump to second address if first is zero
            machine->pc = data0 == 0 ? data1 : machine->pc;

            inc = data0 != 0;
        break;

        case 0x0013: //RND: random number
            *out0 = rand() % 0xFFFF + 1;
            *out1 = rand() % 0xFFFF + 1;
        break;

        case 0x0014:
            *out1 = data0;
        break;

        case 0x0015:
            machine->addrspace[0xFF00 + machine->sp] = data0;
            machine->sp--;

        break;

        case 0x0016:
            machine->sp++;
            *out1 = machine->addrspace[0xFF00 + machine->sp];
        break;

        case 0x0017:
            data0 = data0 % data1;
            *out0 = data0;
        break;

        case 0x0018:
            machine->halt = true;
        break;

        case 0x0019: //JNZ: jump to second address if first is not zero
            machine->pc = data0 != 0 ? data1 : machine->pc;
            inc = data0 != 0;
        break;
        case 0x001A: //POW: first pow second to first
            data0 = pow(data0, data1);
            *out0 = data0;
        break;
        case 0x001B: //CAL: call function
            machine->addrspace[0xFF00 + machine->sp] = machine->pc + 4;
            machine->sp--;
            machine->pc = data1;
            inc = false;
        break;
        case 0x001C: //RET: return from function
            machine->sp++;
            machine->pc = machine->addrspace[0xFF00 + machine->sp];
            inc = false;
        break;
        
    }


    //end program execution

    if((out0 == &(machine->pc) || out1 == &(machine->pc)) && machine->pc != tmppc ){
        inc = false;
    }
    machine->pc += inc ? 4 : 0;
    return 0;
}


bool check(virtualmachine* machine){
    if(machine->pc > 0xFFFE)    machine->pc = 0;

    machine->null = 0;
    return 0;
}