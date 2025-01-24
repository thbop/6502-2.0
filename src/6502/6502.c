// General includes
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
#include "memory.h"
#include "instructions.h"
#include "cpu.h"


// Main program
int main(int argc, char** argv) {
    if ( argc < 3 ) {
        printf("Syntax: <BIOS> <FLOPPY>\n");
        return -1;
    }
    printf("Loading 6502...\n");
    if ( !MEM_load_BIOS(argv[1], 0x8000) ) {
        printf("Failed to load BIOS file: \"%s\"\n", argv[1]);
        return -2;
    }
    if ( !MEM_load_BOOT(argv[2], 0x9000) ) {
        printf("Failed to load FLOPPY (BOOT) file: \"%s\"\n", argv[1]);
        return -3;
    }

    CPU_reset();

    while (true)
        CPU_execute();

    // For basic instruction testing
    // for ( int i = 0; i < 256; i++ ) {
    //     CPU_execute();
    // }

    return 0;
}