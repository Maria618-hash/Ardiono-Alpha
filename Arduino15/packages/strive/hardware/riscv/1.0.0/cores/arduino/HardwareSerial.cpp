#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HardwareSerial.h"
#include "variant.h"
#define F_CPU 50000000

#if defined(STRIVE_1)
HardwareSerial Serial(UART0_BASE_ADDR);
HardwareSerial Serial1(UART1_BASE_ADDR);
//HardwareSerial Serial2(UART2_BASE_ADDR);
//HardwareSerial Serial3(UART3_BASE_ADDR);
//HardwareSerial Serial4(UART4_BASE_ADDR);
#endif
#if defined(STRIVE_1alpha)
HardwareSerial Serial(UART0_BASE_ADDR);
HardwareSerial Serial1(UART1_BASE_ADDR);
HardwareSerial Serial2(UART2_BASE_ADDR);
HardwareSerial Serial3(UART3_BASE_ADDR);
HardwareSerial Serial4(UART4_BASE_ADDR);
HardwareSerial Serial5(UART5_BASE_ADDR);
HardwareSerial Serial6(UART6_BASE_ADDR);
HardwareSerial Serial7(UART7_BASE_ADDR);

#endif
int HardwareSerial::sio_probe_rx()
{
  
    /* Check for characters in UART Receive FIFO */
    if ((UART_LSR_DR & (*ULSR)) == 0)
    {
        return (0);
    }
    return (1);

}

int HardwareSerial::sio_getchar(int blocking)
{
  int c;

  while (blocking && !sio_probe_rx());
  c = *UWRC;
  return c;
}

int HardwareSerial::sio_putchar(char c, int blocking)
{

  if (blocking){
  /* Check for space in UART FIFO */
    while((*ULSR & UART_LSR_THRE_BIT) == 0);
  }
  // write char
  *UWRC = c;
  return 0;
}

/*
 * Set RS-232 baudrate.  Works well with FT-232R from 9600 to 1000000 bauds.
 */
void HardwareSerial::sio_setbaud(int bauds)
{
  *UBRD = (F_CPU / bauds) / 16;
}

// Public Methods //////////////////////////////////////////////////////////////

void HardwareSerial::begin(unsigned long bauds)
{

  /* SET LSR to be 1's so Whisper will be happy that ch is ready */
  *ULSR = 0xff;
  /* Set DLAB bit in LCR */
  *ULCR |= UART_DLAB_BIT; 

  /* Get UART Dividor Value */
  uint16_t div = (F_CPU / bauds) / 16;

  // Now, we split 'div' into its MSB and LSB.
  uint8_t msb = (uint8_t)(div >> 8); // Shift right by 8 bits to get the MSB
  uint8_t lsb = (uint8_t)(div & 0xFF); // Mask the lower 8 bits to get the LSB

  /* Set divisor regs  devisor = 27: clock_freq/baud_rate*16 -->> clock = 50MHz, baud=115200*/
  *UBRD = lsb;
  *UIER = msb;
  /* 8 data bits, 1 stop bit, no parity, clear DLAB */
  *ULCR = (UART_LCR_CS8 | UART_LCR_1_STB | UART_LCR_PDIS);
  *UFCR = (UART_FCR_FIFO_BIT | UART_FCR_MODE0_BIT | UART_FCR_FIFO_8_BIT | UART_FCR_RCVRCLR_BIT | UART_FCR_XMITCLR_BIT);
  /* disable interrupts  */
  *UIER = (0x00);

}

void HardwareSerial::end(void)
{
}

// int UARTClass::available(void)
// {
//   return sio_probe_rx();
// }

int HardwareSerial::available(void)
{
      if (sio_probe_rx())
    {
      int c = sio_getchar(1);
      if (c != -1) {
          sio_receive(c);
      }
    }

    int availableInBuffer = (sio_rxbuf_head - sio_rxbuf_tail + RX_BUF_SIZE) % RX_BUF_SIZE;

    // If there are characters in the buffer, return the count
    if (availableInBuffer > 0) {
        return availableInBuffer;
    }
    else
    {
      return 0;
    }

}

int HardwareSerial::availableForWrite(void)
{
  int busy;
  busy = (!(*ULSR & UART_LSR_THRE_BIT));
  return (!busy);
}

int HardwareSerial::peek(void)
{
  sio_probe_rx();
  if (sio_rxbuf_tail == sio_rxbuf_head)
    return (-1);
  else
    return (sio_rxbuf[sio_rxbuf_tail]);
}


int HardwareSerial::read(void)
{
    sio_probe_rx();

    // Check if there's a character in the buffer
    if (sio_rxbuf_tail != sio_rxbuf_head) {
        int c = sio_rxbuf[sio_rxbuf_tail];
        sio_rxbuf_tail = (sio_rxbuf_tail + 1) % RX_BUF_SIZE;
        return c;
    }
    else{
      return 0;
    }
}

void HardwareSerial::flush(void)
{
  /* Check for space in UART FIFO */
    while((*ULSR & UART_LSR_THRE_BIT) == 0);
}

size_t
HardwareSerial::write(const uint8_t uc_data) 
{

  sio_putchar(uc_data, 1);
  return (1);
}

// Add received characters to the buffer
void HardwareSerial::sio_receive(char c)
{
    // Check if the buffer is not full
    if ((sio_rxbuf_head + 1) % RX_BUF_SIZE != sio_rxbuf_tail) {
        sio_rxbuf[sio_rxbuf_head] = c;
        sio_rxbuf_head = (sio_rxbuf_head + 1) % RX_BUF_SIZE;
    }
}