
#include "functions.h"


int main(){
    /* initialize random seed: */
    srand (time(NULL));
    
    virtualmachine machinestate;
    machinestate.sp = 0xFF;

    machinestate.regA = 0x9964;
    machinestate.regB = 0x000A;
    uint16_t* a = compile("SUB#AB 0000 0000\n");
    machinestate.push = false;
    machinestate.addrspace = a;

        run(&machinestate);
        check(&machinestate);
        printf("0x%x\n0x%x", machinestate.regA, machinestate.regB);
    return 0;
}