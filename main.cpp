
#include "functions.h"


int main(int argc, char* argv[]){
    /* initialize random seed: */
    
    srand (time(NULL));
    string data;
    virtualmachine machinestate;
    machinestate.sp = 0xFF;
    ifstream file(argv[1]);
    
    string line ;
    while( getline( file, line ) )
    {
        data += line;
        data += "\n";
    }

    //printf("%s", data.c_str());

    //uint16_t* a = compile("NOP#NN 0000 0000\n:str\nNOP#NN 0000 0000\nJMP#NN 0005 .str\n");

    uint16_t* a = compile(data + "\n");

    //for(int x = 0; x < 65535; x++){
    //    printf("0x%x\n", a[x]);
    //}
    machinestate.push = false;
    machinestate.halt = false;
    machinestate.addrspace = a;

    while(true){
        run(&machinestate);
        check(&machinestate);
        if(machinestate.halt)   break;
    }
    printf("\n");
        
    return 0;
}