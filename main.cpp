
#include "functions.h"


int main(){
    /* initialize random seed: */
    srand (time(NULL));
    
    virtualmachine machinestate;
    machinestate.sp = 0xFF;
    uint16_t* a = compile("INP#NA 00000000\nOUT#AA 00680067\n");
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