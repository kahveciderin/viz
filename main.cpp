
#include "functions.h"


int main(int argc, char* argv[]){

    srand (time(NULL));
    string data;
    virtualmachine machinestate;
    ifstream file(argv[1]);
    
    #ifdef VIZ4WEB
    #include <regex.h>        
    regex_t regex;
    int reti;
    reti = regcomp(&regex, "(?<=^>>).*", REG_EXTENDED);
    #endif  

    string line ;
    while( getline( file, line ) )
    {
        #ifdef VIZ4WEB
        reti = regexec(&regex, "abc", 0, NULL, 0);
        if (!reti) {
            char *code = new char[128];
            sprintf(code, "%.*s", line.length() - 2, line.c_str() + 2);
            
            data += code;
            data += "\n";
            delete[] code;
        }
        else if (reti == REG_NOMATCH) {
            data += "+";
            data += line;
            data += "\n";
        }
        #else
        data += line;
        data += "\n";
        #endif

    }


    uint16_t* a = compile(data + "\n");

    /*for(int i = 0; i < 65535; i++){
        printf("0x%x\n", a[i]);
    }*/
    //initscr();
    machinestate.push = false;
    machinestate.halt = false;
    machinestate.addrspace = a;
    #ifdef DEBUG
    unsigned long tinstrun = 0;
    #endif
    while(true){
        run(&machinestate);
        check(&machinestate);
        if(machinestate.halt)   break;
        #ifdef DEBUG
        tinstrun++;
        #endif
    }
    #ifdef DEBUG
    printf("\n\nTotal instructions ran: %lu\n", tinstrun);
    #else
    printf("\n");
    #endif

    
    //endwin();
    return 0;
}