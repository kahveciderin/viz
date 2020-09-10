


unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

constexpr unsigned int str2intc(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2intc(str, h+1) * 33) ^ str[h];
}



uint16_t* convert(string line){
    uint16_t data[4];
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
     * 0 register           #
     * 1 fixed              $
     * 2 address            &
     * 3 fixed indexed, x   !
     * 4 fixed indexed, y   ?
     * 5 fixed indexed, z   +
     * 6 address indexed, x ~
     * 7 address indexed, y <
     * 8 address indexed, z >
     * 9 stack              @
     * A stack indexed, x   ^
     * B stack indexed, y   *
     * C stack indexed, z   -
     * D register indexed, x_
     * E register indexed, y.
     * F register indexed, z,
     * 10 none             " " 
     */


    /*
     * REGISTER SELECT (IN OCTAL):
     * 0 A
     * 1 B
     * 2 X
     * 3 Y
     * 4 Z
     * 5 F
     * 6 H
     * 7 NONE
     */


    /*
     * ADD$_A 000000FF ;adds 0xFF to the register A
     * 
     */
    switch(str2int(cmd.c_str())){

        case str2intc("NOP"):
        data[0] = 0x0000;
        break;
    }


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
        case '+':
        data[1] = 0x05;
        break;
        case '~':
        data[1] = 0x06;
        break;
        case '<':
        data[1] = 0x07;
        break;
        case '>':
        data[1] = 0x08;
        break;
        case '@':
        data[1] = 0x09;
        break;
        case '^':
        data[1] = 0x0A;
        break;
        case '*':
        data[1] = 0x0B;
        break;
        case '-':
        data[1] = 0x0C;
        break;
        case '_':
        data[1] = 0x0D;
        break;
        case '.':
        data[1] = 0x0E;
        break;
        case ',':
        data[1] = 0x0F;
        break;
        case ' ':
        data[1] = 0x10;
        break;
    }
    data[1] = data[1] << 8;
    
    
    cmd = line[4];
    cmd += line[5];

    switch(line[4]){


    }
    
    return data;
}



uint16_t* compile(string code){
    uint16_t data[65535];
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

        convert(line);

        #ifdef DEBUG
        printf("\n");
        #endif 
    }

    return 0;
}



