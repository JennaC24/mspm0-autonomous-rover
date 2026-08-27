
/*
 * engr2350_gpio.c
 * Author: Kyle Wilt, RPI
 * Origin Date: 2025-06-11
 * Last Modified: 2025-11-11
 * Version: 0.94
 *
 */

#include"engr2350_gpio.h"

// Alternative mapping of PINCM to Port/Pin:
const uint8_t IOMUX_PINCM_PA[] = {
    IOMUX_PINCM_PA0,
    IOMUX_PINCM_PA1,
    IOMUX_PINCM_PA2,
    IOMUX_PINCM_PA3,
    IOMUX_PINCM_PA4,
    IOMUX_PINCM_PA5,
    IOMUX_PINCM_PA6,
    IOMUX_PINCM_PA7,
    IOMUX_PINCM_PA8,
    IOMUX_PINCM_PA9,
    IOMUX_PINCM_PA10,
    IOMUX_PINCM_PA11,
    IOMUX_PINCM_PA12,
    IOMUX_PINCM_PA13,
    IOMUX_PINCM_PA14,
    IOMUX_PINCM_PA15,
    IOMUX_PINCM_PA16,
    IOMUX_PINCM_PA17,
    IOMUX_PINCM_PA18,
    IOMUX_PINCM_PA19,
    IOMUX_PINCM_PA20,
    IOMUX_PINCM_PA21,
    IOMUX_PINCM_PA22,
    IOMUX_PINCM_PA23,
    IOMUX_PINCM_PA24,
    IOMUX_PINCM_PA25,
    IOMUX_PINCM_PA26,
    IOMUX_PINCM_PA27,
    IOMUX_PINCM_PA28,
    IOMUX_PINCM_PA29,
    IOMUX_PINCM_PA30,
    IOMUX_PINCM_PA31,
};
const uint8_t IOMUX_PINCM_PB[] = {
    IOMUX_PINCM_PB0,
    IOMUX_PINCM_PB1,
    IOMUX_PINCM_PB2,
    IOMUX_PINCM_PB3,
    IOMUX_PINCM_PB4,
    IOMUX_PINCM_PB5,
    IOMUX_PINCM_PB6,
    IOMUX_PINCM_PB7,
    IOMUX_PINCM_PB8,
    IOMUX_PINCM_PB9,
    IOMUX_PINCM_PB10,
    IOMUX_PINCM_PB11,
    IOMUX_PINCM_PB12,
    IOMUX_PINCM_PB13,
    IOMUX_PINCM_PB14,
    IOMUX_PINCM_PB15,
    IOMUX_PINCM_PB16,
    IOMUX_PINCM_PB17,
    IOMUX_PINCM_PB18,
    IOMUX_PINCM_PB19,
    IOMUX_PINCM_PB20,
    IOMUX_PINCM_PB21,
    IOMUX_PINCM_PB22,
    IOMUX_PINCM_PB23,
    IOMUX_PINCM_PB24,
    IOMUX_PINCM_PB25,
    IOMUX_PINCM_PB26,
    IOMUX_PINCM_PB27,
};

const uint8_t * port_list; // Port list to extract PINCM values from
uint8_t pin_number; // Variable to track current in extraction by pin number
uint32_t pin_mask; // mask to track current pin extracted
uint32_t pincm_extracted; // Variable to store extracted pin number

uint32_t setupPINCMFromPINSExtraction(GPIO_Regs* gpio,uint32_t * pins){
    pin_number = 0; // Reset extraction routine
    pin_mask = 0; // Mask starts empty
    if(gpio == GPIOA) port_list = IOMUX_PINCM_PA;
    else if(gpio == GPIOB){
        port_list = IOMUX_PINCM_PB;
        (*pins) &= 0x0FFFFFFF; // Remove B28-B31 is exists in *pins as invalid
    } 
    else{
        return 1; // Invalid port identified, indicate error
    }
    return 0; // Indicate success

}

int8_t extractNextPINCMFromPINS(uint32_t * pins){
    while(*pins){
        if(*pins & 0x01){
            pincm_extracted = port_list[pin_number]; // extract pincm value
            pin_number++; // move to the net pin (for next iteration)
            (*pins)>>=1; // shift out last used pin
            return 1; // End function, mark that pin was found
        }
        // Move pinmask
        if(pin_mask) pin_mask <<=1; // if pin_mask is started, move left
        else pin_mask = 1; // if not started yet (pin0), initialize the mask
        pin_number++; // Even if not an active pin, move forward
        (*pins)>>=1; // and shift out last checked pin
    }
    return 0;
}

void GPIO_initDigitalInput(GPIO_Regs* gpio,uint32_t pins){
    if(setupPINCMFromPINSExtraction(gpio,&pins)) return; // Don't do anything if gpio input is invalid
    DL_GPIO_disableOutput(gpio,pins);
    while(extractNextPINCMFromPINS(&pins)){
        DL_GPIO_initDigitalInput(pincm_extracted);
    }
}

void GPIO_initDigitalOutput(GPIO_Regs* gpio,uint32_t pins){
    if(setupPINCMFromPINSExtraction(gpio,&pins)) return; // Don't do anything if gpio input is invalid
    DL_GPIO_enableOutput(gpio,pins);
    while(extractNextPINCMFromPINS(&pins)){
        DL_GPIO_initDigitalOutput(pincm_extracted);
        //DL_GPIO_enableOutput(gpio,pin_mask);
        IOMUX->SECCFG.PINCM[pincm_extracted] |= IOMUX_PINCM_INENA_ENABLE; // Allow pin to be read
    }
}

void GPIO_setInternalResistor(GPIO_Regs* gpio,uint32_t pins, gpio_pull_t pull){
    if(setupPINCMFromPINSExtraction(gpio,&pins)) return; // Don't do anything if gpio input is invalid
    while(extractNextPINCMFromPINS(&pins)){
        IOMUX->SECCFG.PINCM[pincm_extracted] &= ~0x00030000; // First, disable resistor.
        IOMUX->SECCFG.PINCM[pincm_extracted] |= pull << 16;
    }
}


void GPIO_initPeripheralFunction(GPIO_Regs* gpio,uint32_t pins, uint32_t function){
    if(setupPINCMFromPINSExtraction(gpio,&pins)) return; // Don't do anything if gpio input is invalid
    while(extractNextPINCMFromPINS(&pins)){
        // Always set AF to input - They all do the same thing except this one also enables the input buffers
        DL_GPIO_initPeripheralInputFunction(pincm_extracted,function);
    }
}

// void GPIO_initPeripheralOutputFunction(GPIO_Regs* gpio,uint32_t pins, uint32_t function){
//     if(setupPINCMFromPINSExtraction(gpio,&pins)) return; // Don't do anything if gpio input is invalid
//     while(extractNextPINCMFromPINS(&pins)){
//         DL_GPIO_initPeripheralOutputFunction(pincm_extracted,function);
//     }
// }

// void GPIO_initPeripheralInputFunction(GPIO_Regs* gpio,uint32_t pins, uint32_t function){
//     if(setupPINCMFromPINSExtraction(gpio,&pins)) return; // Don't do anything if gpio input is invalid
//     while(extractNextPINCMFromPINS(&pins)){
//         DL_GPIO_initPeripheralInputFunction(pincm_extracted,function);
//     }
// }

void GPIO_initPeripheralAnalogFunction(GPIO_Regs* gpio,uint32_t pins){
    if(setupPINCMFromPINSExtraction(gpio,&pins)) return; // Don't do anything if gpio input is invalid
    while(extractNextPINCMFromPINS(&pins)){
        DL_GPIO_initPeripheralAnalogFunction(pincm_extracted);
    }
}

void GPIO_setOpenDrain(GPIO_Regs* gpio,uint32_t pins){
    if(setupPINCMFromPINSExtraction(gpio,&pins)) return; // Don't do anything if gpio input is invalid
    while(extractNextPINCMFromPINS(&pins)){
        IOMUX->SECCFG.PINCM[pincm_extracted] |= 1<<25; // set HiZ bit
    }
}

void GPIO_setPushPull(GPIO_Regs* gpio,uint32_t pins){
    if(setupPINCMFromPINSExtraction(gpio,&pins)) return; // Don't do anything if gpio input is invalid
    while(extractNextPINCMFromPINS(&pins)){
        IOMUX->SECCFG.PINCM[pincm_extracted] &= ~(1<<25); // clear HiZ bit
    }
}


void GPIO_setInterruptPolarity(GPIO_Regs* gpio,uint32_t pins,gpio_int_polarity_t polarity){
    // Loop through each pin
    uint8_t pin=0;
    uint32_t pinmask = 0x00000001;
    while(pins){
        if(pins & pinmask){
            pins &= ~pinmask;
            if(pin < 16){
                DL_GPIO_setLowerPinsPolarity(gpio,polarity << (2*pin));
            }else{
                DL_GPIO_setUpperPinsPolarity(gpio,polarity << (2*(pin-16)));
            }
        }
        pinmask <<= 1;
        pin++;
    }
}

uint32_t GPIO_getActiveInterrupt(GPIO_Regs* gpio){
    uint32_t pendint = DL_GPIO_getPendingInterrupt(gpio);
    if(pendint){
        return (0x00000001U << (pendint-1));
    }
    return 0;
}


// Renaming the GROUP1_IRQHandler since this class only uses GPIO interrupts from it
// Create the dummy handler function
void Default_Handler(void) __attribute__((weak));
extern void GPIO_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));

// Call the GPIO handler inside of the GROUP1 handler
// This would be better done modifying the actual GROUP1 handler within startup_mspm0g350x_ticlang.c
// but doing it this way avoids forgetting to update that file for other projects!
void GROUP1_IRQHandler(void){
    GPIO_IRQHandler();
}

// Same handler as in startup_mspm0g350x_ticlang.c but re-added here. Can't
// reference the original from the .c file due to file linking.
void Default_Handler(){
    while(1);
}
