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
typedef signed char    i8;
typedef unsigned char  u8;
typedef unsigned short u16;

// Custom headers
#include "memory.h"
#include "instructions.h"
#include "cpu.h"
#include "disk.h"
#include "bios.h"



// Main program
int main(int argc, char **argv) {
    printf("Loading 6502...\n");
    if ( argc < 3 ) {
        printf("Syntax: <BIOS> <FLOPPY>\n");
        return -1;
    }

    DISK_Initialize(argv[1], argv[2]);

    if ( !DISK_Load_BIOS(0x8000) ) {
        printf("Failed to load BIOS file: \"%s\"\n", argv[1]);
        return -2;
    }

    CPU_reset();

    // while (true) {
    //     CPU_execute();
    //     BIOS_main();
    // }

    // For basic instruction testing
    for ( int i = 0; i < 256; i++ ) {
        CPU_execute();
        BIOS_main();
    }

    return 0;
}