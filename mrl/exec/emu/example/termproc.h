#ifndef EMU_EXAMPLE_TERMPROC_H
#define EMU_EXAMPLE_TERMPROC_H

#include <mrl/exec/emu/processor.h>

//ARGUMENT ORDER: REGISTER ALWAYS FIRST, DESTINATION FIRST

#define EMUX_TP_INOP   0x00 //nop, no args
#define EMUX_TP_ISET   0x01 //put inline value in register
#define EMUX_TP_IWT    0x02 //set value at inline address
#define EMUX_TP_IRD    0x03 //get value from inline address
#define EMUX_TP_IWTR   0x04 //set value at register address
#define EMUX_TP_IRDR   0x05 //get value from register address
#define EMUX_TP_IMOV   0x06 //move value from register to register

#define EMUX_TP_IADD   0x07 //add reg2 + reg1
#define EMUX_TP_ISUB   0x08 //sub reg2 - reg1
#define EMUX_TP_IMUL   0x09 //multiply reg2 * reg1
#define EMUX_TP_IDIV   0x0A //divide reg2 / reg1

#define EMUX_TP_INOT   0x0B //take not of two registers
#define EMUX_TP_IOR    0x0C //take or of two registers
#define EMUX_TP_IAND   0x0D //take and of two registers
#define EMUX_TP_IXOR   0x0E //take xor of two registers

#define EMUX_TP_IJMP   0x0F //jump to in-line address
#define EMUX_TP_IJZ    0x10 //jump if "zero"
#define EMUX_TP_IJNZ   0x11 //jump if "not zero"
#define EMUX_TP_IJL    0x12 //jump if "sign"
#define EMUX_TP_IJLE   0x13 //jump if "sign" or "zero"
#define EMUX_TP_IJG    0x14 //jump if "not sign" and "not zero"
#define EMUX_TP_IJGE   0x15 //jump if "not sign"
#define EMUX_TP_IJS    0x16 //jump to address in register
#define EMUX_TP_IJZS   0x17 //jump if "zero"
#define EMUX_TP_IJNZS  0x18 //jump if "not zero"
#define EMUX_TP_IJLS   0x19 //jump if "sign"
#define EMUX_TP_IJLES  0x1A //jump if "sign" or "zero"
#define EMUX_TP_IJGS   0x1B //jump if "not sign" and "not zero"
#define EMUX_TP_IJGES  0x1C //jump if "not sign"

#define EMUX_TP_IPRT   0x1D //print value in register
#define EMUX_TP_IINP   0x1E //get input, place in register

#define EMUX_TP_IIRQ   0xF0 //send interrupt to board
#define EMUX_TP_IBDC   0xF1 //broadcast interrupt in board
#define EMUX_TP_IIST   0xF2 //set interrupt callback address
#define EMUX_TP_IIGT   0xF3 //get interrupt callback address

emu_processor* emux_tp_create(uint32_t memsize);

#endif
