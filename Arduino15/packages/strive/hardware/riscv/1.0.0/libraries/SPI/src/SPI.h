/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@arduino.cc>
 * Copyright (c) 2014 by Paul Stoffregen <paul@pjrc.com> (Transaction API)
 * Copyright (c) 2014 by Matthijs Kooijman <matthijs@stdin.nl> (SPISettings AVR)
 * Copyright (c) 2014 by Andrew J. Kroll <xxxajk@gmail.com> (atomicity fixes)
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <Arduino.h>

#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif

#define SPI_REG_SPPR 0x00
#define SPI_REG_SPSR 0x08
#define SPI_REG_SPDR 0x10
#define SPI_REG_SPER 0x18
#define SPI_REG_SPCS 0x20

#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06

#define SPI_CLOCK_DIV_4 0x00
#define SPI_CLOCK_DIV_16 0x01
#define SPI_CLOCK_DIV_64 0x02
#define SPI_CLOCK_DIV_128 0x03
#define SPI_CLOCK_DIV_2 0x04
#define SPI_CLOCK_DIV_8 0x05
#define SPI_CLOCK_DIV_32 0x06

#define SPI_MODE0 0x00
#define SPI_MODE1 0x01
#define SPI_MODE2 0x02
#define SPI_MODE3 0x03

#define SPI_MODE_MASK 0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
#define SPI_CLOCK_MASK 0x03  // SPR1 = bit 1, SPR0 = bit 0 on SPCR
#define SPI_ER_MASK 0x03

/* ----- Bits definition                                                                                                                        */                                       

/* ----- Control register                                                                                                                       */
	
#define SPI_SPR  0      /* SPI clock Rate                                                                                               */                                                                                             
#define SPI_CPHA 2      /* Clock Phase: Determines the phase of sampling and sending data.                                              */
#define SPI_CPOL 3      /* Clock Polarity: Determines idle state of SPI clock (SCK)                                                     */
#define SPI_MSTR 4      /* When MSTR = 1, the SPI core is a controller device                                                           */
#define SPI_SPE  6      /* When SPE = 1, the SPI core is enabled.                                                                       */
#define SPIE 7      /* When SPIE = 1, when the SPI Interrupt Flag in the status register is set, the host is interrupted            */


/* ----- Status register bits                                                                                                                   */
 
#define RFEMPTY  0      /* Read FIFO Empty:         If RFEMPTY = 1, the read FIFO is empty.                                         */
#define SPI_RFFULL   1     /* Read FIFO Full:          If RFFULL = 1, the read FIFO is full.                                           */
#define SPI_WFEMPTY  2     /* Write FIFO Empty:        IF WFEMPTY = 1, the write FIFO is empty                                         */
#define SPI_WFFULL   3      /* Write FIFO Full:         IF WFFULL = 1, the write FIFO is full.                                          */
#define SPI_WCOL     6      /* Write Collision flag:    When WCOL = 1, the SPDATA register was written to while the Write FIFO was full */
#define SPIF     7      /* SPI Interrupt Flag:      SPIF = 1 upon completion of a transfer block                                    */


/* ----- SPI Extended Register                                        */

#define SPI_ESPR     (3<<0)      /* Extended SPI Clock Rate Select: Add two bits to the SPR (SPI Clock Rate Select).                         */
#define SPI_ICNT     (3<<6)      /* Interrupt Count: Determine the transfer block size. The SPIF bit is set after ICNT transfers             */

class SPISettings {
public:
  SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
      init_AlwaysInline(clock, bitOrder, dataMode);
  }
  SPISettings() {
    init_AlwaysInline(200000, MSBFIRST, SPI_MODE0);
  }

private:
  void init_AlwaysInline(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
 {
    // Clock settings are defined as follows. 
    
    // ESPR   SPR   Divide WISHBONE clock by 
    //  00    00      2
    //  00    01      4
    //  00    10     16
    //  00    11     32
    //  01    00      8
    //  01    01     64
    //  01    10    128
    //  01    11    256
    //  10    00    512
    //  10    01   1024
    //  10    10   2048
    //  10    11   4096
    //  11    xx  Reserved

     uint8_t clockDiv;


      if (clock >= F_CPU / 2) {
        clockDiv = 0;
      } else if (clock >= F_CPU / 4) {
        clockDiv = 1;
      } else if (clock >= F_CPU / 8) {
        clockDiv = 4;
      } else if (clock >= F_CPU / 16) {
        clockDiv = 2;
      } else if (clock >= F_CPU / 32) {
        clockDiv = 3;
      } else if (clock >= F_CPU / 64) {
        clockDiv = 5;
      } 
        else if (clock >= F_CPU / 128) {
        clockDiv = 6;
      } else if (clock >= F_CPU / 256) {
        clockDiv = 7;
      } else if (clock >= F_CPU / 512) {
        clockDiv = 8;
      } else if (clock >= F_CPU / 1024) {
        clockDiv = 9;
      } else if (clock >= F_CPU / 2048) {
        clockDiv = 10;
      } else if (clock >= F_CPU / 4096) {
        clockDiv = 11;
      } else {

        clockDiv = 11; 
      }

    // Pack into the SPISettings class
    spcr = _BV(SPI_SPE) | _BV(SPI_MSTR) | ((dataMode << 2) & SPI_MODE_MASK) | (clockDiv & SPI_CLOCK_MASK);
    spsr = _BV(SPIF) | _BV(SPI_WCOL);
    sper |= (clockDiv >> 2) & SPI_ER_MASK;
  }
  
  uint32_t spsr;
  uint32_t spcr;
  uint32_t sper;
  friend class SPIClass;
};


class SPIClass {


public:
  SPIClass(uint32_t baseAddress){
	SPCR	= (uint32_t *)(baseAddress + SPI_REG_SPPR);
	SPSR	= (uint32_t *)(baseAddress + SPI_REG_SPSR);
	SPDR	= (uint32_t *)(baseAddress + SPI_REG_SPDR);
	SPER	= (uint32_t *)(baseAddress + SPI_REG_SPER);
	SPCS	= (uint32_t *)(baseAddress + SPI_REG_SPCS);
  }

  // Initialize the SPI library
  void begin();

  static void usingInterrupt(uint8_t interruptNumber);
  // And this does the opposite.
  static void notUsingInterrupt(uint8_t interruptNumber);
  inline void beginTransaction(SPISettings settings) {

    *SPCR = settings.spcr;
    *SPSR = settings.spsr;
  }

  // Write to the SPI bus (MOSI pin) and also receive (MISO pin)
  uint8_t transfer(uint8_t data) {
    *SPDR = data;
    while ((*SPSR & _BV(RFEMPTY))) ; // wait fo receive fifo to update
    return *SPDR;
  }

  uint16_t transfer16(uint16_t data) {
    union { uint16_t val; struct { uint8_t lsb; uint8_t msb; }; } in, out;
    in.val = data;
      *SPDR = in.msb;
      while ((*SPSR & _BV(RFEMPTY))) ;
      out.msb = *SPDR;
      *SPDR = in.lsb;
      while ((*SPSR & _BV(RFEMPTY))) ;
      out.lsb = *SPDR;
    return out.val;
  }
  void transfer(void *buf, size_t count) {
    if (count == 0) return;
    uint8_t *p = (uint8_t *)buf;
    *SPDR = *p;
    while (--count > 0) {
      uint8_t out = *(p + 1);
      while ((*SPSR & _BV(RFEMPTY))) ;
      uint8_t in = *SPDR;
      *SPDR = out;
      *p++ = in;
    }
  }
  // After performing a group of transfers and releasing the chip select
  // signal, this function allows others to access the SPI bus
  void endTransaction(void) {
   
  }

  // Disable the SPI bus
  void end();

  // This function is deprecated.  New applications should use
  // beginTransaction() to configure SPI settings.
  inline void setBitOrder(uint8_t bitOrder) {
  }
  // This function is deprecated.  New applications should use
  // beginTransaction() to configure SPI settings.
  inline void setDataMode(uint8_t dataMode) {
     *SPCR = (*SPCR & ~SPI_MODE_MASK) | (dataMode << 2);
  }
  // This function is deprecated.  New applications should use
  // beginTransaction() to configure SPI settings.
  inline void setClockDivider(uint8_t clockDiv) {
    *SPCR = (*SPCR & ~SPI_CLOCK_MASK) | (clockDiv & SPI_CLOCK_MASK);
    *SPER = (*SPER & ~SPI_ER_MASK) | ((clockDiv >> 2) & SPI_ER_MASK);
  }
  void attachInterrupt() { 
	*SPCR |= _BV(SPIE); 
	}
  void detachInterrupt() { 
	*SPCR &= ~_BV(SPIE); 
	}

private:

  volatile uint32_t *SPCR;
  volatile uint32_t *SPSR;
  volatile uint32_t *SPDR;
  volatile uint32_t *SPER;
  volatile uint32_t *SPCS;
  static uint8_t initialized;
  static uint8_t interruptMode; // 0=none, 1=mask, 2=global
  static uint8_t interruptMask; // which interrupts to mask
  static uint8_t interruptSave; // temp storage, to restore state
  #ifdef SPI_TRANSACTION_MISMATCH_LED
  static uint8_t inTransactionFlag;
  #endif
};

extern SPIClass SPI;

#endif
