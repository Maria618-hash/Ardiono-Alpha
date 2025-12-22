// See LICENSE for license details.
// Some things missing from the official encoding.h

#define MCAUSE_INT         0x80000000
#define MCAUSE_CAUSE       0x7FFFFFFF

#include "strive/const.h"
#include "strive/devices/aon.h"
#include "strive/devices/clint.h"
#include "strive/devices/gpio.h"
#include "strive/devices/plic.h"
#include "strive/devices/pwm.h"
#include "strive/devices/spi.h"
#include "strive/devices/uart.h"
#include "strive/devices/remap.h"
#include "strive/devices/i2c.h"

/****************************************************************************
 * Platform definitions
 *****************************************************************************/


#define TRAPVEC_TABLE_BASE_ADDR _AC(0x00001010,UL)
#define CLINT_BASE_ADDR _AC(0x02000000,UL)
#define PLIC_BASE_ADDR _AC(0x0C000000,UL)
#define AON_BASE_ADDR _AC(0x10000000,UL)

// Memory mapping from your datasheet
//#define RAM_BASE_ADDR _AC(0x00000000,UL)
//#define RAM_SIZE 0x10000  // 64KB RAM
//#define BOOT_ROM_BASE_ADDR _AC(0x80000000,UL)
//#define SYSCON_BASE_ADDR _AC(0x80001000,UL)
#define MEM_BASE_ADDR _AC(0x80000000,UL)
#define SPI_FLASH_BASE_ADDR _AC(0x80001040,UL)

// UART definitions (8 UARTs)
#define UART1_BASE_ADDR _AC(0x80002000,UL)
#define UART2_BASE_ADDR _AC(0x80003000,UL)
#define UART3_BASE_ADDR _AC(0x80004000,UL)
#define UART4_BASE_ADDR _AC(0x80005000,UL)
#define UART5_BASE_ADDR _AC(0x80006000,UL)
#define UART6_BASE_ADDR _AC(0x80007000,UL)
#define UART7_BASE_ADDR _AC(0x80008000,UL)
#define UART8_BASE_ADDR _AC(0x8000D000,UL)

// CAN definitions (2 CAN controllers)
#define CAN1_BASE_ADDR _AC(0x80009400,UL)
#define CAN2_BASE_ADDR _AC(0x80009800,UL)

// PWM definitions (14 PWM channels)
#define PWM1_BASE_ADDR _AC(0x80009E40,UL)
#define PWM2_BASE_ADDR _AC(0x80009E80,UL)
#define PWM3_BASE_ADDR _AC(0x80009EC0,UL)
#define PWM4_BASE_ADDR _AC(0x80009F00,UL)
#define PWM5_BASE_ADDR _AC(0x80009F40,UL)
#define PWM6_BASE_ADDR _AC(0x80009F80,UL)
#define PWM7_BASE_ADDR _AC(0x80009FC0,UL)
#define PWM8_BASE_ADDR _AC(0x8000A000,UL)
#define PWM9_BASE_ADDR _AC(0x8000A040,UL)
#define PWM10_BASE_ADDR _AC(0x8000A080,UL)
#define PWM11_BASE_ADDR _AC(0x8000A0C0,UL)
#define PWM12_BASE_ADDR _AC(0x8000A100,UL)
#define PWM13_BASE_ADDR _AC(0x8000A140,UL)
#define PWM14_BASE_ADDR _AC(0x8000A180,UL)

// Input Capture definitions (4 channels)
#define INPUT_CAPTURE1_BASE_ADDR _AC(0x8000A1C0,UL)
#define INPUT_CAPTURE2_BASE_ADDR _AC(0x8000A200,UL)
#define INPUT_CAPTURE3_BASE_ADDR _AC(0x8000A240,UL)
#define INPUT_CAPTURE4_BASE_ADDR _AC(0x8000A280,UL)

// External Timer definitions (16 timers)
#define EXT_TIMER1_BASE_ADDR _AC(0x8000A2C0,UL)
#define EXT_TIMER2_BASE_ADDR _AC(0x8000A300,UL)
#define EXT_TIMER3_BASE_ADDR _AC(0x8000A340,UL)
#define EXT_TIMER4_BASE_ADDR _AC(0x8000A380,UL)
#define EXT_TIMER5_BASE_ADDR _AC(0x8000A3C0,UL)
#define EXT_TIMER6_BASE_ADDR _AC(0x8000A400,UL)
#define EXT_TIMER7_BASE_ADDR _AC(0x8000A440,UL)
#define EXT_TIMER8_BASE_ADDR _AC(0x8000A480,UL)
#define EXT_TIMER9_BASE_ADDR _AC(0x8000A4C0,UL)
#define EXT_TIMER10_BASE_ADDR _AC(0x8000A500,UL)
#define EXT_TIMER11_BASE_ADDR _AC(0x8000A540,UL)
#define EXT_TIMER12_BASE_ADDR _AC(0x8000A580,UL)
#define EXT_TIMER13_BASE_ADDR _AC(0x8000A5C0,UL)
#define EXT_TIMER14_BASE_ADDR _AC(0x8000A600,UL)
#define EXT_TIMER15_BASE_ADDR _AC(0x8000A640,UL)
#define EXT_TIMER16_BASE_ADDR _AC(0x8000A680,UL)

// Watchdog Timer
#define WATCHDOG_BASE_ADDR _AC(0x8000A700,UL)

// GPIO definitions (3 GPIO modules for pins 1-94)
#define GPIO1_BASE_ADDR _AC(0x8000A800,UL)  // GPIO 1-32
#define GPIO2_BASE_ADDR _AC(0x8000A900,UL)  // GPIO 33-64
#define GPIO3_BASE_ADDR _AC(0x8000AA00,UL)  // GPIO 65-94

// AES Encryption/Decryption
#define AES_ENC_BASE_ADDR _AC(0x8000AB00,UL)
#define AES_DEC_BASE_ADDR _AC(0x8000AC00,UL)

// I2C definitions (3 I2C controllers)
#define I2C_BASE_ADDR _AC(0x8000AD00,UL)
#define I2C2_BASE_ADDR _AC(0x8000AE00,UL)
#define I2C3_BASE_ADDR _AC(0x8000AF00,UL)

// Remappable and Pin Select
#define REMAPPABLE_BASE_ADDR _AC(0x8000B000,UL)
#define PIN_SELECT_BASE_ADDR _AC(0x8000B100,UL)

// SPI ADC definitions
#define SPI_ADC1_BASE_ADDR _AC(0x8000B200,UL)
#define SPI_ADC2_BASE_ADDR _AC(0x8000B400,UL)

// SPI Accelerator definitions (6 SPI controllers)
#define SPI1_ACCEL_BASE_ADDR _AC(0x8000B600,UL)
#define SPI2_ACCEL_BASE_ADDR _AC(0x8000BA00,UL)
#define SPI3_ACCEL_BASE_ADDR _AC(0x8000BE00,UL)
#define SPI4_ACCEL_BASE_ADDR _AC(0x8000C200,UL)
#define SPI5_ACCEL_BASE_ADDR _AC(0x8000C600,UL)
#define SPI6_ACCEL_BASE_ADDR _AC(0x8000CA00,UL)


// IOF Mappings
/*#define IOF0_SPI1_MASK          _AC(0x000007FC,UL)
#define SPI11_NUM_SS     (4)
#define IOF_SPI1_SS0          (2u)
#define IOF_SPI1_SS1          (8u)
#define IOF_SPI1_SS2          (9u)
#define IOF_SPI1_SS3          (10u)
#define IOF_SPI1_MOSI         (3u)
#define IOF_SPI1_MISO         (4u)
#define IOF_SPI1_SCK          (5u)
#define IOF_SPI1_DQ0          (3u)
#define IOF_SPI1_DQ1          (4u)
#define IOF_SPI1_DQ2          (6u)
#define IOF_SPI1_DQ3          (7u)

#define IOF0_SPI2_MASK          _AC(0xFC000000,UL)
#define SPI2_NUM_SS       (1)
#define IOF_SPI2_SS0          (26u)
#define IOF_SPI2_MOSI         (27u)
#define IOF_SPI2_MISO         (28u)
#define IOF_SPI2_SCK          (29u)
#define IOF_SPI2_DQ0          (27u)
#define IOF_SPI2_DQ1          (28u)
#define IOF_SPI2_DQ2          (30u)
#define IOF_SPI2_DQ3          (31u)

#define IOF0_UART0_MASK         _AC(0x00030000, UL)
#define IOF_UART0_RX   (16u)
#define IOF_UART0_TX   (17u)

#define IOF0_UART1_MASK         _AC(0x03000000, UL)
#define IOF_UART1_RX (24u)
#define IOF_UART1_TX (25u)

#define IOF1_PWM0_MASK          _AC(0x0000000F, UL)
#define IOF1_PWM1_MASK          _AC(0x00780000, UL)
#define IOF1_PWM2_MASK          _AC(0x00003C00, UL)

// Interrupt Numbers
#define INT_RESERVED 0
#define INT_WDOGCMP 1
#define INT_RTCCMP 2
#define INT_UART0_BASE 3
#define INT_UART1_BASE 4
#define INT_SPI0_BASE 5
#define INT_SPI1_BASE 6
#define INT_SPI2_BASE 7
#define INT_GPIO_BASE 8
#define INT_PWM0_BASE 40
#define INT_PWM1_BASE 44
#define INT_PWM2_BASE 48
*/
// Helper functions
#define _REG32(p, i) (*(volatile uint32_t *) ((p) + (i)))
#define _REG32P(p, i) ((volatile uint32_t *) ((p) + (i)))
#define AON_REG(offset) _REG32(AON_BASE_ADDR, offset)
#define CLINT_REG(offset) _REG32(CLINT_BASE_ADDR, offset)


//////////////////////////////////////////////////
#define GPIO1_REG(offset) _REG32(GPIO1_BASE_ADDR, offset)
#define GPIO2_REG(offset) _REG32(GPIO2_BASE_ADDR, offset)
#define GPIO3_REG(offset) _REG32(GPIO3_BASE_ADDR, offset)

// UART register access
#define UART1_REG(offset) _REG32(UART1_BASE_ADDR, offset)
#define UART2_REG(offset) _REG32(UART2_BASE_ADDR, offset)
#define UART3_REG(offset) _REG32(UART3_BASE_ADDR, offset)
#define UART4_REG(offset) _REG32(UART4_BASE_ADDR, offset)
#define UART5_REG(offset) _REG32(UART5_BASE_ADDR, offset)
#define UART6_REG(offset) _REG32(UART6_BASE_ADDR, offset)
#define UART7_REG(offset) _REG32(UART7_BASE_ADDR, offset)
#define UART8_REG(offset) _REG32(UART8_BASE_ADDR, offset)

// PWM register access
#define PWM1_REG(offset) _REG32(PWM1_BASE_ADDR, offset)
#define PWM2_REG(offset) _REG32(PWM2_BASE_ADDR, offset)
#define PWM3_REG(offset) _REG32(PWM3_BASE_ADDR, offset)
#define PWM4_REG(offset) _REG32(PWM4_BASE_ADDR, offset)
#define PWM5_REG(offset) _REG32(PWM5_BASE_ADDR, offset)
#define PWM6_REG(offset) _REG32(PWM6_BASE_ADDR, offset)
#define PWM7_REG(offset) _REG32(PWM7_BASE_ADDR, offset)
#define PWM8_REG(offset) _REG32(PWM8_BASE_ADDR, offset)
#define PWM9_REG(offset) _REG32(PWM9_BASE_ADDR, offset)
#define PWM10_REG(offset) _REG32(PWM10_BASE_ADDR, offset)
#define PWM11_REG(offset) _REG32(PWM11_BASE_ADDR, offset)
#define PWM12_REG(offset) _REG32(PWM12_BASE_ADDR, offset)
#define PWM13_REG(offset) _REG32(PWM13_BASE_ADDR, offset)
#define PWM14_REG(offset) _REG32(PWM14_BASE_ADDR, offset)

// I2C register access
#define I2C1_REG(offset) _REG32(I2C1_BASE_ADDR, offset)
#define I2C2_REG(offset) _REG32(I2C2_BASE_ADDR, offset)
#define I2C3_REG(offset) _REG32(I2C3_BASE_ADDR, offset)

// CAN register access
#define CAN1_REG(offset) _REG32(CAN1_BASE_ADDR, offset)
#define CAN2_REG(offset) _REG32(CAN2_BASE_ADDR, offset)

// AES register access
#define AES_ENC_REG(offset) _REG32(AES_ENC_BASE_ADDR, offset)
#define AES_DEC_REG(offset) _REG32(AES_DEC_BASE_ADDR, offset)

// SPI register access
#define SPI1_ACCEL_REG(offset) _REG32(SPI1_ACCEL_BASE_ADDR, offset)
#define SPI2_ACCEL_REG(offset) _REG32(SPI2_ACCEL_BASE_ADDR, offset)
#define SPI3_ACCEL_REG(offset) _REG32(SPI3_ACCEL_BASE_ADDR, offset)
#define SPI4_ACCEL_REG(offset) _REG32(SPI4_ACCEL_BASE_ADDR, offset)
#define SPI5_ACCEL_REG(offset) _REG32(SPI5_ACCEL_BASE_ADDR, offset)
#define SPI6_ACCEL_REG(offset) _REG32(SPI6_ACCEL_BASE_ADDR, offset)


// Misc

#include <stdint.h>


//#define NUM_GPIO 94

//#define PLIC_NUM_INTERRUPTS 52
//#define PLIC_NUM_PRIORITIES 7

#define HAS_BOARD_BUTTONS
#include "hifive1.h"

unsigned long get_timer_freq(void);
uint64_t get_timer_value(void);

