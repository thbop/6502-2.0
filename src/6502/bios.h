#ifndef BIOS_H
#define BIOS_H

#define BIOS_CTRL             0x0200

#define BIOS_STATE_NULL       0
#define BIOS_STATE_READ_DRIVE 1

void BIOS_main() {
    switch( MEM.buffer[BIOS_CTRL] ) {
        case BIOS_STATE_NULL: break;
        case BIOS_STATE_READ_DRIVE:
            u16 lba         = *(u16*)(MEM.buffer+BIOS_CTRL+1);
            u16 sectorCount = *(u16*)(MEM.buffer+BIOS_CTRL+3);
            u16 destBuffer  = *(u16*)(MEM.buffer+BIOS_CTRL+5);
            DISK_Read_Sectors(lba, sectorCount, destBuffer);
            break;

    }
}

#endif