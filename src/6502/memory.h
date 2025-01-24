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







#endif