#include "../datatypes.hpp"
#include "console.h"
#include <iostream>

using namespace device_type;

console::~console(){

}

uint16_t console::run(){
    
}
uint16_t console::out(){
    uint16_t return_value;
    scanf("%c", (char *)&return_value);
    return return_value;
}

void console::in(uint16_t data){
    printf("%c", data);
}