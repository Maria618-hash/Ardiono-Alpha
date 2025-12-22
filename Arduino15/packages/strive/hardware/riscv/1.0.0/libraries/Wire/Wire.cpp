/*
  TwoWire.cpp - TWI/I2C library for Wiring & Arduino
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
*/

#include <string.h> // for memcpy
// #include "HardwareSerial.h"
#include "Wire.h"

uint8_t TwoWire::rxBuffer[BUFFER_LENGTH];
uint8_t TwoWire::rxBufferIndex = 0;
uint8_t TwoWire::rxBufferLength = 0;
// uint8_t TwoWire::txAddress = 0;
uint8_t TwoWire::txBuffer[BUFFER_LENGTH + 1];
uint8_t TwoWire::txBufferIndex = 0;
uint8_t TwoWire::txBufferLength = 0;
uint8_t TwoWire::transmitting = 0;
void (*TwoWire::user_onRequest)(void) = NULL;
void (*TwoWire::user_onReceive)(int) = NULL;

TwoWire::TwoWire(uintptr_t baseAddr)
  : _baseAddr(baseAddr)
{
}

void TwoWire::begin(void)
{
  setClock(20000);

  // Reset Command Regsiter
  I2C_CR_REG_BASE(_baseAddr) = 0;

  // Enable core
  bitSet(I2C_CTR_REG_BASE(_baseAddr), I2C_CTR_EN);
}

void TwoWire::setClock(uint32_t frequency)
{
  // Calculate the prescaler divisor value
  uint32_t prescalerDivisor = I2C_PRESCALE_DIVIDOR(frequency);

  // Extract low and high bytes from the prescaler divisor
  uint8_t lowByte = prescalerDivisor & 0xFF;
  uint8_t highByte = (prescalerDivisor >> 8) & 0xFF;

  // Write the values to the I2C_PRERlo_REG and I2C_PRERhi_REG registers
  I2C_PRERlo_REG_BASE(_baseAddr) = lowByte;
  I2C_PRERhi_REG_BASE(_baseAddr) = highByte;
}

void TwoWire::begin(uint8_t address)
{
  begin();
}

void TwoWire::beginTransmission(uint8_t address)
{
  // txBuffer[0] = (address << 1);
  I2C_TXR_REG_BASE(_baseAddr) = address << 1;

  // UnSet first bit to send Write command
  bitClear(I2C_TXR_REG_BASE(_baseAddr), I2C_TXR_WR);

  I2C_CR_REG_BASE(_baseAddr) = 0x0;

  // Set Start Bit
  bitSet(I2C_CR_REG_BASE(_baseAddr), I2C_CR_WR);

  // Set Start Bit
  bitSet(I2C_CR_REG_BASE(_baseAddr), I2C_CR_STA);

  transferInProgress();

  transmitting = 1;
  txBufferLength = 1;
}

size_t TwoWire::write(uint8_t data)
{
  txBuffer[0] = data;

  // Copy Data to Transmit Register
  I2C_TXR_REG_BASE(_baseAddr) = txBuffer[0];

  I2C_CR_REG_BASE(_baseAddr) = 0x10;

  transferInProgress();

  return 1;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
  if (quantity == 0)
  {
    return 0; // Nothing to write
  }

  // Ensure buffer has enough space for the data
  if (quantity > BUFFER_LENGTH)
  {
    quantity = BUFFER_LENGTH; // Limit to buffer size
  }

  // Copy data to transmit buffer
  for (size_t i = 0; i < quantity; i++)
  {
    txBuffer[i] = data[i];
  }

  // Write data to I2C transmit register
  for (size_t i = 0; i < quantity; i++)
  {
    write(txBuffer[i]);
  }

  return quantity;
}

void TwoWire::flush(void)
{
}

uint8_t TwoWire::endTransmission(uint8_t sendStop)
{
  I2C_CR_REG_BASE(_baseAddr) = 0x0;

  // Set Stop Bit
  bitSet(I2C_CR_REG_BASE(_baseAddr), I2C_CR_STO);

  // Set Stop Bit
  bitSet(I2C_CR_REG_BASE(_baseAddr), I2C_CR_WR);

  transferInProgress();
  return 1;
}

void TwoWire::transferInProgress()
{
  while (bitRead(I2C_SR_REG_BASE(_baseAddr), I2C_SR_TIP) == 0)
    ;
  while (bitRead(I2C_SR_REG_BASE(_baseAddr), I2C_SR_TIP) == 1)
    ;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t length, uint8_t sendStop)
{
  // Address Set
  I2C_TXR_REG_BASE(_baseAddr) = address << 1;

  // Set first bit to send Read command
  bitSet(I2C_TXR_REG_BASE(_baseAddr), I2C_TXR_WR);

  // I2C_TXR_REG = 0x91;
  I2C_CR_REG_BASE(_baseAddr) = 0x00;

  // Set Write Bit
  bitSet(I2C_CR_REG_BASE(_baseAddr), I2C_CR_WR);

  // Set Start Bit
  bitSet(I2C_CR_REG_BASE(_baseAddr), I2C_CR_STA);

  transferInProgress();
  rxBufferIndex = 0;
  while (rxBufferIndex < length)
  {
    // Reset Command Reg
    I2C_CR_REG_BASE(_baseAddr) = 0x0;

    // Set Read from Slave Bit
    bitSet(I2C_CR_REG_BASE(_baseAddr), I2C_CR_RD);

    transferInProgress();
    rxBuffer[rxBufferIndex++] = I2C_RXR_REG_BASE(_baseAddr);
  }

  I2C_CR_REG_BASE(_baseAddr) = 0x68;
  transferInProgress();

  return rxBufferIndex;
}

int TwoWire::available(void)
{
  return rxBufferIndex;
}

int TwoWire::read(void)
{
  if (rxBufferIndex > 0)
  {
    int val = rxBuffer[0]; // Read the first element in the buffer
    // Shift the buffer elements to the left
    for (int i = 1; i < rxBufferIndex; i++)
    {
      rxBuffer[i - 1] = rxBuffer[i];
    }
    rxBufferIndex--; // Decrement the buffer index
    return val;
  }
  else
  {
    return 0; // Return an error value if the buffer is empty
  }
}

int TwoWire::peek(void)
{
  if (rxBufferIndex > 0)
  {
    return rxBuffer[0]; // Return the first element in the buffer without removing it
  }
  else
  {
    return -1; // Return an error value if the buffer is empty
  }
}


// alternate function prototypes

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t) true);
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t) true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
}

void TwoWire::beginTransmission(int address)
{
  beginTransmission((uint8_t)address);
}

uint8_t TwoWire::endTransmission(void)
{
  return endTransmission(true);
}

void TwoWire::begin(int address)
{
  begin((uint8_t)address);
}

void TwoWire::onReceive(void (*function)(int))
{
  user_onReceive = function;
}

void TwoWire::onRequest(void (*function)(void))
{
  user_onRequest = function;
}

TwoWire Wire((uintptr_t)I2C_BASE_ADDR);
#if defined(I2C2_BASE_ADDR)
TwoWire Wire1((uintptr_t)I2C2_BASE_ADDR);
#endif
#if defined(I2C3_BASE_ADDR)
TwoWire Wire2((uintptr_t)I2C3_BASE_ADDR);
#endif
