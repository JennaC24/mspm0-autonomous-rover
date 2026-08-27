/*
 * engr2350_msp432.h
 * Author: Kyle Wilt, RPI
 * Origin Date: 2025-06-05
 * Last Modified: 2025-11-11
 * Version: 0.92
 *
 */

#ifndef ENGR2350_MSPM0_H_
#define ENGR2350_MSPM0_H_

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#include <stdio.h>

// ENGR2350 Specific Driver Libraries
#include "engr2350_gpio.h"
#include "engr2350_timers.h"
#include "engr2350_analog.h"
#include "engr2350_i2c.h"


#define POWER_STARTUP_DELAY    (16)
#define CPUCLK_FREQ            32000000

void sysInit();

int32_t getchar_nw();

// Function to provide the next channel # for the F0 Event Set
uint32_t getNextF0_Channel();

#endif
