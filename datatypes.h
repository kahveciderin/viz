
class device{
    uint16_t databuffer[256];
    uint8_t datap;
    virtual uint16_t run(uint16_t buff[]){}
    uint16_t outbuff;
    public: void in(uint16_t data){
        if(data == 0){
        datap=0;
        outbuff = run(databuffer);
        }
        else{
        databuffer[datap] = data;
        }

        printf("%d", outbuff);
    }
    public: uint16_t out(){
        return outbuff;
    }
};

class externalram:device{
    uint16_t *addrspace;
    uint16_t run(uint16_t buff[]) override{
    switch(buff[0]){

        case 0x1:
        return addrspace[buff[1]];
        break;

        case 0xF:
        addrspace[buff[1]]=buff[2];
        break;
    }
    return 0;
    }
};



class networkcard:device{
    
    char address[4];
    uint16_t port;
    __socket_type protocol;
    char data[256];
    int socket_f;
    //struct sockaddr_in addr; 
    uint16_t run(uint16_t buff[]) override{


        switch(buff[0]){
            case 0x0001: //TCP socket
            protocol = SOCK_STREAM;
            address[0] = (buff[1] & 0xFF00) >> 8;
            address[1] = buff[1] & 0xFF;
            address[2] = (buff[2] & 0xFF00) >> 8;
            address[3] = buff[2] & 0xFF;
            port = buff[3];
            //addr.sin_family = AF_INET; 
	        //addr.sin_addr.s_addr = 0; 
	        //addr.sin_port = htons( port ); 
	
            //bind(socket_f, (struct sockaddr *)&addr, sizeof(addr))
            //return (socket_f = socket(AF_INET, protocol, 0));
            
            break;
            case 0x0002: //UDP socket
            protocol = SOCK_DGRAM;
            address[0] = (buff[1] & 0xFF00) >> 8;
            address[1] = buff[1] & 0xFF;
            address[2] = (buff[2] & 0xFF00) >> 8;
            address[3] = buff[2] & 0xFF;
            port = buff[3];
            return (socket_f = socket(AF_INET, protocol, 0));
            break;
            case 0x0003:

            break;

        }
        

        
        return 0;
    }
};

class gpu:device{
   
};

struct virtualmachine{

    uint16_t pc;
    uint16_t regA;
    uint16_t regB;
    uint16_t regC;
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
    device *devices[1];


};


struct label{

    char name[32];
    uint16_t addr;

};