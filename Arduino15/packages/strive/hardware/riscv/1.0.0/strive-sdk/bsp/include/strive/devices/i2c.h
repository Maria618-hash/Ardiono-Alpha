// See LICENSE for license details.

/* Register offsets */

#define I2C_PRERlo  0x00    //RW
#define I2C_PRERhi  0x01    //RW
#define I2C_CTR     0x02    //RW
#define I2C_TXR     0x03    //W
#define I2C_RXR     0x03    //R
#define I2C_CR      0x04    //W
#define I2C_SR      0x04    //R

/* Constants */

#define I2C_PRESCALE_DIVIDOR(freq)    ( (F_CPU)/(5*freq))


/* Registers Access */

#include <stdint.h>

// Base-address-parametric register accessors.
// These allow multiple I2C controller instances to share the same driver code.
#define I2C_REG(base, reg)            (*(volatile unsigned *)( (uintptr_t)(base) + ((reg) * 4u) ))
#define I2C_PRERlo_REG_BASE(base)     I2C_REG((base), I2C_PRERlo)
#define I2C_PRERhi_REG_BASE(base)     I2C_REG((base), I2C_PRERhi)
#define I2C_CTR_REG_BASE(base)        I2C_REG((base), I2C_CTR)
#define I2C_TXR_REG_BASE(base)        I2C_REG((base), I2C_TXR)
#define I2C_RXR_REG_BASE(base)        I2C_REG((base), I2C_RXR)
#define I2C_CR_REG_BASE(base)         I2C_REG((base), I2C_CR)
#define I2C_SR_REG_BASE(base)         I2C_REG((base), I2C_SR)

// Backwards-compatible single-instance aliases.
#define I2C_PRERlo_REG      I2C_PRERlo_REG_BASE(I2C_BASE_ADDR)
#define I2C_PRERhi_REG      I2C_PRERhi_REG_BASE(I2C_BASE_ADDR)
#define I2C_CTR_REG         I2C_CTR_REG_BASE(I2C_BASE_ADDR)
#define I2C_TXR_REG         I2C_TXR_REG_BASE(I2C_BASE_ADDR)
#define I2C_RXR_REG         I2C_RXR_REG_BASE(I2C_BASE_ADDR)
#define I2C_CR_REG          I2C_CR_REG_BASE(I2C_BASE_ADDR)
#define I2C_SR_REG          I2C_SR_REG_BASE(I2C_BASE_ADDR)


/* Bits */

// Control Register

#define I2C_CTR_EN 7 // Core Enable
#define I2C_CTR_IEN 6 // Interrupt enable

// Transmit Regsiter
#define I2C_TXR_WR 0

// Command Register
#define I2C_CR_STA 7   // Generate (repeated) start condition
#define I2C_CR_STO 6   // Generate Stop Condition
#define I2C_CR_RD 5    // Read from slave
#define I2C_CR_WR 4    // Write to slave
#define I2C_CR_ACK 3   // When a receiver, sent ACK (ACK = '0') or NACK (ACK = '1')
#define I2C_CR_IACK 0  // Interrupt acknowledge. When set, clears a pending interrupt.


// Status Register
#define I2C_SR_RxACK 7   // Received acknowledge from slave
#define I2C_SR_Busy 6    // I2C bus busy
#define I2C_SR_AL 5      // Arbitration lost
#define I2C_SR_TIP 1     // Transfer in progress
#define I2C_SR_IF 0      // Interrupt Flag
