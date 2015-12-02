#include <stdlib.h>
#include <stdio.h>

#include <emu/board.h>

void pinger_irq_cb(emu_device* pinger, uint32_t code)
{
  printf("PING: slot=%d, msg=%d\n", pinger->id, code);
}

void pinger_cc_cb(emu_device* pinger)
{
  printf("CONNECT: slot=%d\n", pinger->id);
}

void free_pinger(emu_device* pinger)
{
  free(pinger->mem);
  free(pinger);
}

void pinger_dc_cb(emu_device* pinger)
{
  printf("DISCONNECT: slot=%d\n", pinger->id);
  free_pinger(pinger);
}

emu_device* create_pinger()
{
  emu_device* pinger = (emu_device*)malloc(sizeof(emu_device));
  pinger->mem = malloc(128);
  if(!pinger->mem)
  {
    free(pinger);
    return NULL;
  }
  pinger->memsize = 128;
  pinger->irq_cb = pinger_irq_cb;
  pinger->cc_cb = pinger_cc_cb;
  pinger->dc_cb = pinger_dc_cb;
  pinger->data = NULL;
  return pinger;
}

void my_connect(emu_board* board, emu_device* pinger, uint8_t id)
{
  emub_connect(board, pinger, id);
}

void my_disconnect(emu_board* board, uint8_t id)
{
  emub_disconnect(board, id);
}

void my_broadcast(emu_board* board, uint32_t msg)
{
  emub_broadcast(board, msg);
}

void my_send(emu_board* board, uint8_t id, uint32_t msg)
{
  emub_send(board, id, msg);
}

void devicetest()
{
  emu_board* b = emub_create();
  emu_device* d1 = create_pinger();
  emu_device* d2 = create_pinger();
  int i;
  int i1 = 0;
  int i2 = 1;

  printf(">>> we are connecting two pingers, in slots %d and %d\n", i1, i2);
  my_connect(b, d1, i1);
  my_connect(b, d2, i2);

  printf(">>> we will now broadcast the signals 0 through 10\n");
  for(i = 0; i < 100; i += 10) my_broadcast(b, i);
  printf(">>> we will now send (255 - n) to each plug n\n");
  for(i = 0; i < 0x100; i++) my_send(b, i, 0x100 - i);

  printf(">>> we will now free the board\n");
  emub_free(b);
}

void freeram(emu_device* ram)
{
  free(ram->mem);
  free(ram);
}

static void ram_dc_cb(emu_device* ram)
{
  freeram(ram);
}

emu_device* makeram()
{
  emu_device* ram = (emu_device*)malloc(sizeof(emu_device));
  ram->mem = (uint8_t*)malloc(128);
  ram->memsize = 128;
  ram->irq_cb = NULL;
  ram->cc_cb = NULL;
  ram->dc_cb = ram_dc_cb;
  ram->data = NULL;
  return ram;
}

void memorytest()
{
  emu_board* b = emub_create();
  const char* string = "uberblah";
  char* iobuffer = (char*)malloc(128);
  emu_device* ram = makeram();

  emub_connect(b, ram, 0);

  //write some memory
  printf("should be 9: %d\n", emub_write(b, 0x000000, 9, (void*)string));
  printf("should be 9: %d\n", emub_write(b, 0x000008, 9, (void*)string));
  printf("should be 9: %d\n", emub_write(b, 0x000010, 9, (void*)string));
  printf("should be 28: %d\n", emub_read(b, 0x000000, 28, (void*)iobuffer));
  printf("should be 'uberblahuberblahuberblah': %s\n", iobuffer);

  //write some memory at the end of the ram
  printf("should be 4: %d\n", emub_write(b, 124, 9, (void*)string));
  printf("should be 4: %d\n", emub_read(b, 124, 9, (void*)(iobuffer + 4)));
  printf("should be uberuberuberblahuberblah: %s\n", iobuffer);
  
  emub_free(b);
  free(iobuffer);
}

int main(int argc, char** argv)
{
  devicetest();
  memorytest();

  exit(EXIT_SUCCESS);
}

