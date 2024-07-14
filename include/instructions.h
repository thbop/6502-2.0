
enum {
    INS_LDA_IM  = 0xA9, // LDA
    INS_LDA_ZP  = 0xA5,
    INS_LDA_ZPX = 0xB5,
    INS_LDA_ABS = 0xAD,
    INS_LDA_ABX = 0xBD,
    INS_LDA_ABY = 0xB9,
    INS_LDA_IX  = 0xA1,
    INS_LDA_IY  = 0xB1,

    INS_LDX_IM  = 0xA2, // LDX
    INS_LDX_ZP  = 0xA6,
    INS_LDX_ZPY = 0xB6,
    INS_LDX_ABS = 0xAE,
    INS_LDX_ABY = 0xBE,

    INS_LDY_IM  = 0xA0, // LDY
    INS_LDY_ZP  = 0xA4,
    INS_LDY_ZPX = 0xB4,
    INS_LDY_ABS = 0xAC,
    INS_LDY_ABX = 0xBC,

    INS_JMP_ABS = 0x4C, // JMP
    INS_JMP_IDR = 0x6C
};
    