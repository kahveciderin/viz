#include "../datatypes.hpp"
#include "console.hpp"
#include <iostream>

uint16_t device_type::console::run(){
    return 0;
}
uint16_t device_type::console::out(){
    unsigned char t = 0;
    std::cin >> t;
    return t;
}

void device_type::console::in(uint16_t data){
    std::cout << static_cast<unsigned char>(data);
}