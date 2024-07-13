#ifndef CPU_H
#define CPU_H

struct {
    u16 PC;         // Program Counter
    u8 SP, A, X, Y; // Stack Pointer, Accumulator, X, and Y
    u8 C : 1,       // Carry Flag
       Z : 1,       // Zero Flag
       I : 1,       // Interrupt Disable
       D : 1,       // Decimal Mode Flag
       B : 1,       // Break Command
       V : 1,       // Overflow Flag
       N : 1;       // Negative Flag
    
} CPU;

u16 CPU_read_u16( u16 address ) {
    //               MSB                         LSB
    return (MEM.buffer[address] << 8) + MEM.buffer[address-1];
}

u8 CPU_read_u8( u16 address ) {
    return MEM.buffer[address-1];
}

u8 CPU_fetch_u8() {
    return CPU_read_u8( CPU.PC++ );
}

u16 CPU_fetch_u16() {
    CPU.PC += 2;
    return CPU_read_u16( CPU.PC-2 );
}

void CPU_reset() {
    // Reset PC and set SP
    CPU.PC = CPU_read_u16( 0xFFFC );
    CPU.SP = 0xFF;

    // Reset Registers
    CPU.A = CPU.X =
    CPU.Y = 0;

    // Reset Flags
    CPU.C = CPU.Z =
    CPU.I = CPU.D =
    CPU.B = CPU.V =
    CPU.N = 0;
}

void CPU_set_generic_flag( u8 value ) {
    CPU.Z = ( value == 0 );          // Set Zero Flag if value is 0
    CPU.N = ( 0b10000000 && value ); // Set Negative Flag if 7th bit is 1
}

u8 CPU_get_IM() {
    return CPU_fetch_u8();
}

u8 CPU_get_ZP(u8 offset) {
    u8 zpaddr = CPU_fetch_u8();
    return CPU_read_u8(zpaddr+offset);
}

u8 CPU_get_ABS(u8 offset) {
    u16 absaddr = CPU_fetch_u16();
    return CPU_read_u8(absaddr+offset);
}

void CPU_LD( u8* dest, u8 value ) {
    CPU_set_generic_flag(value);
    *dest = value;
}

void CPU_execute() {
    u8 ins = CPU_fetch_u8();
    // printf("PC: %X INS: %X A: %X\n", CPU.PC-1, ins, CPU.A);
    switch (ins) {
        case INS_LDA_IM:  CPU_LD( &CPU.A, CPU_get_IM() );          break; // LDA
        case INS_LDA_ZP:  CPU_LD( &CPU.A, CPU_get_ZP(0) );         break;
        case INS_LDA_ZPX: CPU_LD( &CPU.A, CPU_get_ZP(CPU.X) );     break;
        case INS_LDA_ABS: CPU_LD( &CPU.A, CPU_get_ABS(0) );        break;
        case INS_LDA_ABX: CPU_LD( &CPU.A, CPU_get_ABS(CPU.X) );    break;
        case INS_LDA_ABY: CPU_LD( &CPU.A, CPU_get_ABS(CPU.Y) );    break;
        // Incomplete

        case INS_LDX_IM:  CPU_LD( &CPU.X, CPU_get_IM() );          break; // LDX
        case INS_LDX_ZP:  CPU_LD( &CPU.X, CPU_get_ZP(0) );         break;
        case INS_LDX_ZPY: CPU_LD( &CPU.X, CPU_get_ZP(CPU.Y) );     break;
        case INS_LDX_ABS: CPU_LD( &CPU.X, CPU_get_ABS(0) );        break;
        case INS_LDX_ABY: CPU_LD( &CPU.X, CPU_get_ABS(CPU.Y) );    break;

        case INS_JMP_ABS: CPU.PC = CPU_fetch_u16();                break; // JMP
        case INS_JMP_IDR: CPU.PC = CPU_get_ABS(0);                 break;
    
        default:                                                   break;
    }
}


#endif