#ifndef MEMORY_H
#define MEMORY_H

struct {
    u8 buffer[0xFFFF];
    // 0000 - 00FF = Zero Page                          (RAM)
    // 0100 - 01FF = System Stack                       (RAM)
    // 0200 - 7FFF = RAM
    // 8000 - FFF9 = ROM
    // FFFA - FFFB = u16* nonmaskable_interrupt_handler (ROM)
    // FFFC - FFFD = u16* reset_location                (ROM)
    // FFFE - FFFF = u16* BRK_interrupt_handler         (ROM)
} MEM;


// void MEM_reset() {
//     memset(MEM.buffer, 0, 0xFFFF);
// }

int MEM_load_ROM( char* filename ) {
    FILE* fp = fopen(filename, "rb");
    if ( fp == NULL ) {
        printf("ERROR: file \"%s\" not found!\n", filename);
        return 1;
    }

    for ( int i = 0; i < 0xFFFF; i++ ) {
        MEM.buffer[i] = fgetc(fp);
        if ( MEM.buffer[i] )
            printf("%x\n", MEM.buffer[i]);
    }

    fclose(fp);
    return 0;
}

#endif