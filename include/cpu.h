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
    
    u8 interrupt;
    
} CPU;

u8 CPU_pack_flags() {
    return
          CPU.C        +
        ( CPU.Z << 1 ) +
        ( CPU.I << 2 ) +
        ( CPU.D << 3 ) +
        ( CPU.B << 4 ) +
        0b00100000     + // 0x20 or 32
        ( CPU.V << 6 ) +
        ( CPU.N << 7 );
}

void CPU_unpack_flags( u8 value ) {
    CPU.C =  value       & 1;
    CPU.Z = (value >> 1) & 1;
    CPU.I = (value >> 2) & 1;
    CPU.D = (value >> 3) & 1;
    CPU.B = (value >> 4) & 1;
    CPU.V = (value >> 6) & 1;
    CPU.N = (value >> 7) & 1;
}

u16 CPU_read_u16( u16 address ) {
    //               MSB                         LSB
    return (MEM.buffer[address+1] << 8) + MEM.buffer[address];
}

u8 CPU_read_u8( u16 address ) {
    return MEM.buffer[address];
}


void CPU_write_u8( u16 address, u8 value ) {
    MEM.buffer[address] = value;
}

void CPU_write_u16( u16 address, u16 value ) {
    MEM.buffer[address]   = value & 0xFF; // LSB
    MEM.buffer[address+1] = value >> 8;   // MSB
}

u8 CPU_fetch_u8() {
    return CPU_read_u8( CPU.PC++ );
}

u16 CPU_fetch_u16() {
    CPU.PC += 2;
    return CPU_read_u16( CPU.PC-2 );
}

void CPU_stack_push_u8( u8 value ) {
    // printf("-> %02X\n", value);
    CPU_write_u8( CPU.SP+0x100, value );
    CPU.SP--;
}

void CPU_stack_push_u16( u16 value ) {
    // printf("-> %02X\n", value);
    CPU_write_u16( CPU.SP+0x100, value );
    CPU.SP -= 2;
}

u8 CPU_stack_pull_u8() {
    CPU.SP++;
    // printf("<- %02X\n", CPU_read_u8( CPU.SP+0x100));
    return CPU_read_u8( CPU.SP+0x100);
}

u16 CPU_stack_pull_u16() {
    CPU.SP += 2;
    // printf("<- %02X\n", CPU_read_u16( CPU.SP+0x100));
    return CPU_read_u16( CPU.SP+0x100);
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

    CPU.interrupt = 0;
}

// CPU set generic flags
void CPU_sgf( u8 value ) {
    CPU.Z = ( value == 0 );             // Set Zero Flag if value is 0
    CPU.N = ( 0b10000000 & value ) > 0; // Set Negative Flag if 7th bit is 1
}

u8 CPU_get_IM() {
    return CPU_fetch_u8();
}

u8 CPU_get_ZP(u8 offset) {
    u8 zpaddr = CPU_fetch_u8();
    return CPU_read_u8(zpaddr+offset);
}

void CPU_set_ZP( u8 value, u8 offset ) {
    CPU_write_u8(CPU_fetch_u8()+offset, value);
}

// Delta refers to value change (e.g. added to value), offset refers to address lookup offset
u8 CPU_modify_ZP( u8 delta, u8 offset ) {
    u8 addr  = CPU_fetch_u8()+offset;
    u8 value = CPU_read_u8(addr)+delta;
    CPU_write_u8( addr, value );
    return value;
}

u8 CPU_get_ABS(u8 offset) {
    u16 absaddr = CPU_fetch_u16();
    return CPU_read_u8(absaddr+offset);
}

void CPU_set_ABS( u8 value, u8 offset ) {
    CPU_write_u8(CPU_fetch_u16()+offset, value);
}

u8 CPU_modify_ABS( u8 delta, u8 offset ) {
    u16 addr = CPU_fetch_u16()+offset;
    u8 value = CPU_read_u8(addr)+delta;
    CPU_write_u8( addr, value );
    return value;
}

u8 CPU_get_IDR(u8 X, u8 Y) {
    return CPU_read_u16( CPU_read_u16( CPU_fetch_u8() + X ) + Y );
}

void CPU_set_IDR(u8 value, u8 X, u8 Y) {
    return CPU_write_u8( CPU_read_u16( CPU_fetch_u8() + X ) + Y, value );
}


void CPU_LD( u8* dest, u8 value ) {
    CPU_sgf(value);
    *dest = value;
}

void CPU_JSR() {
    CPU_stack_push_u16( CPU.PC+2 );
    CPU.PC = CPU_fetch_u16();
}

void CPU_BRK() {
    CPU_stack_push_u16( CPU.PC );
    CPU_stack_push_u16( CPU_pack_flags() );

    CPU.B = 1;
    CPU.PC = CPU_read_u16( 0xFFFE );
}


void CPU_RTI() {
    CPU_unpack_flags( CPU_stack_pull_u16() );
    CPU.PC = CPU_stack_pull_u16();
}

void CPU_ADC( u8 value ) {
    u16 sum = CPU.A;
    u8 samesigns = !( (CPU.A ^ value) & 0x80 );

    sum += value + CPU.C;
    CPU.A = sum & 0xFF;

    // Set flags
    CPU.C = sum > 0xFF;
    CPU.V = samesigns && ( ( CPU.A ^ value ) );
    CPU_sgf( CPU.A );
}


void CPU_execute() {
    if ( CPU.interrupt ) { CPU_BRK(); CPU.interrupt = 0; }
    u8 ins = CPU_fetch_u8();
    printf(
        "PC: %02X INS: %02X A: %02X X: %02X Y: %02X C: %02X Z: %02X I: %02X D: %02X B: %02X V: %02X N: %02X SP: %02X\n",
        CPU.PC-1, ins, CPU.A, CPU.X, CPU.Y, CPU.C, CPU.Z, CPU.I, CPU.D, CPU.B, CPU.V, CPU.N, CPU.SP
    );
    switch (ins) {
        case INS_ADC_IM : CPU_ADC( CPU_get_IM() );                 break; // ADC
        case INS_ADC_ZP : CPU_ADC( CPU_get_ZP(0) );                break;
        case INS_ADC_ZPX: CPU_ADC( CPU_get_ZP(CPU.X) );            break;
        case INS_ADC_ABS: CPU_ADC( CPU_get_ABS(0) );               break;
        case INS_ADC_ABX: CPU_ADC( CPU_get_ABS(CPU.X) );           break;
        case INS_ADC_ABY: CPU_ADC( CPU_get_ABS(CPU.Y) );           break;
        case INS_ADC_IX : CPU_ADC( CPU_get_IDR(CPU.X, 0) );        break;
        case INS_ADC_IY : CPU_ADC( CPU_get_IDR(0, CPU.Y) );        break;

        case INS_BRK    : CPU_BRK();                               break; // BRK

        case INS_CLC    : CPU.C = 0;                               break; // CLC

        case INS_LDA_IM : CPU_LD( &CPU.A, CPU_get_IM() );          break; // LDA
        case INS_LDA_ZP : CPU_LD( &CPU.A, CPU_get_ZP(0) );         break;
        case INS_LDA_ZPX: CPU_LD( &CPU.A, CPU_get_ZP(CPU.X) );     break;
        case INS_LDA_ABS: CPU_LD( &CPU.A, CPU_get_ABS(0) );        break;
        case INS_LDA_ABX: CPU_LD( &CPU.A, CPU_get_ABS(CPU.X) );    break;
        case INS_LDA_ABY: CPU_LD( &CPU.A, CPU_get_ABS(CPU.Y) );    break;
        case INS_LDA_IX : CPU_LD( &CPU.A, CPU_get_IDR(CPU.X, 0) ); break;
        case INS_LDA_IY : CPU_LD( &CPU.A, CPU_get_IDR(0, CPU.Y) ); break;

        case INS_LDX_IM:  CPU_LD( &CPU.X, CPU_get_IM() );          break; // LDX
        case INS_LDX_ZP:  CPU_LD( &CPU.X, CPU_get_ZP(0) );         break;
        case INS_LDX_ZPY: CPU_LD( &CPU.X, CPU_get_ZP(CPU.Y) );     break;
        case INS_LDX_ABS: CPU_LD( &CPU.X, CPU_get_ABS(0) );        break;
        case INS_LDX_ABY: CPU_LD( &CPU.X, CPU_get_ABS(CPU.Y) );    break;

        case INS_LDY_IM : CPU_LD( &CPU.Y, CPU_get_IM() );          break; // LDY
        case INS_LDY_ZP : CPU_LD( &CPU.Y, CPU_get_ZP(0) );         break;
        case INS_LDY_ZPX: CPU_LD( &CPU.Y, CPU_get_ZP(CPU.X) );     break;
        case INS_LDY_ABS: CPU_LD( &CPU.Y, CPU_get_ABS(0) );        break;
        case INS_LDY_ABX: CPU_LD( &CPU.Y, CPU_get_ABS(CPU.X) );    break;

        case INS_INC_ZP : CPU_sgf( CPU_modify_ZP( 1, 0 ) );        break; // INC
        case INS_INC_ZPX: CPU_sgf( CPU_modify_ZP( 1, CPU.X ) );    break;
        case INS_INC_ABS: CPU_sgf( CPU_modify_ABS( 1, 0 ) );       break;
        case INS_INC_ABX: CPU_sgf( CPU_modify_ABS( 1, CPU.X ) );   break;

        case INS_INX    : CPU.X++; CPU_sgf(CPU.X);                 break; // INX
        case INS_INY    : CPU.Y++; CPU_sgf(CPU.Y);                 break; // INY

        case INS_JMP_ABS: CPU.PC = CPU_fetch_u16();                break; // JMP
        case INS_JMP_IDR: CPU.PC = CPU_get_ABS(0);                 break;

        case INS_JSR    : CPU_JSR();                               break; // JSR

        case INS_PHA    : CPU_stack_push_u8(CPU.A);                break; // PHA
        case INS_PHP    : CPU_stack_push_u8(CPU_pack_flags());     break; // PHP
        case INS_PLA    : CPU_LD( &CPU.A, CPU_stack_pull_u8() );   break; // PLA
        case INS_PLP    : CPU_unpack_flags( CPU_stack_pull_u8() ); break; // PLP

        case INS_STA_ZP : CPU_set_ZP ( CPU.A, 0 );                 break; // STA
        case INS_STA_ZPX: CPU_set_ZP ( CPU.A, CPU.X );             break;
        case INS_STA_ABS: CPU_set_ABS( CPU.A, 0 );                 break;
        case INS_STA_ABX: CPU_set_ABS( CPU.A, CPU.X );             break;
        case INS_STA_ABY: CPU_set_ABS( CPU.A, CPU.Y );             break;
        case INS_STA_IX : CPU_set_IDR( CPU.A, CPU.X, 0 );          break;
        case INS_STA_IY : CPU_set_IDR( CPU.A, 0, CPU.Y );          break;

        case INS_STX_ZP : CPU_set_ZP ( CPU.X, 0 );                 break; // STX
        case INS_STX_ZPY: CPU_set_ZP ( CPU.X, CPU.Y );             break;
        case INS_STX_ABS: CPU_set_ABS( CPU.X, 0 );                 break;

        case INS_STY_ZP : CPU_set_ZP ( CPU.Y, 0 );                 break; // STY
        case INS_STY_ZPX: CPU_set_ZP ( CPU.Y, CPU.X );             break;
        case INS_STY_ABS: CPU_set_ABS( CPU.Y, 0 );                 break;

        case INS_RTI    : CPU_RTI();                               break; // RTI
        case INS_RTS    : CPU.PC = CPU_stack_pull_u16();           break; // RTS

        default:                                                   break;
    }
}


#endif