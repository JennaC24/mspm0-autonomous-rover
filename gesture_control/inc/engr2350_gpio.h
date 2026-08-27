
/*
 * engr2350_gpio.h
 * Author: Kyle Wilt, RPI
 * Origin Date: 2025-06-11
 * Last Modified: 2025-11-12
 * Version: 0.94
 *
 */

#ifndef ENGR2350_GPIO_H_
#define ENGR2350_GPIO_H_

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>
#include "engr2350_pfmap.h"

/* Pin Definitions */
#define GPIO_PIN0        DL_GPIO_PIN_0 
#define GPIO_PIN1        DL_GPIO_PIN_1 
#define GPIO_PIN2        DL_GPIO_PIN_2 
#define GPIO_PIN3        DL_GPIO_PIN_3 
#define GPIO_PIN4        DL_GPIO_PIN_4 
#define GPIO_PIN5        DL_GPIO_PIN_5 
#define GPIO_PIN6        DL_GPIO_PIN_6 
#define GPIO_PIN7        DL_GPIO_PIN_7 
#define GPIO_PIN8        DL_GPIO_PIN_8 
#define GPIO_PIN9        DL_GPIO_PIN_9 
#define GPIO_PIN10       DL_GPIO_PIN_10 
#define GPIO_PIN11       DL_GPIO_PIN_11 
#define GPIO_PIN12       DL_GPIO_PIN_12 
#define GPIO_PIN13       DL_GPIO_PIN_13 
#define GPIO_PIN14       DL_GPIO_PIN_14 
#define GPIO_PIN15       DL_GPIO_PIN_15 
#define GPIO_PIN16       DL_GPIO_PIN_16 
#define GPIO_PIN17       DL_GPIO_PIN_17 
#define GPIO_PIN18       DL_GPIO_PIN_18 
#define GPIO_PIN19       DL_GPIO_PIN_19 
#define GPIO_PIN20       DL_GPIO_PIN_20 
#define GPIO_PIN21       DL_GPIO_PIN_21 
#define GPIO_PIN22       DL_GPIO_PIN_22 
#define GPIO_PIN23       DL_GPIO_PIN_23 
#define GPIO_PIN24       DL_GPIO_PIN_24 
#define GPIO_PIN25       DL_GPIO_PIN_25 
#define GPIO_PIN26       DL_GPIO_PIN_26 
#define GPIO_PIN27       DL_GPIO_PIN_27 
#define GPIO_PIN28       DL_GPIO_PIN_28 
#define GPIO_PIN29       DL_GPIO_PIN_29 
#define GPIO_PIN30       DL_GPIO_PIN_30 
#define GPIO_PIN31       DL_GPIO_PIN_31 

/* Defines for easier PINCMx identification/use */
#define IOMUX_PINCM_PA0     (0)
#define IOMUX_PINCM_PA1     (1)
#define IOMUX_PINCM_PA2     (6)
#define IOMUX_PINCM_PA3     (7)
#define IOMUX_PINCM_PA4     (8)
#define IOMUX_PINCM_PA5     (9)
#define IOMUX_PINCM_PA6     (10)
#define IOMUX_PINCM_PA7     (13)
#define IOMUX_PINCM_PA8     (18)
#define IOMUX_PINCM_PA9     (19)
#define IOMUX_PINCM_PA10    (20)
#define IOMUX_PINCM_PA11    (21)
#define IOMUX_PINCM_PA12    (33)
#define IOMUX_PINCM_PA13    (34)
#define IOMUX_PINCM_PA14    (35)
#define IOMUX_PINCM_PA15    (36)
#define IOMUX_PINCM_PA16    (37)
#define IOMUX_PINCM_PA17    (38)
#define IOMUX_PINCM_PA18    (39)
#define IOMUX_PINCM_PA19    (40)
#define IOMUX_PINCM_PA20    (41)
#define IOMUX_PINCM_PA21    (45)
#define IOMUX_PINCM_PA22    (46)
#define IOMUX_PINCM_PA23    (52)
#define IOMUX_PINCM_PA24    (53)
#define IOMUX_PINCM_PA25    (54)
#define IOMUX_PINCM_PA26    (58)
#define IOMUX_PINCM_PA27    (59)
#define IOMUX_PINCM_PA28    (2)
#define IOMUX_PINCM_PA29    (3)
#define IOMUX_PINCM_PA30    (4)
#define IOMUX_PINCM_PA31    (5)
#define IOMUX_PINCM_PB0     (11)
#define IOMUX_PINCM_PB1     (12)
#define IOMUX_PINCM_PB2     (14)
#define IOMUX_PINCM_PB3     (15)
#define IOMUX_PINCM_PB4     (16)
#define IOMUX_PINCM_PB5     (17)
#define IOMUX_PINCM_PB6     (22)
#define IOMUX_PINCM_PB7     (23)
#define IOMUX_PINCM_PB8     (24)
#define IOMUX_PINCM_PB9     (25)
#define IOMUX_PINCM_PB10    (26)
#define IOMUX_PINCM_PB11    (27)
#define IOMUX_PINCM_PB12    (28)
#define IOMUX_PINCM_PB13    (29)
#define IOMUX_PINCM_PB14    (30)
#define IOMUX_PINCM_PB15    (31)
#define IOMUX_PINCM_PB16    (32)
#define IOMUX_PINCM_PB17    (42)
#define IOMUX_PINCM_PB18    (43)
#define IOMUX_PINCM_PB19    (44)
#define IOMUX_PINCM_PB20    (47)
#define IOMUX_PINCM_PB21    (48)
#define IOMUX_PINCM_PB22    (49)
#define IOMUX_PINCM_PB23    (50)
#define IOMUX_PINCM_PB24    (51)
#define IOMUX_PINCM_PB25    (55)
#define IOMUX_PINCM_PB26    (56)
#define IOMUX_PINCM_PB27    (57)
// Pins B28-B31 do not exist

// Internal pullup/down resistor options
typedef enum {
    GPIO_PULL_NONE=0,
    GPIO_PULL_DOWN=1,
    GPIO_PULL_UP=2,
} gpio_pull_t;

// Interrupt polarity options
typedef enum {
    GPIO_INT_POLARITY_NONE=0,
    GPIO_INT_EDGE_RISE=1,
    GPIO_INT_EDGE_FALL=2,
    GPIO_INT_EDGE_RISE_FALL=3,
} gpio_int_polarity_t;

// Interrupt support
#define GPIO_INT_IRQn GPIOA_INT_IRQn // Both GPIOA_INT_IRQn and GPIOB_INT_IRQn  point to same thing


// These functions are modified from their DL_GPIO counterparts to avoid the IOMUX_PINCM work.
// They *are not* efficient due to needing to look up the PINCM index for each passed pin.
void GPIO_initDigitalInput(GPIO_Regs* gpio,uint32_t pins);
void GPIO_initDigitalOutput(GPIO_Regs* gpio,uint32_t pins);
void GPIO_setInternalResistor(GPIO_Regs* gpio,uint32_t pins, gpio_pull_t pull);
void GPIO_initPeripheralFunction(GPIO_Regs* gpio,uint32_t pins, uint32_t function);
//void GPIO_initPeripheralOutputFunction(GPIO_Regs* gpio,uint32_t pins, uint32_t function);
//void GPIO_initPeripheralInputFunction(GPIO_Regs* gpio,uint32_t pins, uint32_t function);
void GPIO_initPeripheralAnalogFunction(GPIO_Regs* gpio,uint32_t pins);
void GPIO_setOpenDrain(GPIO_Regs* gpio,uint32_t pins);
void GPIO_setPushPush(GPIO_Regs* gpio,uint32_t pins);

// These functions are just renamed versions of the DL_GPIO functions (for consistency)
// Only functions necessary for ENGR2350 are renamed here.
static inline void GPIO_enablePower(GPIO_Regs* gpio){ DL_GPIO_enablePower(gpio);}
static inline uint32_t GPIO_readPins(GPIO_Regs* gpio,uint32_t pins){ return DL_GPIO_readPins(gpio,pins);}
static inline void GPIO_writePins(GPIO_Regs* gpio,uint32_t pins){ DL_GPIO_writePins(gpio,pins);}
static inline void GPIO_setPins(GPIO_Regs* gpio,uint32_t pins){ DL_GPIO_setPins(gpio,pins);}
static inline void GPIO_clearPins(GPIO_Regs* gpio,uint32_t pins){ DL_GPIO_clearPins(gpio,pins);}
static inline void GPIO_togglePins(GPIO_Regs* gpio,uint32_t pins){ DL_GPIO_togglePins(gpio,pins);}
static inline void GPIO_enableInterrupt(GPIO_Regs* gpio,uint32_t pins){ DL_GPIO_enableInterrupt(gpio,pins);}
static inline void GPIO_disableInterrupt(GPIO_Regs* gpio,uint32_t pins){ DL_GPIO_disableInterrupt(gpio,pins);}
static inline uint32_t GPIO_getEnabledInterrupts(GPIO_Regs* gpio,uint32_t pins){ return DL_GPIO_getEnabledInterrupts(gpio,pins);}
static inline uint32_t GPIO_getPendingInterrupts(GPIO_Regs* gpio){ return DL_GPIO_getEnabledInterruptStatus(gpio,0xFFFFFFFF);}
static inline uint32_t GPIO_getAllPendingInterrupts(GPIO_Regs* gpio){ return DL_GPIO_getRawInterruptStatus(gpio,0xFFFFFFFF);}
static inline void GPIO_setInterrupt(GPIO_Regs* gpio,uint32_t pins){ DL_GPIO_setInterrupt(gpio,pins);}
static inline void GPIO_clearInterrupt(GPIO_Regs* gpio,uint32_t pins){ DL_GPIO_clearInterruptStatus(gpio,pins);}

// These functions are modified for easier use as complared to DL_GPIO counterparts
void GPIO_setInterruptPolarity(GPIO_Regs* gpio,uint32_t pins,gpio_int_polarity_t polarity);
uint32_t GPIO_getActiveInterrupt(GPIO_Regs* gpio);

#endif