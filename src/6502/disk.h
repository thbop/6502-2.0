#ifndef DISK_H
#define DISK_H

struct {
    char *BIOS_filename;
    char *FLOPPY_filename;
} DISK;

void DISK_Initialize( char *BIOS_filename, char *FLOPPY_filename ) {
    DISK.BIOS_filename   = BIOS_filename;
    DISK.FLOPPY_filename = FLOPPY_filename;
}

bool DISK_Load_BIOS( size_t offset ) {
    FILE* fp = fopen(DISK.BIOS_filename, "rb");
    if ( fp == NULL ) {
        printf("ERROR: file \"%s\" not found!\n", DISK.BIOS_filename);
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

bool DISK_Read_Sectors(u16 lba, u16 count, u16 destBuffer) {
    FILE* fp = fopen(DISK.FLOPPY_filename, "rb");
    if ( fp == NULL ) {
        printf("ERROR: file \"%s\" not found!\n", DISK.FLOPPY_filename);
        return false;
    }

    size_t size = count*512;

    if ( fread(MEM.buffer+destBuffer, sizeof(u8), size, fp) != size ) // Read sectors
        return false;

    fclose(fp);
    return true;
}

#endif