// General includes
#include <stdio.h>
#include <string.h>
#include <pthread.h>

// Global typedefs
typedef unsigned char  u8;
typedef unsigned short u16;

// Custom headers
#include "include/memory.h"
#include "include/instructions.h"
#include "include/cpu.h"

void execute() {
    while (1) CPU_execute();
}

// Main program
int main(int argc, char** argv) {
    // if ( argc > 1 ) {
    //     if ( MEM_load_ROM(argv[1]) ) return 1;
    // }
    // else {
    //     printf("ERROR: File argument not supplied!\n");
    //     return 1;
    // }
    if ( MEM_load_ROM("sys.out") ) return 1;

    CPU_reset();


    // pthread_t thread_id;
    // pthread_create(&thread_id, NULL, execute, NULL);

    // while (1) {
    //     fgets(MEM.buffer+0x0200, 0xFF, stdin); // Not very accurate...
    //     CPU.interrupt = 1; while ( CPU.B );
    //     for ( int i = 0; i < 0xFF; i++ ) printf("%X ", MEM.buffer[0x300+i]);
    // }

    

    // For basic instruction testing
    // for ( int i = 0; i < 130; i++ ) {
    //     CPU_execute();
    // }

    return 0;
}