switch(str2int(cmd.c_str())){
    case str2intc("NOP"):
    data[0] = 0x0;
    break;
    case str2intc("ADD"):
    data[0] = 0x1;
    break;
    case str2intc("SUB"):
    data[0] = 0x2;
    break;
    case str2intc("MUL"):
    data[0] = 0x3;
    break;
    case str2intc("DIV"):
    data[0] = 0x4;
    break;
    case str2intc("CMP"):
    data[0] = 0x5;
    break;
    case str2intc("JMP"):
    data[0] = 0x6;
    break;
    case str2intc("GFX"):
    data[0] = 0x7;
    break;
    case str2intc("AND"):
    data[0] = 0x8;
    break;
    case str2intc("NOT"):
    data[0] = 0x9;
    break;
    case str2intc("OOR"):
    data[0] = 0xa;
    break;
    case str2intc("XOR"):
    data[0] = 0xb;
    break;
    case str2intc("INP"):
    data[0] = 0xc;
    break;
    case str2intc("OUT"):
    data[0] = 0xd;
    break;
    case str2intc("RSH"):
    data[0] = 0xe;
    break;
    case str2intc("LSH"):
    data[0] = 0xf;
    break;
    case str2intc("SET"):
    data[0] = 0x10;
    break;
    case str2intc("GET"):
    data[0] = 0x11;
    break;
    case str2intc("JOZ"):
    data[0] = 0x12;
    break;
    case str2intc("RND"):
    data[0] = 0x13;
    break;
    case str2intc("MOV"):
    data[0] = 0x14;
    break;
}