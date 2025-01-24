#ifndef BIOS_H
#define BIOS_H

#define BIOS_CTRL             0x0200

#define BIOS_STATE_NULL       0
#define BIOS_STATE_READ_DRIVE 1
#define BIOS_STATE_PUTC       2

void BIOS_main() {
    bool ok = true;
    switch( MEM.buffer[BIOS_CTRL] ) {
        case BIOS_STATE_NULL: break;
        case BIOS_STATE_READ_DRIVE:
            u16 lba         = *(u16*)(MEM.buffer+BIOS_CTRL+1);
            u16 sectorCount = *(u16*)(MEM.buffer+BIOS_CTRL+3);
            u16 destBuffer  = *(u16*)(MEM.buffer+BIOS_CTRL+5);
            ok = DISK_Read_Sectors(lba, sectorCount, destBuffer);
            break;
        case BIOS_STATE_PUTC:
            putc(*(MEM.buffer+BIOS_CTRL+7), stdout);
            break;

    }
    if (ok) MEM.buffer[BIOS_CTRL] = 0x00;
    else    MEM.buffer[BIOS_CTRL] = 0xFF;
}

#endif