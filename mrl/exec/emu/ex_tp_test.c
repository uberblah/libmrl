#include <stdlib.h>
#include <stdio.h>
#include <emu/board.h>
#include <emu/processor.h>
#include <emu/example/termproc.h>

#define TEST_MEMSIZE 1024

int main(int argc, char** argv)
{
    char buf[TEST_MEMSIZE];
    emu_board* board = emub_create();
    emu_processor* proc = emux_tp_create(TEST_MEMSIZE);
    emu_device* dev = proc->device;
    emub_connect(board, dev, 0);

    //TEST THE NOP, SET AND PRINT INSTRUCTIONS
    printf(">>> you should see \"deadbeef\" and its parts\n");
    char regid = EMU_REG_A;
    int value = 0xdeadbeef;
    int li = 0;

    //SET THE VALUE OF A REGISTER
    buf[li++] = EMUX_TP_INOP;
    buf[li++] = EMUX_TP_ISET;
    buf[li++] = regid;
    buf[li++] = ((char*)&value)[0];
    buf[li++] = ((char*)&value)[1];
    buf[li++] = ((char*)&value)[2];
    buf[li++] = ((char*)&value)[3];

    //READ THE DIFFERENT PARTS OF THE REGISTER
    buf[li++] = EMUX_TP_INOP; //more random nops
    buf[li++] = EMUX_TP_INOP;
    buf[li++] = EMUX_TP_IPRT;
    buf[li++] = regid | EMU_REGPART_I;
    buf[li++] = EMUX_TP_IPRT;
    buf[li++] = regid | EMU_REGPART_A;
    buf[li++] = EMUX_TP_IPRT;
    buf[li++] = regid | EMU_REGPART_B;
    buf[li++] = EMUX_TP_INOP;
    buf[li++] = EMUX_TP_IPRT;
    buf[li++] = regid | EMU_REGPART_AA;
    buf[li++] = EMUX_TP_IPRT;
    buf[li++] = regid | EMU_REGPART_AB;
    buf[li++] = EMUX_TP_IPRT;
    buf[li++] = regid | EMU_REGPART_BA;
    buf[li++] = EMUX_TP_IPRT;
    buf[li++] = regid | EMU_REGPART_BB;

    //WRITE THE TEST TO MEMORY
    emub_write(board, 0, TEST_MEMSIZE, (void*)buf);
    //RUN THE TEST!
    proc->ip = 0;
    while(proc->ip < li)
	emup_step(proc);

    //TEST THE WRITE AND READ INSTRUCTIONS
    printf(">>> you should see beginnings of \"deadbeef\"\n");
    uint32_t addr = 0x100;
    value = 0xdeadbeef;
    li = 0;
    
    //PUT VALUE IN REGISTER
    buf[li++] = EMUX_TP_ISET;
    buf[li++] = EMU_REG_A | EMU_REGPART_I;
    buf[li++] = ((char*)&value)[0];
    buf[li++] = ((char*)&value)[1];
    buf[li++] = ((char*)&value)[2];
    buf[li++] = ((char*)&value)[3];

    //WRITE THE VALUE TO MEMORY
    buf[li++] = EMUX_TP_IWT;
    buf[li++] = EMU_REG_A | EMU_REGPART_I;
    buf[li++] = ((char*)&addr)[0];
    buf[li++] = ((char*)&addr)[1];
    buf[li++] = ((char*)&addr)[2];
    buf[li++] = ((char*)&addr)[3];

    //READ PIECES OF THE VALUE AND DISPLAY THEM
    buf[li++] = EMUX_TP_IRD;
    buf[li++] = EMU_REG_B | EMU_REGPART_AA;
    buf[li++] = ((char*)&addr)[0];
    buf[li++] = ((char*)&addr)[1];
    buf[li++] = ((char*)&addr)[2];
    buf[li++] = ((char*)&addr)[3];
    buf[li++] = EMUX_TP_IPRT;
    buf[li++] = EMU_REG_B | EMU_REGPART_AA;
    buf[li++] = EMUX_TP_IRD;
    buf[li++] = EMU_REG_C | EMU_REGPART_A;
    buf[li++] = ((char*)&addr)[0];
    buf[li++] = ((char*)&addr)[1];
    buf[li++] = ((char*)&addr)[2];
    buf[li++] = ((char*)&addr)[3];
    buf[li++] = EMUX_TP_IPRT;
    buf[li++] = EMU_REG_C | EMU_REGPART_A;
    buf[li++] = EMUX_TP_IRD;
    buf[li++] = EMU_REG_D | EMU_REGPART_I;
    buf[li++] = ((char*)&addr)[0];
    buf[li++] = ((char*)&addr)[1];
    buf[li++] = ((char*)&addr)[2];
    buf[li++] = ((char*)&addr)[3];
    buf[li++] = EMUX_TP_IPRT;
    buf[li++] = EMU_REG_D | EMU_REGPART_I;
    
    //WRITE THE TEST TO MEMORY
    emub_write(board, 0, TEST_MEMSIZE, (void*)buf);
    //RUN THE TEST!
    proc->ip = 0;
    while(proc->ip < li)
	emup_step(proc);
    
    //TEST THE WTR AND RDR INSTRUCTIONS
    printf(">>> you should see parts of \"deadbeef\"\n");
    addr = 0x200;
    value = 0xdeadbeef;
    li = 0;
    buf[li++] = EMUX_TP_ISET;
    buf[li++] = EMU_REG_R | EMU_REGPART_I;
    buf[li++] = ((char*)&addr)[0];
    buf[li++] = ((char*)&addr)[1];
    buf[li++] = ((char*)&addr)[2];
    buf[li++] = ((char*)&addr)[3];
    buf[li++] = EMUX_TP_ISET;
    buf[li++] = EMU_REG_V | EMU_REGPART_I;
    buf[li++] = ((char*)&value)[0];
    buf[li++] = ((char*)&value)[1];
    buf[li++] = ((char*)&value)[2];
    buf[li++] = ((char*)&value)[3];
    buf[li++] = EMUX_TP_IWTR;
    buf[li++] = EMU_REG_V | EMU_REGPART_I;
    buf[li++] = EMU_REG_R | EMU_REGPART_I;
    buf[li++] = EMUX_TP_IRDR;
    buf[li++] = EMU_REG_U | EMU_REGPART_I;
    buf[li++] = EMU_REG_R | EMU_REGPART_I;
    buf[li++] = EMUX_TP_IPRT;
    buf[li++] = EMU_REG_U | EMU_REGPART_I;
    
    //WRITE THE TEST TO MEMORY
    emub_write(board, 0, TEST_MEMSIZE, (void*)buf);
    //RUN THE TEST!
    proc->ip = 0;
    while(proc->ip < li)
	emup_step(proc);

    //TEST THE IMOV INSTRUCTION
    printf(">>> you should see \"beefbeef\" with a nice hole in it\n");
    addr = 0x200;
    value = 0xdeadbeef;
    li = 0;
    buf[li++] = EMUX_TP_ISET;
    buf[li++] = EMU_REG_A | EMU_REGPART_I;
    buf[li++] = ((char*)&value)[0];
    buf[li++] = ((char*)&value)[1];
    buf[li++] = ((char*)&value)[2];
    buf[li++] = ((char*)&value)[3];
    buf[li++] = EMUX_TP_ISET;
    buf[li++] = EMU_REG_B | EMU_REGPART_I;
    buf[li++] = 0;
    buf[li++] = 0;
    buf[li++] = 0;
    buf[li++] = 0;
    buf[li++] = EMUX_TP_IMOV;
    buf[li++] = EMU_REG_B | EMU_REGPART_AA;
    buf[li++] = EMU_REG_A | EMU_REGPART_I;
    buf[li++] = EMUX_TP_IMOV;
    buf[li++] = EMU_REG_B | EMU_REGPART_B;
    buf[li++] = EMU_REG_A | EMU_REGPART_I;
    buf[li++] = EMUX_TP_IPRT;
    buf[li++] = EMU_REG_B | EMU_REGPART_I;

    //WRITE TEST TO MEMORY
    emub_write(board, 0, TEST_MEMSIZE, (void*)buf);
    //RUN TEST
    proc->ip = 0;
    while(proc->ip < li)
	emup_step(proc);
    
    //TEST THE ARITHMETIC INSTRUCTIONS
    printf(">>> you should see the numbers 2, 5, 7, 5, 25, 12, 1.5, 3.5, 5.0, 3.5, 12.25, 8.166667\n");
    uint32_t a = 2;
    uint32_t b = 5;
    li = 0;
    buf[li++] = EMUX_TP_ISET; //set A
    buf[li++] = EMU_REG_A | EMU_REGPART_I;
    buf[li++] = ((char*)&a)[0];
    buf[li++] = ((char*)&a)[1];
    buf[li++] = ((char*)&a)[2];
    buf[li++] = ((char*)&a)[3];
    buf[li++] = EMUX_TP_IPRT; //print A
    buf[li++] = EMU_REG_A | EMU_REGPART_I;
    buf[li++] = EMUX_TP_ISET; //set B
    buf[li++] = EMU_REG_B | EMU_REGPART_I;
    buf[li++] = ((char*)&b)[0];
    buf[li++] = ((char*)&b)[1];
    buf[li++] = ((char*)&b)[2];
    buf[li++] = ((char*)&b)[3];
    buf[li++] = EMUX_TP_IPRT; //print B
    buf[li++] = EMU_REG_B | EMU_REGPART_I;
    buf[li++] = EMUX_TP_IMOV; //move A to C
    buf[li++] = EMU_REG_C | EMU_REGPART_I;
    buf[li++] = EMU_REG_A | EMU_REGPART_I;
    buf[li++] = EMUX_TP_IADD; //add B to C
    buf[li++] = EMU_REG_C | EMU_REGPART_I;
    buf[li++] = EMU_REG_B | EMU_REGPART_I;
    buf[li++] = EMUX_TP_IPRT; //print C
    buf[li++] = EMU_REG_C | EMU_REGPART_I;
    buf[li++] = EMUX_TP_ISUB; //subtract A from C
    buf[li++] = EMU_REG_C | EMU_REGPART_I;
    buf[li++] = EMU_REG_A | EMU_REGPART_I;
    buf[li++] = EMUX_TP_IPRT; //print C
    buf[li++] = EMU_REG_C | EMU_REGPART_I;
    buf[li++] = EMUX_TP_IMUL; //multiply C by B
    buf[li++] = EMU_REG_C | EMU_REGPART_I;
    buf[li++] = EMU_REG_B | EMU_REGPART_I;
    buf[li++] = EMUX_TP_IPRT; //print C
    buf[li++] = EMU_REG_C | EMU_REGPART_I;
    buf[li++] = EMUX_TP_IDIV; //divide C by A
    buf[li++] = EMU_REG_C | EMU_REGPART_I;
    buf[li++] = EMU_REG_A | EMU_REGPART_I;
    buf[li++] = EMUX_TP_IPRT; //print C
    buf[li++] = EMU_REG_C | EMU_REGPART_I;
   
    //DO THE FLOAT TEST
    float fa = 1.5f;
    float fb = 3.5f;
    buf[li++] = EMUX_TP_ISET; //set A
    buf[li++] = EMU_REG_A | EMU_REGPART_F;
    buf[li++] = ((char*)&fa)[0];
    buf[li++] = ((char*)&fa)[1];
    buf[li++] = ((char*)&fa)[2];
    buf[li++] = ((char*)&fa)[3];
    buf[li++] = EMUX_TP_IPRT; //print A
    buf[li++] = EMU_REG_A | EMU_REGPART_F;
    buf[li++] = EMUX_TP_ISET; //set B
    buf[li++] = EMU_REG_B | EMU_REGPART_F;
    buf[li++] = ((char*)&fb)[0];
    buf[li++] = ((char*)&fb)[1];
    buf[li++] = ((char*)&fb)[2];
    buf[li++] = ((char*)&fb)[3];
    buf[li++] = EMUX_TP_IPRT; //print B
    buf[li++] = EMU_REG_B | EMU_REGPART_F;
    buf[li++] = EMUX_TP_IMOV; //move A to C
    buf[li++] = EMU_REG_C | EMU_REGPART_F;
    buf[li++] = EMU_REG_A | EMU_REGPART_F;
    buf[li++] = EMUX_TP_IADD; //add B to C
    buf[li++] = EMU_REG_C | EMU_REGPART_F;
    buf[li++] = EMU_REG_B | EMU_REGPART_F;
    buf[li++] = EMUX_TP_IPRT; //print C
    buf[li++] = EMU_REG_C | EMU_REGPART_F;
    buf[li++] = EMUX_TP_ISUB; //subtract A from C
    buf[li++] = EMU_REG_C | EMU_REGPART_F;
    buf[li++] = EMU_REG_A | EMU_REGPART_F;
    buf[li++] = EMUX_TP_IPRT; //print C
    buf[li++] = EMU_REG_C | EMU_REGPART_F;
    buf[li++] = EMUX_TP_IMUL; //multiply C by B
    buf[li++] = EMU_REG_C | EMU_REGPART_F;
    buf[li++] = EMU_REG_B | EMU_REGPART_F;
    buf[li++] = EMUX_TP_IPRT; //print C
    buf[li++] = EMU_REG_C | EMU_REGPART_F;
    buf[li++] = EMUX_TP_IDIV; //divide C by A
    buf[li++] = EMU_REG_C | EMU_REGPART_F;
    buf[li++] = EMU_REG_A | EMU_REGPART_F;
    buf[li++] = EMUX_TP_IPRT; //print C
    buf[li++] = EMU_REG_C | EMU_REGPART_F;
    
    //WRITE TEST TO MEMORY
    emub_write(board, 0, TEST_MEMSIZE, (void*)buf);
    //RUN TEST
    proc->ip = 0;
    while(proc->ip < li)
	emup_step(proc);
    
    emub_free(board);
    exit(EXIT_SUCCESS);
}
