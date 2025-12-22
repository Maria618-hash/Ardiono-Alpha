/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef HardwareSerial_h
#define HardwareSerial_h

#include <inttypes.h>

#include "Stream.h"
//#include "variant.h"
#include "strive/devices/uart.h"

class HardwareSerial : public Stream
{
  public:
   inline HardwareSerial(uint32_t base)
    {
        UBRD = (uint32_t *)(base + UART_REG_BRDL);
        UIER = (uint32_t *)(base + UART_REG_IER);
        UIIR = (uint32_t *)(base + UART_REG_IIR);
        UFCR = (uint32_t *)(base + UART_REG_FCR);
        ULCR = (uint32_t *)(base + UART_REG_LCR);
        ULSR = (uint32_t *)(base + UART_REG_LSR);
        UWRC = (uint32_t *)(base + UART_WR_CH);
    }
    
    void begin(unsigned long dwBaudRate);
    void end();
    virtual int available(void);
    virtual int peek(void);
    virtual int read(void);
    virtual int availableForWrite(void);
    virtual void flush(void);
    virtual size_t write(uint8_t);
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write; // pull in write(str) and write(buf, size) from Print
    void sio_receive(char c);
    operator bool() { return true; }

    private:
    static const int RX_BUF_SIZE = 8; // Size of the receive buffer
    volatile uint32_t *UBRD;
    volatile uint32_t *UIER;
    volatile uint32_t *UIIR;
    volatile uint32_t *UFCR;
    volatile uint32_t *ULCR;
    volatile uint32_t *ULSR;
    volatile uint32_t *UWRC;
    int write_error;
    size_t printNumber(unsigned long, uint8_t);
    size_t printFloat(double, uint8_t);

  protected:
    volatile uint8_t *serbase;  // base address of SIO register for port
    int sio_probe_rx();
    int sio_getchar(int blocking);
    int sio_putchar(char c, int blocking);
    void sio_setbaud(int bauds);
    
    enum {
      SIO_RXBUFSIZE = (1 << 3),
      SIO_RXBUFMASK = (SIO_RXBUFSIZE - 1)
    };


//    volatile uint8_t  tx_xoff;  // bit 7 set = disable Xoff/Xon flow control
    volatile uint8_t  sio_rxbuf_head;
    volatile uint8_t  sio_rxbuf_tail;
    char              sio_rxbuf[SIO_RXBUFSIZE];
};

extern void serialEventRun(void) __attribute__((weak));

#endif