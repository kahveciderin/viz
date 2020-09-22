
#include "functions.h"


int main(int argc, char* argv[]){

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


    uint16_t* a = compile(data + "\n");


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