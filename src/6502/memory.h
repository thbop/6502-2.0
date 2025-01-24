#ifndef MEMORY_H
#define MEMORY_H

struct {
    u8 buffer[0x10000];
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

bool MEM_load_ROM( char* filename ) {
    FILE* fp = fopen(filename, "rb");
    if ( fp == NULL ) {
        printf("ERROR: file \"%s\" not found!\n", filename);
        return false;
    }

    for ( int i = 0; i < 0x10000; i++ ) {
        MEM.buffer[i] = fgetc(fp);
    }

    fclose(fp);
    return true;
}

bool MEM_load_BIOS( char* filename, size_t offset ) {
    FILE* fp = fopen(filename, "rb");
    if ( fp == NULL ) {
        printf("ERROR: file \"%s\" not found!\n", filename);
        return false;
    }
    
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp) - 6; // Save the vectors at the end instead of offset
    fseek(fp, 0, SEEK_SET);

    if ( fread(MEM.buffer+offset, sizeof(u8), size, fp) != size ) // Read the BIOS
        return false;
    
    if ( fread(MEM.buffer+0xFFFA, sizeof(u8), 6, fp) != 6 )       // Read the vectors
        return false;

    fclose(fp);
    return true;
}

bool MEM_load_BOOT( char* filename, size_t offset ) {
    FILE* fp = fopen(filename, "rb");
    if ( fp == NULL ) {
        printf("ERROR: file \"%s\" not found!\n", filename);
        return false;
    }
    
    if ( fread(MEM.buffer+offset, sizeof(u8), 512, fp) != 512 )
        return false;

    fclose(fp);
    return true;
}

#endif