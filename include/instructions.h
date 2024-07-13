
enum {
    INS_LDA_IM  = 0xA9, // LDA
    INS_LDA_ZP  = 0xA5,
    INS_LDA_ZPX = 0xB5,
    INS_LDA_ABS = 0xAD,
    INS_LDA_ABX = 0xBD,
    INS_LDA_ABY = 0xB9,
    // Incomplete

    INS_LDX_IM  = 0xA2, // LDX
    INS_LDX_ZP  = 0xA6,
    INS_LDX_ZPY = 0xB6,
    INS_LDX_ABS = 0xAE,
    INS_LDX_ABY = 0xBE,

    INS_JMP_ABS = 0x4C, // JMP
    INS_JMP_IDR = 0x6C
};
    