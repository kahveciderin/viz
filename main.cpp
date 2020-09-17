
#include "functions.h"


int main(){
    /* initialize random seed: */
    srand (time(NULL));
    
    virtualmachine machinestate;
    machinestate.sp = 0xFF;

    uint16_t* a = compile("JMP#NN 0000 0058\nPSH#BN 0000 0000\nPSH#XN 0000 0000\nMOV#NB 0000 0000\nMOV#NX 0000 0000\nADD#BN 0000 0001\nMOV#AX 0000 0000\nDIV#AN 0000 000A\nMOD#XN 0000 000A\nADD#XN 0000 0030\nPSH#XN 0000 0000\nJOZ#AN 0000 0034\nJMP#NN 0000 0014\nSUB#BN 0000 0001\nPOP#NX 0000 0000\nOUT#XN 0000 0000\nJOZ#BN 0000 0048\nJMP#NN 0000 0034\nOUT#NN 000A 000D\nPOP#NX 0000 0000\nPOP#NB 0000 0000\nPOP#NI 0000 0000\nMOV#NA 0034 0000\nPSH#NN 0064 0000\nJMP#NN 0000 0004\nJMP#NI 0000 0000\n");
    machinestate.push = false;
    machinestate.addrspace = a;


        while(true){
            run(&machinestate);
            check(&machinestate);
        }
        
    return 0;
}