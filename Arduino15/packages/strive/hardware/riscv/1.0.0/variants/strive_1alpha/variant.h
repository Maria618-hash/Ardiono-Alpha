
#ifndef _VARIANT_FREEDOM_E300_
#define _VARIANT_FREEDOM_E300_

#ifndef STRIVE_1alpha
#define STRIVE_1alpha
#endif

#include <stdint.h>

//Enable Remapable IOS
#define REMAP_ENABLED
#include "platform.h"


/*----------------------------------------------------------------------------
*        Headers
*----------------------------------------------------------------------------*/

#include "Arduino.h"
#ifdef __cplusplus
#include "HardwareSerial.h"
#endif


/* LEDs */
#define PIN_LED_13          13
#define PIN_LED             3
#define LED_BUILTIN         3

#ifdef __cplusplus
// extern UARTClass Serial;
// extern UARTClass Serial1;
extern HardwareSerial Serial;
extern HardwareSerial Serial1;
extern HardwareSerial Serial2;
extern HardwareSerial Serial3;
extern HardwareSerial Serial4;
extern HardwareSerial Serial5;
extern HardwareSerial Serial6;
extern HardwareSerial Serial7;



#endif

/*
 * SPI Interfaces
 */

#define SPI_INTERFACES_COUNT 6
#define SPI_REG(x) SPI1_REG(x)

#define UART_INTERFACES_COUNT 2
#define UART_REG(x) UART0_REG(x)
#define UART_REGP(i) _REG32P(UART0_BASE_ADDR, (i))

// we only want to enable 3 peripheral managed SPI pins: SCK, MOSI, MISO
// CS pins can either be handled by hardware or bit banged as GPIOs

// static const uint8_t SS   = PIN_SPI1_SS0;
// static const uint8_t SS1  = PIN_SPI1_SS1;
// static const uint8_t SS2  = PIN_SPI1_SS2;
// static const uint8_t SS3  = PIN_SPI1_SS3;
// static const uint8_t MOSI = PIN_SPI1_MOSI;
// static const uint8_t MISO = PIN_SPI1_MISO;
// static const uint8_t SCK  = PIN_SPI1_SCK;

// static const uint32_t SPI_IOF_MASK = (1 << IOF_SPI1_SCK) | (1 << IOF_SPI1_MOSI) | (1 << IOF_SPI1_MISO);
// static const uint32_t IOF_UART_MASK = IOF0_UART0_MASK;

#define VARIANT_DIGITAL_PIN_MAP  {{.io_port = 0, .bit_pos = 57, .pwm_num = 1, .pwm_cmp_num = PWM_N_PTC1}, \
	{.io_port = 0, .bit_pos = 58, .pwm_num = 1, .pwm_cmp_num = PWM_P_PTC1}, \
	{.io_port = 0, .bit_pos = 59, .pwm_num = 2, .pwm_cmp_num = PWM_N_PTC2}, \
	{.io_port = 0, .bit_pos = 60, .pwm_num = 2,  .pwm_cmp_num = PWM_P_PTC2}, \
	{.io_port = 0, .bit_pos = 61, .pwm_num = 3,  .pwm_cmp_num = PWM_N_PTC3}, \
	{.io_port = 0, .bit_pos = 62, .pwm_num = 3,  .pwm_cmp_num = PWM_P_PTC3}, \
	{.io_port = 0, .bit_pos = 63, .pwm_num = 4,  .pwm_cmp_num = PWM_N_PTC4}, \
	{.io_port = 0, .bit_pos = 64, .pwm_num = 4, .pwm_cmp_num = PWM_P_PTC4}, \
	{.io_port = 0, .bit_pos = 65, .pwm_num = 5,  .pwm_cmp_num = PWM_N_PTC5}, \
	{.io_port = 0, .bit_pos = 66,  .pwm_num = 5,  .pwm_cmp_num = PWM_P_PTC5}, \
	{.io_port = 0, .bit_pos = 67,  .pwm_num = 6,  .pwm_cmp_num = PWM_N_PTC6}, \
	{.io_port = 0, .bit_pos = 68,  .pwm_num =6, .pwm_cmp_num  = PWM_P_PTC6}, \
	{.io_port = 0, .bit_pos = 69,  .pwm_num = 7, .pwm_cmp_num = PWM_N_PTC7}, \
	{.io_port = 0, .bit_pos = 70,  .pwm_num = 7, .pwm_cmp_num = PWM_P_PTC7}, \
	{.io_port = 0, .bit_pos = 71,  .pwm_num = 8, .pwm_cmp_num = PWM_N_PTC8}, \
	{.io_port = 0, .bit_pos = 72,  .pwm_num = 8, .pwm_cmp_num = PWM_P_PTC8}, \
	{.io_port = 0, .bit_pos = 73,  .pwm_num = 9,   .pwm_cmp_num = PWM_N_PTC9}, \
	{.io_port = 0, .bit_pos = 74,  .pwm_num = 9,   .pwm_cmp_num = PWM_P_PTC9}, \
	{.io_port = 0, .bit_pos = 75,  .pwm_num = 10,   .pwm_cmp_num = PWM_N_PTC10}, \
	{.io_port = 0, .bit_pos = 76,  .pwm_num = 10,  .pwm_cmp_num = PWM_P_PTC10}, \
	{.io_port = 0, .bit_pos = 77,  .pwm_num = 11,  .pwm_cmp_num = PWM_N_PTC11}, \
	{.io_port = 0, .bit_pos = 78,  .pwm_num = 11, .pwm_cmp_num  = PWM_P_PTC11}, \
	{.io_port = 0, .bit_pos = 79,  .pwm_num = 12, .pwm_cmp_num = PWM_N_PTC12}, \
	{.io_port = 0, .bit_pos = 80,  .pwm_num = 12, .pwm_cmp_num = PWM_P_PTC12}, \
	{.io_port = 0, .bit_pos = 81,  .pwm_num = 13, .pwm_cmp_num = PWM_N_PTC13}, \
	{.io_port = 0, .bit_pos = 82,  .pwm_num = 13, .pwm_cmp_num = PWM_P_PTC13}, \
	{.io_port = 0, .bit_pos = 83,  .pwm_num = 14,   .pwm_cmp_num = PWM_N_PTC14}, \
	{.io_port = 0, .bit_pos = 84,  .pwm_num = 14,   .pwm_cmp_num = PWM_P_PTC14}}

#define VARIANT_NUM_PIN (32)

#define VARIANT_PWM_LIST {(volatile void *) PWM1_BASE_ADDR, \
      (volatile void *) PWM2_BASE_ADDR, \
	  (volatile void *) PWM3_BASE_ADDR, \
	  (volatile void *) PWM4_BASE_ADDR, \
	  (volatile void *) PWM5_BASE_ADDR, \
	  (volatile void *) PWM6_BASE_ADDR, \
	  (volatile void *) PWM7_BASE_ADDR, \
	  (volatile void *) PWM8_BASE_ADDR, \
	  (volatile void *) PWM9_BASE_ADDR, \
	  (volatile void *) PWM10_BASE_ADDR, \
	  (volatile void *) PWM11_BASE_ADDR, \
	  (volatile void *) PWM12_BASE_ADDR, \
	  (volatile void *) PWM13_BASE_ADDR, \
      (volatile void *) PWM14_BASE_ADDR}

#define VARIANT_NUM_PWM (14)
#define VARIANT_NUM_SPI (6)
// For interfacing with the onboard SPI Flash.
#define VARIANT_NUM_QSPI (1)
#define VARIANT_NUM_UART (8)

#endif 
