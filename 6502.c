// General includes
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#ifdef _WIN32
#include <windows.h>
#define sleep Sleep

#endif

#ifdef linux // UNTESTED
#include <unistd.h>

#endif

// Global typedefs
typedef char           i8;
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


    pthread_t thread_id;
    pthread_create(&thread_id, NULL, execute, NULL);

    sleep(10); // Let some assembly run

    // char* txt = "Hello World!";
    // for ( int i = 0; i < 13; i++ ) MEM.buffer[i+0x0200] = txt[i];
    // CPU.interrupt = 1; sleep(10);
    // for ( int i = 0; i < 0xFF; i++ ) printf("%c", MEM.buffer[i+0x0300]);

    while (1) {
        for ( int i = 0; i < 0xFF; i++ ) printf("%c", MEM.buffer[i+0x0300]);

        fgets(MEM.buffer+0x0200, 0xFF, stdin);                 // Not very accurate...
        MEM.buffer[0x0200+strlen(MEM.buffer+0x0200)-1] = '\0'; // Get rid of \n

        CPU.interrupt = 1; sleep(10);
    }

    

    // For basic instruction testing
    // for ( int i = 0; i < 256; i++ ) {
    //     CPU_execute();
    // }

    return 0;
}