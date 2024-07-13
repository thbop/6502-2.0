// General includes
#include <stdio.h>
#include <string.h>

// Global typedefs
typedef unsigned char  u8;
typedef unsigned short u16;

// Custom headers
#include "include/memory.h"
#include "include/instructions.h"
#include "include/cpu.h"

// Main program
int main(int argc, char** argv) {
    if ( argc > 1 ) {
        if ( MEM_load_ROM(argv[1]) ) return 1;
    }
    else {
        printf("ERROR: File argument not supplied!\n");
        return 1;
    }

    CPU_reset();

    CPU_execute();

    printf("%x\n", CPU.A);


    return 0;
}