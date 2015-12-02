#ifndef EMU_BOARD_H
#define EMU_BOARD_H

#include <stdint.h>

//forward declaration for our emu_device struct (see below)
typedef struct emu_device emu_device;
///a board is just an array of 256 identical plugs
typedef emu_device* emu_board[0x100];
///used to implement interrupt responses for devices
typedef void(*emu_irq_cb)(emu_device* dev, uint32_t code);
///used to notify devices about other kinds of events
typedef void(*emu_ev_cb)(emu_device* dev);
///a struct for storing information about a device
struct emu_device
{
  ///the board we're plugged into. set by emub_connect
  emu_board* board;
  ///the size of our shared memory, or 0 if no memory
  uint32_t memsize;
  ///the location of our shared memory
  void* mem;
  ///a callback for interrupts from the board
  emu_irq_cb irq_cb;
  ///a connection callback, called when connecting to board
  ///the board and id fields are set prior to calling this
  emu_ev_cb cc_cb;
  ///a disconnection callback, called before disconnecting
  ///the board and id fields are available when calling this
  ///i recommend clearing the board and id fields in this call
  emu_ev_cb dc_cb;
  ///any internal (non-public) information about the device
  void* data;
  ///the id of the plug on the board, set by emub_connect
  uint8_t id;
};

///create an emu_board with no devices attached
emu_board* emub_create();
///free an emu_board, disconnecting any devices first
void emub_free(emu_board* board);
///connect a device to an emu_board at plug 'id'
void emub_connect(emu_board* board, emu_device* device, uint8_t id);
///disconnect the device on a board at plug 'id'
void emub_disconnect(emu_board* board, uint8_t id);
///send an interrupt through the board to plug 'id'
void emub_send(emu_board* board, uint8_t id, uint32_t code);
///broadcast an interrupt to all devices on the board
void emub_broadcast(emu_board* board, uint32_t code);

///read 'count' bytes from the board's shared memory to 'out'
///return the number of bytes successfully read
uint32_t emub_read(emu_board* board, uint32_t addr, uint32_t count, void* out);
///write 'count' bytes to the board's shared memory from 'src'
///return the number of bytes successfully written
uint32_t emub_write(emu_board* board, uint32_t addr, uint32_t count, void* src);

#endif
