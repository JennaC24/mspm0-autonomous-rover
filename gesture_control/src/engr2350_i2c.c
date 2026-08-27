/*
 * engr2350_i2c.h
 * Author: Kyle Wilt, RPI
 * Origin Date: 2025-11-11
 * Last Modified: 2025-11-14
 * Version: 0.90
 *
 */

 #include"engr2350_i2c.h"

#define MOD_I2C_CLK_DIV    8

void I2C_initController( I2C_Regs *i2c , I2C_ControllerConfig *cfg ){
    DL_I2C_enablePower(i2c);
    DL_I2C_resetControllerTransfer(i2c);
    DL_I2C_ClockConfig i2ccfg = {
        .clockSel = DL_I2C_CLOCK_BUSCLK,
        .divideRatio = MOD_I2C_CLK_DIV -1
    };
    DL_I2C_setClockConfig(i2c,&i2ccfg);
    // Calculate the timer period
    float modclk = ((float)cfg->busclkRate)/MOD_I2C_CLK_DIV;
    uint8_t prd = (modclk/cfg->bitRate)/10-1+0.5; // +0.5 for round to nearest
    prd &= 0x7F; // max value 127
    cfg->bitRate = (modclk/10)/(prd+1); // update struct to indicate actual frequency
    DL_I2C_setTimerPeriod(i2c,prd);
    DL_I2C_setTargetAddressingMode(i2c,(DL_I2C_TARGET_ADDRESSING_MODE)cfg->addrMode);
    i2c->MASTER.MCR |= 1<<2; // enable clock stretching
    DL_I2C_enableController(i2c);
}

uint32_t I2C_writeData( I2C_Regs *i2c , uint16_t addr , uint8_t startReg , uint8_t *data , uint32_t len ){
    while(i2c->MASTER.MSR & 0x01); // wait for any current transmissions to complete
    DL_I2C_startControllerTransfer(i2c,(uint32_t) addr,DL_I2C_CONTROLLER_DIRECTION_TX,len+1);
    i2c->MASTER.MTXDATA = startReg;
    uint32_t len_orig = len;
    while(!(i2c->MASTER.MSR & 0x02) && len){
        len -= DL_I2C_fillControllerTXFIFO(i2c,&data[len_orig-len],1); // Not efficient, but don't care
    }
    while(i2c->MASTER.MSR & 0x01); // wait for current transmissions to complete
    i2c->MASTER.MFIFOCTL |= 0x80; // Flush any remaining data, just in case
    while((i2c->MASTER.MFIFOSR & 0x0F00) != 0x0800){} // wait until txfifo is empty
    i2c->MASTER.MFIFOCTL &= ~0x80; // clear the TX Flush trigger
    delay_cycles(3200); // Add a delay here just in case
    return (i2c->MASTER.MSR & 0x02) == 0x02; // return 1 if tx error, 0 if good
}

uint32_t I2C_readData ( I2C_Regs *i2c , uint16_t addr , uint8_t startReg , uint8_t *data , uint32_t len ){
    while(i2c->MASTER.MSR & 0x01); // wait for any current transmissions to complete
    DL_I2C_startControllerTransfer(i2c,(uint32_t) addr,DL_I2C_CONTROLLER_DIRECTION_TX,1);
    i2c->MASTER.MTXDATA = startReg;
    while(i2c->MASTER.MSR & 0x01); // wait for any current transmissions to complete
    i2c->MASTER.MFIFOCTL |= 0x80; // Flush any remaining data, just in case
    while((i2c->MASTER.MFIFOSR & 0x0F00) != 0x0800){} // wait until txfifo is empty
    i2c->MASTER.MFIFOCTL &= ~0x80; // clear the TX Flush trigger
    if(i2c->MASTER.MSR & 0x02) return 1; // return 1 if transmit error

    delay_cycles(3200); // Add a delay here just in case
    DL_I2C_startControllerTransfer(i2c,(uint32_t) addr,DL_I2C_CONTROLLER_DIRECTION_RX,len);
    while(i2c->MASTER.MSR & 0x01){ // while receiving, pull received data bytes
        if(i2c->MASTER.MFIFOSR & 0x000F) *data++ = i2c->MASTER.MRXDATA;
    }
    delay_cycles(3200); // Add a delay here just in case
    // if(i2c->MASTER.MFIFOSR & 0x000F) *data++ = i2c->MASTER.MRXDATA; // Grab remaining byte, if available
    return i2c->MASTER.MSR & 0x02; // return 2 if rx error, 0 if good



}
