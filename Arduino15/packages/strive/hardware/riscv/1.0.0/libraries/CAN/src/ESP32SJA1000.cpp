#include "ESP32SJA1000.h"

/* ===== BASIC CAN REGISTER OFFSETS ===== */
#define REG_MOD     0x00
#define REG_CMR     0x01
#define REG_SR      0x02
#define REG_IR      0x03
#define REG_ACR     0x04
#define REG_AMR     0x05
#define REG_BTR0    0x06
#define REG_BTR1    0x07

#define REG_TX_ID   0x0A
#define REG_TX_ID2  0x0B
#define REG_TX_DATA 0x0C

#define REG_RX_ID   0x14
#define REG_RX_ID2  0x15
#define REG_RX_DATA 0x16

ESP32SJA1000Class::ESP32SJA1000Class(uint32_t base)
: CANControllerClass(), _base(base) {}

/* ===== LOW LEVEL IO ===== */

uint8_t ESP32SJA1000Class::readRegister(uint8_t reg) {
  return *(volatile uint32_t*)(_base + reg * 4);
}

void ESP32SJA1000Class::writeRegister(uint8_t reg, uint8_t val) {
  *(volatile uint32_t*)(_base + reg * 4) = val;
}

/* ===== INIT ===== */

int ESP32SJA1000Class::begin(long baudrate) {
  // Reset mode
  writeRegister(REG_MOD, 0x01);

  if (baudrate == 250E3) {
    writeRegister(REG_BTR0, 0x04);
    writeRegister(REG_BTR1, 0x1C);
  } else if (baudrate == 500E3) {
    writeRegister(REG_BTR0, 0x04);
    writeRegister(REG_BTR1, 0x16);
  } else {
    return 0;
  }

  // Normal mode
  writeRegister(REG_MOD, 0x00);
  return 1;
}

/* ===== TRANSMIT ===== */

int ESP32SJA1000Class::endPacket() {
  // ID
  // writeRegister(REG_TX_ID, _txId);

  // // DLC + RTR
  // uint8_t dlc = (_txRtr ? 0x40 : 0x00) | (_txLength & 0x0F);
  // writeRegister(REG_TX_ID2, dlc);

  // // DATA
  // for (int i = 0; i < _txLength; i++) {
  //   writeRegister(REG_TX_DATA + i, _txData[i]);
  // }

  // // TRANSMIT COMMAND
  // writeRegister(REG_CMR, 0x01);
  //  return 1;
    writeRegister(REG_TX_ID, _txId);
    char dlc; int size;
    dlc = modifyRegister(REG_TX_ID2,0xF0,_txDlc);
    writeRegister(REG_TX_ID2, dlc); // write byte to dlc bits

  for (int i = 0; i < _txLength; i++) {
    writeRegister(REG_TX_DATA + i, _txData[i]);
  }

  return 1;
}

/* ===== RECEIVE (OVERRIDES CANControllerClass) ===== */

int ESP32SJA1000Class::parsePacket() {
  // RX buffer status
  if ((readRegister(REG_SR) & 0x01) == 0) {
    return 0;
  }

  _rxId     = readRegister(REG_RX_ID);
  _rxLength = readRegister(REG_RX_ID2) & 0x0F;
  _rxIndex  = 0;

  for (int i = 0; i < _rxLength; i++) {
    _rxData[i] = readRegister(REG_RX_DATA + i);
  }

  // Release RX buffer
  writeRegister(REG_CMR, 0x04);

  return _rxLength;
}
char modifyRegister(unsigned int address, char reset_bits, char mask)
{
    char byte = readRegister(address);
    byte = byte & reset_bits; 
    byte = byte | mask; 
    return byte;

}

/* ===== FILTER ===== */

int ESP32SJA1000Class::filter(int id, int mask) {
  writeRegister(REG_ACR, id);
  writeRegister(REG_AMR, mask);
  return 1;
}
