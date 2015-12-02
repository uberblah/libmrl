#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mrl/exec/emu/processor.h>

emu_processor* emup_create(emu_instruction* iset, uint32_t memsize)
{
  //allocate and build the device
  emu_device* device = (emu_device*)malloc(sizeof(emu_device));
  if(!device) return NULL;
  device->mem = malloc(memsize);
  if(!device->mem)
  {
    free(device);
    return NULL;
  }
  device->memsize = memsize;
  device->irq_cb = NULL;
  device->cc_cb = NULL;
  device->dc_cb = NULL;
  //allocate, link and build the processor
  emu_processor* proc = (emu_processor*)malloc(sizeof(emu_processor));
  if(!proc)
  {
    free(device);
    free(device->mem);
    return NULL;
  }
  device->data = proc; //device refers to processor
  proc->device = device; //processor refers to device
  proc->ip = 0; //zero the instruction pointer
  int i = 0; //fill in instruction set
  if(iset) for(; i < 256; i++) proc->iset[i] = iset[i];
  else for(; i < 256; i++) proc->iset[i] = NULL;
  //zero out the registers
  for(i = 0; i < 128; i++) proc->regs[i] = 0;
  
  return proc;
}

void emup_free(emu_processor* proc)
{
  emu_device* dev = proc->device;
  if(dev)
  {
    emu_board* board = dev->board;
    //if we're connected to a board, deal with that
    if(board) emub_disconnect(board, dev->id);
    if(dev->mem) free(dev->mem);
    dev->memsize = 0;
    dev->board = NULL;
    dev->mem = NULL;
    dev->irq_cb = NULL;
    dev->cc_cb = NULL;
    dev->dc_cb = NULL;
    dev->data = NULL;
    dev->id = 0;
    free(dev);
  }
  proc->device = NULL;
  int i = 0;
  for(; i < 256; i++) proc->iset[i] = NULL;
  for(i = 0; i < 128; i++) proc->regs[i] = 0;
  free(proc);
}

void emup_step(emu_processor* proc)
{
  emu_device* dev = proc->device; //get device
  if(!dev) return; //check device null
  void* mem = dev->mem; //get memory
  if(!mem) return; //check memory null
  if(dev->memsize <= proc->ip) return; //check memory size
  proc->iset[((uint8_t*)mem)[proc->ip]](proc); //execute
}

/*
the first 5 bits of a register ID indicate the super-register
the last 3 bits indicate which section of that super-register

there are 32 super-registers, and each is 4 bytes
each super-register has 4 bytes, 2 shorts, 1 long, 1 float

the first bit indicates whether the section is a byte
the second bit indicates whether the section is a short,
  if the first bit was a zero
the third bit indicates whether the section is a float,
  if the first and second bits were both zero
if all three bits are zero, it's an integer
*/
static const uint8_t last3 = 0x07;
static const uint8_t middle5 = 0x7C;

int emup_regtype(uint8_t regid)
{
  uint8_t typepart = regid & last3;
  if(typepart & 0x04) return EMU_REGTYPE_INT8;
  if(typepart & 0x02) return EMU_REGTYPE_INT16;
  if(typepart & 0x01) return EMU_REGTYPE_FLOAT;
  return EMU_REGTYPE_INT32;
}

uint32_t emup_regsize(uint8_t regid)
{
  if(regid & 0x04) return 1;
  if(regid & 0x02) return 2;
  return 4;
}

void emup_regset(emu_processor* proc, uint8_t regid, void* val)
{
  uint32_t offset = (regid >> 1) & middle5;
  uint32_t add = 0;
  uint32_t size = 4;
  if(regid & 0x04)
  {
    size = 1;
    add = regid & 0x03;
  }
  else if(regid & 0x02)
  {
    size = 2;
    add = 2 * (regid & 0x01);
  }
  offset += add;
  memmove((void*)(proc->regs + offset), val, size);
}

void emup_regget(emu_processor* proc, uint8_t regid, void* out)
{
  uint32_t offset = (regid >> 1) & middle5;
  uint32_t add = 0;
  uint32_t size = 4;
  if(regid & 0x04)
  {
    size = 1;
    add = regid & 0x03;
  }
  else if(regid & 0x02)
  {
    size = 2;
    add = 2 * (regid & 0x01);
  }
  offset += add;
  memmove(out, (void*)(proc->regs + offset), size);
}
