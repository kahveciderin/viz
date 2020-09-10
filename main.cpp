
#include "functions.h"


int main(){
    virtualmachine* machinestate;
    uint16_t* a = compile("ADD$_A 000000FF\n");
    //printf("%x\n%x\n%x\n%x\n",a[0],a[1],a[2],a[3]);
    machinestate->addrspace = a;
    run(machinestate);
    return 0;
}