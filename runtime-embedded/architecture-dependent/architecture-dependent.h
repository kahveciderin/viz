//Implement this interface for your embedded machine to port the VIZ runtime to your machine.

#include <stdint.h>
//Gets memory for the VIZ program. The maximum size for memory is 0x20000 (sizeof(uint16_t) * 0x10000). The memory range FF00-FFFF must be valid for the stack to function.
uint16_t *init_memspace(void);
//Retrieves and loads the VIZ binary into the machine memory.
void load_program(uint16_t *memspace);
