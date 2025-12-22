#include "CAN.h"

// ---------------- Constructor ----------------
CANClass::CANClass(uint32_t base_address)
{
  CAN_CONTROL        = (uint32_t *)(base_address + (0  * 0x04));
  CAN_COMMAND        = (uint32_t *)(base_address + (1  * 0x04));
  CAN_STATUS         = (uint32_t *)(base_address + (2  * 0x04));
  CAN_INTERRUPT      = (uint32_t *)(base_address + (3  * 0x04));
  CAN_ACC_CODE       = (uint32_t *)(base_address + (4  * 0x04));
  CAN_ACC_MASK       = (uint32_t *)(base_address + (5  * 0x04));
  CAN_BUS_TIMING     = (uint32_t *)(base_address + (6  * 0x04));
  CAN_BUS_TIMING2    = (uint32_t *)(base_address + (7  * 0x04));
  CAN_OCR            = (uint32_t *)(base_address + (8  * 0x04));
  CAN_TEST           = (uint32_t *)(base_address + (9  * 0x04));

  CAN_TRANSMIT_ID    = (uint32_t *)(base_address + (10 * 0x04));
  CAN_TRANSMIT_ID2   = (uint32_t *)(base_address + (11 * 0x04));
  CAN_TRANSMIT_1     = (uint32_t *)(base_address + (12 * 0x04));
  CAN_TRANSMIT_2     = (uint32_t *)(base_address + (13 * 0x04));
  CAN_TRANSMIT_3     = (uint32_t *)(base_address + (14 * 0x04));
  CAN_TRANSMIT_4     = (uint32_t *)(base_address + (15 * 0x04));
  CAN_TRANSMIT_5     = (uint32_t *)(base_address + (16 * 0x04));
  CAN_TRANSMIT_6     = (uint32_t *)(base_address + (17 * 0x04));
  CAN_TRANSMIT_7     = (uint32_t *)(base_address + (18 * 0x04));
  CAN_TRANSMIT_8     = (uint32_t *)(base_address + (19 * 0x04));

  CAN_RECEIVE_ID     = (uint32_t *)(base_address + (20 * 0x04));
  CAN_RECEIVE_ID2    = (uint32_t *)(base_address + (21 * 0x04));
  CAN_RECEIVE_1      = (uint32_t *)(base_address + (22 * 0x04));
  CAN_RECEIVE_2      = (uint32_t *)(base_address + (23 * 0x04));
  CAN_RECEIVE_3      = (uint32_t *)(base_address + (24 * 0x04));
  CAN_RECEIVE_4      = (uint32_t *)(base_address + (25 * 0x04));
  CAN_RECEIVE_5      = (uint32_t *)(base_address + (26 * 0x04));
  CAN_RECEIVE_6      = (uint32_t *)(base_address + (27 * 0x04));
  CAN_RECEIVE_7      = (uint32_t *)(base_address + (28 * 0x04));
  CAN_RECEIVE_8      = (uint32_t *)(base_address + (29 * 0x04));

  CAN_CLK_DIV        = (uint32_t *)(base_address + (31 * 0x04));

  // Arduino-style state variables
  _packetBegun = 0;
  _txId        = 0;
  _txExtended  = 0;
  _txRtr       = 0;
  _txDlc       = 0;
  _txLength    = 0;
  _txData      = 0;
}

// ---------------- Internal helper ----------------
char CANClass::modifyRegister(volatile uint32_t *reg, char reset_bits, char mask)
{
  char val = (char)(*reg);
  val &= reset_bits;
  val |= mask;
  return val;
}

void CANClass::reset() {
    // if (sel == 1) {
    //     *CAN_CONTROL = 0x00;  // CAN set
    // } else {
        *CAN_CONTROL = 0x01;  // CAN reset
   // }
}


// ---------------- MCP2515-style API ----------------

uint8_t CANClass::begin(uint8_t speed)
{
  // Reset controller
 // *CAN_COMMAND = 0x01; // reset

  // Configure baud rate (example mapping)
  switch (speed)
  {
    case 1:   // 500 kbps
      *CAN_BUS_TIMING  = 0x04;
      *CAN_BUS_TIMING2 = 0x1c;
      break;

    case 2:   // 250 kbps
      *CAN_BUS_TIMING  = 0x03;
      *CAN_BUS_TIMING2 = 0x07;
      break;

    case 3:   // 125 kbps
      *CAN_BUS_TIMING  = 0x01;
      *CAN_BUS_TIMING2 = 0x1C;
      break;

    default:
      return 0; // unsupported speed
  }

  // Enable CAN controller
  //*CAN_CONTROL = 0x00;
  return 1;
}


void CANClass::filter(uint32_t id, uint32_t mask) {
    *CAN_ACC_CODE = id;
    *CAN_ACC_MASK = mask;
}

void CANClass::command(uint8_t cmd) {
    *CAN_COMMAND = cmd;
}

void CANClass::setTransmitId(uint32_t id1, uint32_t id2) {
    *CAN_TRANSMIT_ID  = id1;
    *CAN_TRANSMIT_ID2 = id2;
}


int CANClass::beginPacket(int id, int dlc, int rtr) {
    if (id < 0 || id > 0x7FF) {
        return 0;  // invalid ID
    }
    if (dlc > 8) {
        return 0;  // invalid DLC
    }

    _packetBegun = true;
    _txId = id;
    _txExtended = false;
    _txRtr = rtr;
    _txDlc = dlc;
    _txLength = 0;

    return 1; // success
}

void CANClass::write(uint8_t byte) {
    writeBuff(&byte, 1);
}

int CANClass::writeBuff(const uint8_t* buffer, int size) {
    // Write the transmit ID
    *CAN_TRANSMIT_ID = _txId;

    // Modify DLC bits in CAN_TRANSMIT_ID2 register (mask with 0xF0, set _txDlc)
    uint8_t dlc = modifyRegister(CAN_TRANSMIT_ID2, 0xF0, _txDlc);
    *CAN_TRANSMIT_ID2 = dlc;

    if (size > 8) {
        size = 8;  // Max 8 bytes per CAN frame
    }

    uint32_t addr = (uint32_t)CAN_TRANSMIT_1;
    for (int i = 0; i < size; i++) {
        // Write each byte into consecutive transmit data registers
        *((volatile uint8_t*)addr) = buffer[i];
        addr += 4;  // Assuming registers are spaced by 4 bytes
    }
    return 1; // Success
}




uint8_t CANClass::mcp2515_check_free_buffer()
{
  return ((*CAN_STATUS & 0x04) == 0); // TX buffer free
}

uint8_t CANClass::mcp2515_send_message(tCAN *message)
{
  if (!mcp2515_check_free_buffer()) return 0;

  _txId  = message->id;
  _txDlc = message->header.length & 0x0F;

  *CAN_TRANSMIT_ID  = _txId;
  *CAN_TRANSMIT_ID2 = modifyRegister(CAN_TRANSMIT_ID2, 0xF0, _txDlc);

  volatile uint32_t *addr = CAN_TRANSMIT_1;
  for (int i = 0; i < _txDlc; i++)
  {
    *addr++ = message->data[i];
  }

  *CAN_COMMAND = 0x01; // transmit request
  return 1;
}

uint8_t CANClass::mcp2515_check_message()
{
  return (*CAN_STATUS & 0x01); // RX available
}

uint8_t CANClass::mcp2515_get_message(tCAN *message)
{
  if (!mcp2515_check_message()) return 0;

  message->id = *CAN_RECEIVE_ID;
  message->header.length = (*CAN_RECEIVE_ID2) & 0x0F;

  volatile uint32_t *addr = CAN_RECEIVE_1;
  for (int i = 0; i < message->header.length; i++)
  {
    message->data[i] = *addr++;
  }

  return 1;
}

void CANClass::mcp2515_bit_modify(uint8_t reg, uint8_t mask, uint8_t data)
{
  volatile uint32_t *r = (volatile uint32_t *)((uint32_t)CAN_CONTROL + reg);
  char val = *r;
  val &= ~mask;
  val |= (data & mask);
  *r = val;
}
