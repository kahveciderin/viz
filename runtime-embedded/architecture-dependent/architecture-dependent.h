//Implement this interface for your embedded machine to port the VIZ runtime to your machine.

#include <stdint.h>
//Gets memory for the VIZ program. The maximum size for memory is 0x20000 (sizeof(uint16_t) * 0x10000). The memory range FF00-FFFF must be valid for the stack to function.
uint16_t *init_memspace(void);
//Retrieves and loads the VIZ binary into the machine memory.
void load_program(uint16_t *memspace);
//Gets input from the port
uint16_t in(uint16_t port);
//Puts data into the output
void out(uint16_t data, uint16_t port);
//pow function, x ^ e
uint16_t pow16(uint16_t x, uint16_t e);