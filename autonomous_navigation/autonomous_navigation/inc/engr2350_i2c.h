
/*
 * engr2350_i2c.h
 * Author: Kyle Wilt, RPI
 * Origin Date: 2025-11-11
 * Last Modified: 2025-11-14
 * Version: 0.90
 *
 * Note: For simplicity, the I2C clock is automatically configured
 * to use BUSCLK/1 when calling I2C_initI2C().
 */

 #ifndef ENGR2350_I2C_H
 #define ENGR2350_I2C_H

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>


typedef enum {
    I2C_ADDR_MODE_7BIT = DL_I2C_TARGET_ADDRESSING_MODE_7_BIT,
    I2C_ADDR_MODE_10BIT = DL_I2C_TARGET_ADDRESSING_MODE_10_BIT,
} I2C_ADDR_MODE;

typedef struct {
    uint32_t busclkRate;
    uint32_t bitRate;
    I2C_ADDR_MODE addrMode;
} I2C_ControllerConfig;

void I2C_initController( I2C_Regs *i2c , I2C_ControllerConfig *cfg );

uint32_t I2C_writeData( I2C_Regs *i2c , uint16_t addr , uint8_t startReg , uint8_t *data , uint32_t len );
uint32_t I2C_readData ( I2C_Regs *i2c , uint16_t addr , uint8_t startReg , uint8_t *data , uint32_t len );





 #endif