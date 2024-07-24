
enum {
    INS_ADC_IM  = 0x69, // ADC
    INS_ADC_ZP  = 0x65,
    INS_ADC_ZPX = 0x75,
    INS_ADC_ABS = 0x6D,
    INS_ADC_ABX = 0x7D,
    INS_ADC_ABY = 0x79,
    INS_ADC_IX  = 0x61,
    INS_ADC_IY  = 0x71,

    INS_BRK     = 0x00, // BRK

    INS_CLC     = 0x18, // CLC

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

    INS_INC_ZP  = 0xE6, // INC
    INS_INC_ZPX = 0xF6,
    INS_INC_ABS = 0xEE,
    INS_INC_ABX = 0xFE,

    INS_INX     = 0xE8, // INX
    INS_INY     = 0xC8, // INY

    INS_JSR     = 0x20, // JSR

    INS_JMP_ABS = 0x4C, // JMP
    INS_JMP_IDR = 0x6C,

    INS_PHA     = 0x48, // PHA
    INS_PHP     = 0x08, // PHP
    INS_PLA     = 0x68, // PLA
    INS_PLP     = 0x28, // PLP

    INS_STA_ZP  = 0x85, // STA
    INS_STA_ZPX = 0x95,
    INS_STA_ABS = 0x8D,
    INS_STA_ABX = 0x9D,
    INS_STA_ABY = 0x99,
    INS_STA_IX  = 0x81,
    INS_STA_IY  = 0x91,

    INS_STX_ZP  = 0x86, // STX
    INS_STX_ZPY = 0x96,
    INS_STX_ABS = 0x8E,

    INS_STY_ZP  = 0x84, // STY
    INS_STY_ZPX = 0x94,
    INS_STY_ABS = 0x8C,

    INS_RTI     = 0x40, // RTI
    INS_RTS     = 0x60, // RTS
};
    