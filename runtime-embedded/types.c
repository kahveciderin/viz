#include "types.h"
#include <stdint.h>
#include <string.h>
#include "architecture-dependent/architecture-dependent.h"
void init_machine(virtualmachine_t *vm) {
    memset(vm, 0, sizeof(virtualmachine_t));
    vm->sp = 0xff;
    vm->addrspace = init_memspace();
}