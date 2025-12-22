// /*
//   Copyright (c) 2011 Arduino.  All right reserved.

//   This library is free software; you can redistribute it and/or
//   modify it under the terms of the GNU Lesser General Public
//   License as published by the Free Software Foundation; either
//   version 2.1 of the License, or (at your option) any later version.

//   This library is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//   See the GNU Lesser General Public License for more details.

//   You should have received a copy of the GNU Lesser General Public
//   License along with this library; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
// */

// #ifndef _UART_CLASS_
// #define _UART_CLASS_

// #define DEC 10
// #define HEX 16
// #define OCT 8
// #define BIN 2

// __BEGIN_DECLS
// #include <inttypes.h>
// #include <stdio.h> // for size_t
// __END_DECLS

// #include "WString.h"
// #include "Printable.h"
// #include "platform.h"
// #include "HardwareSerial.h"

// class UARTClass : public HardwareSerial
// {
//   public:
//     UARTClass(uint32_t base = UART0_BASE_ADDR ) : serbase(reinterpret_cast<uint8_t*>(base)) {}
  
//     void begin(unsigned long dwBaudRate);
//     void end(void);
//     int available(void);
//     int availableForWrite(void);
//     int peek(void);
//     int read(void);
//     void flush(void);
//     void sio_receive(char c);
//     void init(uint32_t base);

//     size_t write(uint8_t);

//     // size_t write(const char *str) {
//     //   if (str == NULL) return 0;
//     //   return write((const uint8_t *)str, strlen(str));
//     // }
//     // size_t write(const uint8_t *buffer, size_t size);
//     // size_t write(const char *buffer, size_t size) {
//     //   return write((const uint8_t *)buffer, size);
//     // }
    
//     // size_t print(const __FlashStringHelper *);
//     // size_t print(const String &);
//     // size_t print(const char[]);
//     // size_t print(char);
//     // size_t print(unsigned char, int = DEC);
//     // size_t print(int, int = DEC);
//     // size_t print(unsigned int, int = DEC);
//     // size_t print(long, int = DEC);
//     // size_t print(unsigned long, int = DEC);
//     // size_t print(double, int = 2);
//     // size_t print(const Printable&);

//     // size_t println(const __FlashStringHelper *);
//     // size_t println(const String &s);
//     // size_t println(const char[]);
//     // size_t println(char);
//     // size_t println(unsigned char, int = DEC);
//     // size_t println(int, int = DEC);
//     // size_t println(unsigned int, int = DEC);
//     // size_t println(long, int = DEC);
//     // size_t println(unsigned long, int = DEC);
//     // size_t println(double, int = 2);
//     // size_t println(const Printable&);
//     // size_t println(void);
//     // using Print::write; // pull in write(str) and write(buf, size) from Print
//     // operator bool() {return (true);}; // UART always active
   

//     //using Print::write; // pull in write(str) and write(buf, size) from Print

//     //soperator bool() {return (true);}; // UART always active

//   private:
//     static const int RX_BUF_SIZE = 8; // Size of the receive buffer
//     volatile uint32_t *UBRD;
//     volatile uint32_t *UIER;
//     volatile uint32_t *UIIR;
//     volatile uint32_t *UFCR;
//     volatile uint32_t *ULCR;
//     volatile uint32_t *ULSR;
//     volatile uint32_t *UWRC;
//     int write_error;
//     size_t printNumber(unsigned long, uint8_t);
//     size_t printFloat(double, uint8_t);

//   protected:
//     volatile uint8_t *serbase;  // base address of SIO register for port
//     int sio_probe_rx();
//     int sio_getchar(int blocking);
//     int sio_putchar(char c, int blocking);
//     void sio_setbaud(int bauds);
    
//     enum {
//       SIO_RXBUFSIZE = (1 << 3),
//       SIO_RXBUFMASK = (SIO_RXBUFSIZE - 1)
//     };


// //    volatile uint8_t  tx_xoff;  // bit 7 set = disable Xoff/Xon flow control
//     volatile uint8_t  sio_rxbuf_head;
//     volatile uint8_t  sio_rxbuf_tail;
//     char              sio_rxbuf[SIO_RXBUFSIZE];
// };

// #endif // _UART_CLASS_