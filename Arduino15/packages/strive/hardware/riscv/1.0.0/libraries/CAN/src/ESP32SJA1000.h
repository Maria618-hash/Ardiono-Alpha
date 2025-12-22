#pragma once
#include <Arduino.h>
#include "CANController.h"

class ESP32SJA1000Class : public CANControllerClass {
public:
  ESP32SJA1000Class(uint32_t base);

  int begin(long baudrate) override;
  int endPacket() override;
  int parsePacket() override;
  int filter(int id, int mask) override;

protected:
  uint8_t readRegister(uint8_t reg);
  void writeRegister(uint8_t reg, uint8_t val);

private:
  uint32_t _base;
};
