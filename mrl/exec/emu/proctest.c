#include <stdlib.h>
#include <stdio.h>
#include <emu/board.h>
#include <emu/processor.h>

//a basic instruction that just prints hello
void ihello(emu_processor* proc)
{
  printf("Hello!\n");
}

//try running a basic instruction a few times
void proc_instruction_test()
{
  printf("You should see \"Hello!\" three times now...\n");
  
  emu_instruction iset[256];
  int i = 0;
  for(; i < 256; i++) iset[i] = ihello;
  emu_processor* proc = emup_create(iset, 1024);
  if(!proc)
  {
    printf("OH DARN!! WE FAILED TO ALLOCATE A PROCESSOR!!\n");
    exit(EXIT_FAILURE);
  }
  for(i = 0; i < 1024; i++) ((uint8_t*)proc->device->mem)[i] = 0;
  for(i = 0; i < 3; i++) emup_step(proc);
  emup_free(proc);
}

//an instruction to move data from one register to another
void imov(emu_processor* proc)
{
  uint32_t iobuf = 0;
  uint8_t* ip = ((uint8_t*)proc->device->mem) + proc->ip;
  uint8_t src = ip[1];
  uint8_t dst = ip[2];
  emup_regget(proc, src, &iobuf);
  emup_regset(proc, dst, &iobuf);
  proc->ip += 3;
}

//flip the endianness of a uint32
uint32_t eflip(uint32_t num)
{
  uint32_t buf = num;
  uint8_t* src = (uint8_t*)(&buf);
  uint8_t* dst = (uint8_t*)(&num);
  dst += 3;
  *dst = *src;
  src++;
  dst--;
  *dst = *src;
  src++;
  dst--;
  *dst = *src;
  src++;
  dst--;
  *dst = *src;
  return num;
}

void proc_register_test()
{
  emu_instruction iset[256];
  int i = 0;
  for(; i < 256; i++) iset[i] = imov;
  emu_processor* proc = emup_create(iset, 1024);
  uint8_t* mem = proc->device->mem;

  //try placing data in a register, make sure it's there
  uint32_t iobuf = eflip(0xdeadbeef);
  emup_regset(proc, EMU_REG_A | EMU_REGPART_I, &iobuf);
  printf("should be deadbeef: %x\n", eflip(((uint32_t*)proc->regs)[0]));
  iobuf = 0; //try getting that data the automatic way
  emup_regget(proc, EMU_REG_A | EMU_REGPART_I, &iobuf);
  printf("should be deadbeef: %x\n", eflip(iobuf));

  //try copying data from one register to another using the instruction
  printf("should not be deadbeef: %x\n", eflip(((uint32_t*)proc->regs)[1]));
  mem[0] = 0x00; //mov instruction
  mem[1] = EMU_REG_A | EMU_REGPART_I; //from
  mem[2] = EMU_REG_B | EMU_REGPART_I; //to
  emup_step(proc); //execute!
  iobuf = 0; //check value at destination of mov
  emup_regget(proc, EMU_REG_B | EMU_REGPART_I, &iobuf);
  printf("should be deadbeef: %x\n", eflip(iobuf));
  printf("should be same as above: %x\n", eflip(((uint32_t*)proc->regs)[1]));

  //try copying some individual bytes between the two registers
  mem[3] = 0x00;
  mem[4] = EMU_REG_A | EMU_REGPART_AA;
  mem[5] = EMU_REG_A | EMU_REGPART_AB;
  mem[6] = 0x00;
  mem[7] = EMU_REG_B | EMU_REGPART_BA;
  mem[8] = EMU_REG_A | EMU_REGPART_BB;
  emup_step(proc);
  emup_step(proc);
  iobuf = 0;
  emup_regget(proc, EMU_REG_A | EMU_REGPART_I, &iobuf);
  printf("should be dedebebe: %x\n", eflip(iobuf));
  
  emup_free(proc);
}

int main(int argc, char** argv)
{
  proc_instruction_test();
  proc_register_test();
  
  exit(EXIT_SUCCESS);
}
