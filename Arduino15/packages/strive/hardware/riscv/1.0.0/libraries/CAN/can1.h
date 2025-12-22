#ifndef _CAN_H_
#define _CAN_H_

#include <Arduino.h>

typedef struct {
  uint32_t id;
  struct {
    uint8_t rtr : 1;
    uint8_t extended : 1;
    uint8_t length : 4;
  } header;
  uint8_t data[8];
} tCAN;

class CANClass {
public:
  CANClass(uint32_t baseAddress);

  // MCP2515-compatible API
  uint8_t begin(uint8_t speed);
  uint8_t mcp2515_send_message(tCAN *message);
  uint8_t mcp2515_check_message();
  uint8_t mcp2515_get_message(tCAN *message);
  uint8_t mcp2515_check_free_buffer();
  void    mcp2515_bit_modify(uint8_t reg, uint8_t mask, uint8_t data);

private:
  char modifyRegister(volatile uint32_t *reg, char reset_bits, char mask);
  void begin(int sel);
  void reset();
  void filter(uint32_t id, uint32_t mask);
  void command(uint8_t cmd);
  void setTransmitId(uint32_t id1, uint32_t id2);
  int beginPacket(int id, int dlc, int rtr);
  void write(uint8_t byte);
  int writeBuff(const uint8_t* buffer, int size) ;
int writeBuffChar(const char* buffer, int size);
void can_endPacket( can_registers* device);

receiveId(int sel)
// ===== Full register map (NO omissions, NO address changes) =====
volatile uint32_t *CAN_CONTROL; // +0x00
volatile uint32_t *CAN_COMMAND; // +0x04
volatile uint32_t *CAN_STATUS; // +0x08
volatile uint32_t *CAN_INTERRUPT; // +0x0C
volatile uint32_t *CAN_ACC_CODE; // +0x10
volatile uint32_t *CAN_ACC_MASK; // +0x14
volatile uint32_t *CAN_BUS_TIMING; // +0x18
volatile uint32_t *CAN_BUS_TIMING2; // +0x1C
volatile uint32_t *CAN_OCR; // +0x20
volatile uint32_t *CAN_TEST; // +0x24


volatile uint32_t *CAN_TRANSMIT_ID; // +0x28
volatile uint32_t *CAN_TRANSMIT_ID2; // +0x2C
volatile uint32_t *CAN_TRANSMIT_1; // +0x30
volatile uint32_t *CAN_TRANSMIT_2; // +0x34
volatile uint32_t *CAN_TRANSMIT_3; // +0x38
volatile uint32_t *CAN_TRANSMIT_4; // +0x3C
volatile uint32_t *CAN_TRANSMIT_5; // +0x40
volatile uint32_t *CAN_TRANSMIT_6; // +0x44
volatile uint32_t *CAN_TRANSMIT_7; // +0x48
volatile uint32_t *CAN_TRANSMIT_8; // +0x4C


volatile uint32_t *CAN_RECEIVE_ID; // +0x50
volatile uint32_t *CAN_RECEIVE_ID2; // +0x54
volatile uint32_t *CAN_RECEIVE_1; // +0x58
volatile uint32_t *CAN_RECEIVE_2; // +0x5C
volatile uint32_t *CAN_RECEIVE_3; // +0x60
volatile uint32_t *CAN_RECEIVE_4; // +0x64
volatile uint32_t *CAN_RECEIVE_5; // +0x68
volatile uint32_t *CAN_RECEIVE_6; // +0x6C
volatile uint32_t *CAN_RECEIVE_7; // +0x70
volatile uint32_t *CAN_RECEIVE_8; // +0x74


volatile uint32_t *CAN_CLK_DIV; // +0x7C


// ===== Arduino-style TX state =====
int _packetBegun;
int _txId;
int _txExtended;
int _txRtr;
char _txDlc;
int _txLength;
int _txData;
};
#endif
