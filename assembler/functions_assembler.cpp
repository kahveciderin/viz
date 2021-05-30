#include "definitions.h"
#include "switch.h"
#include <string>
#include <cstring>
unsigned int str2int(const char *str, int h) {
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}
uint16_t *convert(std::string line) {
    static uint16_t data[4];
    /*
    * (As hex)
    * First four digits are opcodes
    * Next two digits are addressing modes
    * Next two digits are register select (in which register the result will be)
    * Next eight digits are data (little endian)
    */
    std::string cmd;
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

    data[0] = opcode_to_code(cmd);

    switch (line[3]) {
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

    switch (line[4]) {
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
    case 'a':
        data[1] += 0xA;
        break;
    case 'b':
        data[1] += 0xB;
        break;
    case 'z':
        data[1] += 0xC;
        break;
    case 'h':
        data[1] += 0xD;
        break;
    case 'n':
        data[1] += 0xE;
        break;
    case 'c':
        data[1] += 0xF;
        break;
    }

    data[1] = data[1] << 4;

    switch (line[5]) {
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
    case 'a':
        data[1] += 0xA;
        break;
    case 'b':
        data[1] += 0xB;
        break;
    case 'z':
        data[1] += 0xC;
        break;
    case 'h':
        data[1] += 0xD;
        break;
    case 'n':
        data[1] += 0xE;
        break;
    case 'c':
        data[1] += 0xF;
        break;
    }

    if (line[6] == ' ') {
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
uint16_t *compile(std::string code, uint16_t *data_size) {
    static uint16_t *data = new uint16_t[0x10000];
    uint16_t g = 0;

    label labels[0x10000];

    int q = 1;
    memcpy(labels[0].name, "", 0);
    labels[0].addr = 0x0000;
    for (int i = 0; i < code.length(); i++) {
        std::string line;

        while (code[i] != TERMINATOR) {
        std::string s;
        s = code[i];
        line.append(s);

        i++;
        }

        if (line[0] == '@') {
        if (line[1] == '!') {
            g += stoi(line.substr(2, 6), 0, 16);

        } else {
            g = stoi(line.substr(1, 5), 0, 16);
        }
        g -= 4;
        }

    #ifdef VIZ4WEB
        if (line[0] != '#' && line[0] != ':' && line[0] != '+') {
    #else
        if (line[0] != '#' && line[0] != ':') {
    #endif

        g += 4;
        }
        if (line[0] == '$') {
        // printf("%d", g);
        g += strlen(line.c_str());
        g -= 4;
        // printf(" %d\n", g);
        }

        if (line[0] == ':') {
        memcpy(labels[q].name, line.c_str() + 1, strlen(line.c_str()) - 1);
        labels[q].addr = g;
    #ifdef DEBUG
        printf("Label: %s %x\n", labels[q].name, labels[q].addr);
    #endif
        q++;
        }
    }

    g = 0;
    for (int v = 0; v < q; v++) {
        std::string fromf(labels[v].name);

        uint16_t tmpdbg = labels[v].addr;
        std::string dot = ".";
        fromf = dot.append(fromf);
        char val[32];

        sprintf(val, "%04X", tmpdbg);

        std::string tof(val);
        int index;
        while ((index = code.find(fromf + " ")) != std::string::npos) {
        code.replace(index, fromf.length(),
                    tof); // remove and replace from that position
        }
        index = 0;
        while ((index = code.find(fromf + "\n")) != std::string::npos) {
        code.replace(index, fromf.length(),
                    tof); // remove and replace from that position
        }
    }

    for (int i = 0; i < code.length(); i++) {
        std::string line;

        while (code[i] != TERMINATOR) {
        std::string s;
        s = code[i];
        line.append(s);

        i++;
        }

        if (line[0] == '@') {
        if (line[1] == '!') {
            g += stoi(line.substr(2, 6), 0, 16);
        } else {
            g = stoi(line.substr(1, 5), 0, 16);
        }
        } else if (line[0] == '$') {
        for (int f = 1; f <= strlen(line.c_str()) - 1; f++) {
            // data = (uint16_t *)realloc(data, sizeof(uint16_t) * (g + 1));
            data[g] = line[f];
            g++;
        }
        // data = (uint16_t *)realloc(data, sizeof(uint16_t) * (g + 1));
        data[g] = 0;
        g++;
        }
    #ifdef VIZ4WEB
        else if (line[0] != '#' && line[0] != ':' && line[0] != '+') {
    #else
        else if (line[0] != '#' && line[0] != ':') {
    #endif

    #ifdef DEBUG
            std::cout << line.c_str() << "\n";
    #endif

        
        uint16_t *compiled = convert(line);
        // data = (uint16_t *)realloc(data, sizeof(uint16_t) * (g + 4));
        data[g] = compiled[0];
        g++;
        data[g] = compiled[1];
        g++;
        data[g] = compiled[2];
        g++;
        data[g] = compiled[3];
        g++;
    #ifdef DEBUG
        std::cout << "\n";
    #endif
        }
    }
    *data_size = g;
    return data;
}