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

// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include "UARTClass.h"
// #include "variant.h"


// // UARTClass Serial;
// // UARTClass Serial1;


// void UARTClass::init(uint32_t base)
// {
//   UBRD = (uint32_t *)(base + UART_REG_BRDL);
//   UIER = (uint32_t *)(base + UART_REG_IER);
//   UIIR = (uint32_t *)(base + UART_REG_IIR);
//   UFCR = (uint32_t *)(base + UART_REG_FCR);
//   ULCR = (uint32_t *)(base + UART_REG_LCR);
//   ULSR = (uint32_t *)(base + UART_REG_LSR);
//   UWRC = (uint32_t *)(base + UART_WR_CH);
// }

// int UARTClass::sio_probe_rx()
// {
  
//     /* Check for characters in UART Receive FIFO */
//     if ((UART_LSR_DR & (*ULSR)) == 0)
//     {
//         return (0);
//     }
//     return (1);

// }

// int UARTClass::sio_getchar(int blocking)
// {
//   int c, busy;

//   while (blocking && !sio_probe_rx());
//   c = *UWRC;
//   return c;
// }

// int UARTClass::sio_putchar(char c, int blocking)
// {

//   if (blocking){
//   /* Check for space in UART FIFO */
//     while((*ULSR & UART_LSR_THRE_BIT) == 0);
//   }
//   // write char
//   *UWRC = c;
//   return 0;
// }

// /*
//  * Set RS-232 baudrate.  Works well with FT-232R from 9600 to 1000000 bauds.
//  */
// void UARTClass::sio_setbaud(int bauds)
// {
//   *UBRD = (F_CPU / bauds) / 16;
// }

// // Public Methods //////////////////////////////////////////////////////////////

// void UARTClass::begin(unsigned long bauds)
// {

//   /* SET LSR to be 1's so Whisper will be happy that ch is ready */
//   *ULSR = 0xff;
//   /* Set DLAB bit in LCR */
//   *ULCR |= UART_DLAB_BIT;
//   /* Set divisor regs  devisor = 27: clock_freq/baud_rate*16 -->> clock = 50MHz, baud=115200*/
//   *UBRD = (F_CPU / bauds) / 16;
//   /* 8 data bits, 1 stop bit, no parity, clear DLAB */
//   *ULCR = (UART_LCR_CS8 | UART_LCR_1_STB | UART_LCR_PDIS);
//   *UFCR = (UART_FCR_FIFO_BIT | UART_FCR_MODE0_BIT | UART_FCR_FIFO_8_BIT | UART_FCR_RCVRCLR_BIT | UART_FCR_XMITCLR_BIT);
//   /* disable interrupts  */
//   *UIER = (0x00);

// }

// void UARTClass::end(void)
// {
// }

// // int UARTClass::available(void)
// // {
// //   return sio_probe_rx();
// // }

// int UARTClass::available(void)
// {
//       if (sio_probe_rx())
//     {
//       int c = sio_getchar(1);
//       if (c != -1) {
//           sio_receive(c);
//       }
//     }

//     int availableInBuffer = (sio_rxbuf_head - sio_rxbuf_tail + RX_BUF_SIZE) % RX_BUF_SIZE;

//     // If there are characters in the buffer, return the count
//     if (availableInBuffer > 0) {
//         return availableInBuffer;
//     }
//     else
//     {
//       return 0;
//     }

// }

// int UARTClass::availableForWrite(void)
// {
//   int busy;
//   busy = (!(*ULSR & UART_LSR_THRE_BIT));
//   return (!busy);
// }

// int UARTClass::peek(void)
// {
//   sio_probe_rx();
//   if (sio_rxbuf_tail == sio_rxbuf_head)
//     return (-1);
//   else
//     return (sio_rxbuf[sio_rxbuf_tail]);
// }

// // int UARTClass::read(void)
// // {
// //   return (sio_getchar(1));
// // }

// int UARTClass::read(void)
// {
//     sio_probe_rx();

//     // Check if there's a character in the buffer
//     if (sio_rxbuf_tail != sio_rxbuf_head) {
//         int c = sio_rxbuf[sio_rxbuf_tail];
//         sio_rxbuf_tail = (sio_rxbuf_tail + 1) % RX_BUF_SIZE;
//         return c;
//     }
//     else{
//       return 0;
//     }
// }

// void UARTClass::flush(void)
// {
//   /* Check for space in UART FIFO */
//     while((*ULSR & UART_LSR_THRE_BIT) == 0);
// }

// size_t
// UARTClass::write(const uint8_t uc_data) 
// {

//   sio_putchar(uc_data, 1);
//   return (1);
// }

// // Add received characters to the buffer
// void UARTClass::sio_receive(char c)
// {
//     // Check if the buffer is not full
//     if ((sio_rxbuf_head + 1) % RX_BUF_SIZE != sio_rxbuf_tail) {
//         sio_rxbuf[sio_rxbuf_head] = c;
//         sio_rxbuf_head = (sio_rxbuf_head + 1) % RX_BUF_SIZE;
//     }
// }


// // // Public Methods //////////////////////////////////////////////////////////////

// // /* default implementation: may be overridden */
// // size_t UARTClass::write(const uint8_t *buffer, size_t size)
// // {
// //   size_t n = 0;
// //   while (size--) {
// //     n += write(*buffer++);
// //   }
// //   return n;
// // }


// // size_t UARTClass::print(const __FlashStringHelper *ifsh)
// // {
// //   return print(reinterpret_cast<const char *>(ifsh));
// // }

// // size_t UARTClass::print(const String &s)
// // {
// //   return write(s.c_str(), s.length());
// // }

// // size_t UARTClass::print(const char str[])
// // {
// //   return write(str);
// // }

// // size_t UARTClass::print(char c)
// // {
// //   return UARTClass::write((uint8_t)c);
// // }

// // size_t UARTClass::print(unsigned char b, int base)
// // {
// //   return print((unsigned long) b, base);
// // }

// // size_t UARTClass::print(int n, int base)
// // {
// //   return print((long) n, base);
// // }

// // size_t UARTClass::print(unsigned int n, int base)
// // {
// //   return print((unsigned long) n, base);
// // }

// // size_t UARTClass::print(long n, int base)
// // {
// //   if (base == 0) {
// //     return write((uint8_t)n);
// //   } else if (base == 10) {
// //     if (n < 0) {
// //       int t = print('-');
// //       n = -n;
// //       return printNumber(n, 10) + t;
// //     }
// //     return printNumber(n, 10);
// //   } else {
// //     return printNumber(n, base);
// //   }
// // }

// // size_t UARTClass::print(unsigned long n, int base)
// // {
// //   if (base == 0) return write((uint8_t)n);
// //   else return printNumber(n, base);
// // }

// // size_t UARTClass::print(double n, int digits)
// // {
// //   return printFloat(n, digits);
// // }

// // size_t UARTClass::println(const __FlashStringHelper *ifsh)
// // {
// //   size_t n = print(ifsh);
// //   n += println();
// //   return n;
// // }

// // size_t UARTClass::print(const Printable& x)
// // {
// //   //return x.printTo(*this);
// // }

// // size_t UARTClass::println(void)
// // {
// //   size_t n = print('\r');
// //   n += print('\n');
// //   return n;
// // }

// // size_t UARTClass::println(const String &s)
// // {
// //   size_t n = print(s);
// //   n += println();
// //   return n;
// // }

// // size_t UARTClass::println(const char c[])
// // {
// //   size_t n = print(c);
// //   n += println();
// //   return n;
// // }

// // size_t UARTClass::println(char c)
// // {
// //   size_t n = print(c);
// //   n += println();
// //   return n;
// // }

// // size_t UARTClass::println(unsigned char b, int base)
// // {
// //   size_t n = print(b, base);
// //   n += println();
// //   return n;
// // }

// // size_t UARTClass::println(int num, int base)
// // {
// //   size_t n = print(num, base);
// //   n += println();
// //   return n;
// // }

// // size_t UARTClass::println(unsigned int num, int base)
// // {
// //   size_t n = print(num, base);
// //   n += println();
// //   return n;
// // }

// // size_t UARTClass::println(long num, int base)
// // {
// //   size_t n = print(num, base);
// //   n += println();
// //   return n;
// // }

// // size_t UARTClass::println(unsigned long num, int base)
// // {
// //   size_t n = print(num, base);
// //   n += println();
// //   return n;
// // }

// // size_t UARTClass::println(double num, int digits)
// // {
// //   size_t n = print(num, digits);
// //   n += println();
// //   return n;
// // }

// // size_t UARTClass::println(const Printable& x)
// // {
// //   size_t n = print(x);
// //   n += println();
// //   return n;
// // }

// // // Private Methods /////////////////////////////////////////////////////////////

// // size_t UARTClass::printNumber(unsigned long n, uint8_t base) {
// //   char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
// //   char *str = &buf[sizeof(buf) - 1];

// //   *str = '\0';

// //   // prevent crash if called with base == 1
// //   if (base < 2) base = 10;

// //   do {
// //     unsigned long m = n;
// //     n /= base;
// //     char c = m - base * n;
// //     *--str = c < 10 ? c + '0' : c + 'A' - 10;
// //   } while(n);

// //   return write(str);
// // }

// // size_t UARTClass::printFloat(double number, uint8_t digits) 
// // { 
// //   size_t n = 0;
  
// //   if (isnan(number)) return print("nan");
// //   if (isinf(number)) return print("inf");
// //   if (number > 4294967040.0) return print ("ovf");  // constant determined empirically
// //   if (number <-4294967040.0) return print ("ovf");  // constant determined empirically
  
// //   // Handle negative numbers
// //   if (number < 0.0)
// //   {
// //      n += print('-');
// //      number = -number;
// //   }

// //   // Round correctly so that print(1.999, 2) prints as "2.00"
// //   double rounding = 0.5;
// //   for (uint8_t i=0; i<digits; ++i)
// //     rounding /= 10.0;
  
// //   number += rounding;

// //   // Extract the integer part of the number and print it
// //   unsigned long int_part = (unsigned long)number;
// //   double remainder = number - (double)int_part;
// //   n += print(int_part);

// //   // Print the decimal point, but only if there are digits beyond
// //   if (digits > 0) {
// //     n += print("."); 
// //   }

// //   // Extract digits from the remainder one at a time
// //   while (digits-- > 0)
// //   {
// //     remainder *= 10.0;
// //     int toPrint = int(remainder);
// //     n += print(toPrint);
// //     remainder -= toPrint; 
// //   } 
  
// //   return n;
// // }