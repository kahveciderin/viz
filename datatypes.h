struct virtualmachine{

    uint16_t pc;
    uint16_t regA;
    uint16_t regB;
    uint16_t regX;
    uint16_t regY;
    uint16_t regZ;
    uint16_t regF;
    uint16_t regH;
    uint8_t sp;
    uint16_t *addrspace;
    uint16_t tmpstack;
    bool push;
    uint16_t null;
    uint16_t fixed0;
    uint16_t fixed1;
    bool halt;

};

struct label{

    char name[32];
    uint16_t addr;

};