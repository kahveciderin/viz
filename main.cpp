
#include "functions.h"


int main(){
    virtualmachine machinestate;
    machinestate.sp = 0xFF;
    uint16_t* a = compile("ADD$NA 000000FF\nAND$NB DEADBEEF\n");
    machinestate.push = false;
    machinestate.addrspace = a;

    
        run(&machinestate);
        check(&machinestate);
        printf("\n\n=========================\n\n");
        run(&machinestate);
        check(&machinestate);
        printf("\n\n=========================\n\n");
    
    return 0;
}