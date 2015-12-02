#ifndef EMU_PROCESSOR_H
#define EMU_PROCESSOR_H

#include <stdint.h>

#include <mrl/exec/emu/board.h>

//TO GET THE FULL ID OF A PARTICULAR REGISTER PART...
//EMU_REG_<REGID> | EMU_REGPART_<PARTID>

//types of registers
#define EMU_REGTYPE_INT8  0
#define EMU_REGTYPE_INT16 1
#define EMU_REGTYPE_INT32 2
#define EMU_REGTYPE_FLOAT 3
//register IDs
//there are actually up to 32 registers
//we have names for the first 26 (roman alphabet)
//each one is 4 bytes long
//these are spaced by 8 because we use the last 3 bits
//  to determine which part of the register we're using
//the first five bits are the register id
#define EMU_REG_A   0x00
#define EMU_REG_B   0x08
#define EMU_REG_C   0x10
#define EMU_REG_D   0x18
#define EMU_REG_E   0x20
#define EMU_REG_F   0x28
#define EMU_REG_G   0x30
#define EMU_REG_H   0x38
#define EMU_REG_I   0x40
#define EMU_REG_J   0x48
#define EMU_REG_K   0x50
#define EMU_REG_L   0x58
#define EMU_REG_M   0x60
#define EMU_REG_N   0x68
#define EMU_REG_O   0x70
#define EMU_REG_P   0x78
#define EMU_REG_Q   0x80
#define EMU_REG_R   0x88
#define EMU_REG_S   0x90
#define EMU_REG_T   0x98
#define EMU_REG_U   0xA0
#define EMU_REG_V   0xA8
#define EMU_REG_W   0xB0
#define EMU_REG_X   0xB8
#define EMU_REG_Y   0xC0
#define EMU_REG_Z   0xC8
#define EMU_REG_ARG 0xD0
#define EMU_REG_BP  0xD8
#define EMU_REG_SP  0xE0
#define EMU_REG_FLG 0xE8
#define EMU_REG_REM 0xF0
#define EMU_REG_OFW 0xF8
//register part IDs
//these tell you which part of a register we refer to
//I: All 4 bytes as an integer
//F: All 4 bytes as a float
//A: The first 16 bits as an integer
//B: The second 16 bits as an integer
//AA: The first byte as an integer
//AB: The second byte as an integer
//BA: The third byte as an integer
//AB: The fourth byte as an integer
#define EMU_REGPART_I  0x00
#define EMU_REGPART_F  0x01
#define EMU_REGPART_A  0x02
#define EMU_REGPART_B  0x03
#define EMU_REGPART_AA 0x04
#define EMU_REGPART_AB 0x05
#define EMU_REGPART_BA 0x06
#define EMU_REGPART_BB 0x07

//forward declaration of our emu_processor struct (see below)
typedef struct emu_processor emu_processor;
///an instruction is a callback operating on the processor
///this should include incrementing the instruction pointer
typedef void(*emu_instruction)(emu_processor*);

///the processor struct, which must be paired with a device.
///recommend construction using emup_create (see below)
struct emu_processor
{
  ///the processor's instruction set
  emu_instruction iset[256];
  ///area where register contents are stored
  uint8_t regs [128];
  ///the instruction pointer (to somewhere in shared memory)
  uint32_t ip;
  ///the device associated with this processor
  ///go through here to find memory and the board
  emu_device* device;
};

///create a processor and its device. return the processor.
///the device pointer is stored in the processor's 'device' field
emu_processor* emup_create(emu_instruction* iset, uint32_t memsize);
///free a processor and its associated device
void emup_free(emu_processor* proc);
///step the processor, by executing one instruction from memory
void emup_step(emu_processor* proc);
///get the type of a register
int emup_regtype(uint8_t regid);
///get the size of a register
uint32_t emup_regsize(uint8_t regid);
///set the value in a register, or as far as possible
void emup_regset(emu_processor* proc, uint8_t regid, void* val);
///get the value of a register
void emup_regget(emu_processor* proc, uint8_t regid, void* out);

#endif
