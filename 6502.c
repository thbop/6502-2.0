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
    MEM_load_ROM("sys.out");

    CPU_reset();

    MEM.buffer[0x0005] = 0x37;

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, execute, NULL);
    // pthread_join(thread_id, NULL);

    while (1) {
        printf("> ");
        fgets(MEM.buffer+0x0100, 0xFF, stdin);
        printf("A: %X\n", CPU.A);
    }

    // For basic instruction testing
    // for ( int i = 0; i < 10; i++ ) {
    //     CPU_execute();
    // }


    return 0;
}