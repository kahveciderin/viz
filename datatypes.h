class device;
struct virtualmachine{

    uint16_t pc = 0;
    uint16_t regA = 0;
    uint16_t regB = 0;
    uint16_t regC = 0;
    uint16_t regX = 0;
    uint16_t regY = 0;
    uint16_t regZ = 0;
    uint16_t regF = 0;
    uint16_t regH = 0;
    uint8_t sp = 0xFF;
    uint16_t *addrspace;
    uint16_t tmpstack;
    bool push;
    uint16_t null;
    uint16_t fixed0;
    uint16_t fixed1;
    bool halt;
    device *devices[1];


};


class device{
    public: uint16_t databuffer[256];
    uint8_t datap;
    virtual uint16_t run(){ return 0; }
    virtual ~device() { }
    //virtual ~device() = 0;
    uint16_t outbuff;
    public: virtualmachine* machine;
    void init(virtualmachine * mach){
        machine = mach;
    }
    public: void in(uint16_t data){
        if(data == 0 && datap > 2){
        datap=0;
        #ifdef DEBUG
        printf("%04X %04X %04X %04X\n", databuffer[0], databuffer[1], databuffer[2], databuffer[3]);
        #endif
        outbuff = run();
        }
        else{
        databuffer[datap] = data;
        #ifdef DEBUG
        printf("Added %04X to %d", databuffer[datap], datap);
        #endif
        datap++;
        }

        //printf("%d", outbuff);
    }
    public: uint16_t out(){
        return outbuff;
    }
};

class externalram:device{
    uint16_t *addrspace = new uint16_t[65535];
    uint16_t run() override{
    uint8_t z = 0;
    char *pathbuff = (char*)malloc(sizeof(char) * 256);
    FILE *fileptr;
    uint16_t g;
    switch(databuffer[0]){

        case 0x1:
        #ifdef DEBUG
        printf("read %04X\n", databuffer[1]);
        #endif
        return addrspace[databuffer[1]];
        break;
        case 0x4F:
        #ifdef DEBUG
        printf("file read to %04X pointer %04X\n", databuffer[1], databuffer[2]);
        
        #endif
        z = 0;
        while(machine->addrspace[databuffer[2] + z] != 0){
            pathbuff[z] = machine->addrspace[databuffer[2] + z];
            z++;
        }
        fileptr = fopen(pathbuff,"rb");
        
        while(1){
        char c = fgetc(fileptr);
        if(c == EOF)
        break;
        #ifdef LITTLE
        if(g % 2 == 0){
            addrspace[databuffer[1] + (int)floor(g/2)] = c;
        }else{
            addrspace[databuffer[1] + (int)floor(g/2)] += c << 8;
        }
        #else
        if(g % 2 == 0){
            addrspace[databuffer[1] + (int)floor(g/2)] = c << 8;
        }else{
            addrspace[databuffer[1] + (int)floor(g/2)] += c;
        }
        #endif

        
        
        g++;
        }

        #ifdef DEBUG
        printf("File location: %s\n", pathbuff);
        #endif
        break;
        case 0x41:
        #ifdef DEBUG
        printf("file write to %04X pointer %04X\n", databuffer[1], databuffer[2]);
        
        #endif
        z = 0;
        while(machine->addrspace[databuffer[2] + z] != 0){
            pathbuff[z] = machine->addrspace[databuffer[2] + z];
            z++;
        }
        fileptr = fopen(pathbuff,"wb");
        

        #ifdef LITTLE
        for(int j = 0; j < 65535; j+=2){
            fputc((addrspace[j] & 0xFF), fileptr);
            fputc((addrspace[j] & 0xFF00) >> 8, fileptr);
        }
        #else
        for(int j = 0; j < 65535; j++){

            fputc((addrspace[j] & 0xFF00) >> 8, fileptr);
            fputc(addrspace[j] & 0xFF, fileptr);
        }
        #endif

        #ifdef DEBUG
        printf("File location: %s\n", pathbuff);
        #endif
        break;
        case 0xF:
        #ifdef DEBUG
        printf("write %04X to %04X\n", databuffer[1], databuffer[2]);
        #endif
        addrspace[databuffer[1]]=databuffer[2];
        break;
    }
    return 0;
    }
    ~externalram() {}
};




struct label{

    char name[32];
    uint16_t addr;

};