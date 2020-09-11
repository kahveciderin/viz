switch(str2int(cmd.c_str())){

    case str2intc("NOP"):
    data[0] = 0x0000;
    break;
    case str2intc("ADD"):
    data[0] = 0x0001;
    break;
    case str2intc("SUB"):
    data[0] = 0x0002;
    break;
    case str2intc("MUL"):
    data[0] = 0x0003;
    break;
    case str2intc("DIV"):
    data[0] = 0x0004;
    break;
    case str2intc("CMP"):
    data[0] = 0x0005;
    break;
    case str2intc("JMP"):
    data[0] = 0x0006;
    break;
    case str2intc("GFX"):
    data[0] = 0x0007;
    break;
}