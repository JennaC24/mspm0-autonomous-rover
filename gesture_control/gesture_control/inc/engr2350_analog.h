/*
 * engr2350_analog.h
 * Author: Kyle Wilt, RPI
 * Origin Date: 2025-10-01
 * Last Modified: 2025-11-02
 * Version: 0.99.f1
 *
 * Note: For simplicity, the ADC clock is automatically configured
 * to use SYSOSC/4 when calling ADC_initADC().
 * The ADC is also set to always use AUTO sampling mode
 */

#ifndef ENGR2350_ANALOG_H_
#define ENGR2350_ANALOG_H_

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>

// *****************************************************************
// Voltage Reference Generator
// *****************************************************************

typedef enum {
   VREF_V_1V4,
   VREF_V_2V5,
   VREF_V_OFF
} VREF_V;

void VREF_setReference( VREF_Regs *vref , VREF_V output );


// *****************************************************************
// ADC12
// *****************************************************************

typedef ADC12_Regs ADC_Regs;

typedef enum {
   ADC_RESOLUTION_8BIT = DL_ADC12_SAMP_CONV_RES_8_BIT,
   ADC_RESOLUTION_10BIT = DL_ADC12_SAMP_CONV_RES_10_BIT,
   ADC_RESOLUTION_12BIT = DL_ADC12_SAMP_CONV_RES_12_BIT,
} ADC_RESOLUTION;

typedef enum {
   ADC_SEQ_SINGLE,
   ADC_SEQ_SEQUENCE
} ADC_SEQ;

typedef enum {
   ADC_REPEAT_ENABLED = DL_ADC12_REPEAT_MODE_ENABLED,
   ADC_REPEAT_DISABLED = DL_ADC12_REPEAT_MODE_DISABLED
} ADC_REPEAT;

typedef enum {
   ADC_MEM_INDEX_0 = DL_ADC12_MEM_IDX_0,
   ADC_MEM_INDEX_1 = DL_ADC12_MEM_IDX_1,
   ADC_MEM_INDEX_2 = DL_ADC12_MEM_IDX_2,
   ADC_MEM_INDEX_3 = DL_ADC12_MEM_IDX_3,
   ADC_MEM_INDEX_4 = DL_ADC12_MEM_IDX_4,
   ADC_MEM_INDEX_5 = DL_ADC12_MEM_IDX_5,
   ADC_MEM_INDEX_6 = DL_ADC12_MEM_IDX_6,
   ADC_MEM_INDEX_7 = DL_ADC12_MEM_IDX_7,
   ADC_MEM_INDEX_8 = DL_ADC12_MEM_IDX_8,
   ADC_MEM_INDEX_9 = DL_ADC12_MEM_IDX_9,
   ADC_MEM_INDEX_10 = DL_ADC12_MEM_IDX_10,
   ADC_MEM_INDEX_11 = DL_ADC12_MEM_IDX_11,
} ADC_MEM_INDEX;

typedef struct {
    ADC_RESOLUTION res;
    ADC_REPEAT repeat;
    ADC_SEQ sequence;
    uint8_t trigsrc;
    ADC_MEM_INDEX memStart;
    ADC_MEM_INDEX memEnd;
} ADC_Config;

void ADC_initADC(ADC_Regs *adc, ADC_Config *config);

typedef enum {
   ADC_VREF_VDD = DL_ADC12_REFERENCE_VOLTAGE_VDDA,
   ADC_VREF_EXT = DL_ADC12_REFERENCE_VOLTAGE_EXTREF,
   ADC_VREF_INT = DL_ADC12_REFERENCE_VOLTAGE_INTREF,
} ADC_VREF;

typedef enum {
   ADC_TRIGMODE_AUTO = DL_ADC12_TRIGGER_MODE_AUTO_NEXT,
   ADC_TRIGMODE_TRIG = DL_ADC12_TRIGGER_MODE_TRIGGER_NEXT,
} ADC_TRIGMODE;

typedef struct {
   uint32_t channel;
   ADC_MEM_INDEX mem;
   ADC_VREF vref;
   ADC_TRIGMODE trigMode;
} ADC_ChanConfig;

void ADC_initChannel(ADC_Regs *adc, ADC_ChanConfig *chanfig);

#define ADC_INTSRC_OVERFLOW         DL_ADC12_INTERRUPT_OVERFLOW
#define ADC_INTSRC_TRIG_OVF         DL_ADC12_INTERRUPT_TRIG_OVF
#define ADC_INTSRC_WINDOW_COMP_HIGH DL_ADC12_INTERRUPT_WINDOW_COMP_HIGH
#define ADC_INTSRC_WINDOW_COMP_LOW  DL_ADC12_INTERRUPT_WINDOW_COMP_LOW
#define ADC_INTSRC_WINDOW_COMP_IN   DL_ADC12_INTERRUPT_INIFG
#define ADC_INTSRC_DMA_DONE         DL_ADC12_INTERRUPT_DMA_DONE
#define ADC_INTSRC_UNDERFLOW        DL_ADC12_INTERRUPT_UNDERFLOW
#define ADC_INTSRC_MEM0             DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED
#define ADC_INTSRC_MEM1             DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED
#define ADC_INTSRC_MEM2             DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED
#define ADC_INTSRC_MEM3             DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED
#define ADC_INTSRC_MEM4             DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED
#define ADC_INTSRC_MEM5             DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED
#define ADC_INTSRC_MEM6             DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED
#define ADC_INTSRC_MEM7             DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED
#define ADC_INTSRC_MEM8             DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED
#define ADC_INTSRC_MEM9             DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED
#define ADC_INTSRC_MEM1             DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED
#define ADC_INTSRC_MEM11            DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED

void ADC_startConversion(ADC_Regs *adc);
static inline void ADC_stopConversion(ADC_Regs *adc){DL_ADC12_startConversion(adc);}
static inline void ADC_enableConversions(ADC_Regs *adc){DL_ADC12_enableConversions(adc);}
static inline void ADC_disableConversions(ADC_Regs *adc){DL_ADC12_disableConversions(adc);}
static inline uint32_t ADC_getStatus(ADC_Regs *adc){return DL_ADC12_getStatus(adc);}
static inline uint16_t ADC_getResult(ADC_Regs *adc,ADC_MEM_INDEX mem){return DL_ADC12_getMemResult(adc,(DL_ADC12_MEM_IDX)mem);}

void ADC_enableInterrupt(ADC_Regs *adc,uint32_t interruptMask);
void ADC_disableInterrupt(ADC_Regs *adc,uint32_t interruptMask);
uint32_t ADC_getActiveInterrupt(ADC_Regs *adc);
uint32_t ADC_getPendingInterrupts(ADC_Regs *adc);
uint32_t ADC_getAllPendingInterrupts(ADC_Regs *adc);
void ADC_clearInterrupt(ADC_Regs *adc,uint32_t interruptMask);





#endif