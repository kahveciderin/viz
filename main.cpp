
#include "functions.h"


int main(){
    virtualmachine* machinestate;
    uint16_t* a = compile("ADD$NA 000000FF\nAND$NA DEADFADE\n");
    printf("%x\n%x\n%x\n%x\n",a[0],a[1],a[2],a[3]);
    printf("%x\n%x\n%x\n%x\n",a[4],a[5],a[6],a[7]);
    //machinestate->addrspace = a;
    //run(machinestate);
    return 0;
}