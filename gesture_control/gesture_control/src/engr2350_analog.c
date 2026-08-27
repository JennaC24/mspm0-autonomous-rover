/*
 * engr2350_analog.h
 * Author: Kyle Wilt, RPI
 * Origin Date: 2025-10-01
 * Last Modified: 2025-11-02
 * Version: 0.99.f1
 *
 */

 #include "engr2350_analog.h"

// *****************************************************************
// Voltage Reference Generator
// *****************************************************************

void VREF_setReference( VREF_Regs *vref , VREF_V output ){
    vref->GPRCM.PWREN = VREF_PWREN_ENABLE_ENABLE | VREF_PWREN_KEY_UNLOCK_W; // Enable power to module
    uint32_t v_bits = 0;
    if(output == VREF_V_OFF){
        vref->CTL0 &= VREF_CTL0_ENABLE_DISABLE;

    }else if(output == VREF_V_1V4){
        v_bits = VREF_CTL0_BUFCONFIG_OUTPUT1P4V;
    }else if(output == VREF_V_2V5){
        v_bits = VREF_CTL0_BUFCONFIG_OUTPUT2P5V;
    }
    vref->CTL0 = v_bits | VREF_CTL0_ENABLE_ENABLE;
}

// *****************************************************************
// ADC12
// *****************************************************************

void ADC_initADC(ADC_Regs *adc, ADC_Config *config){
    DL_ADC12_enablePower(adc);
    DL_ADC12_disableConversions(adc);
    DL_ADC12_setClockConfig(adc,
                &(DL_ADC12_ClockConfig) {
                    .clockSel=DL_ADC12_CLOCK_ULPCLK,
                    .freqRange=DL_ADC12_CLOCK_FREQ_RANGE_24_TO_32,
                    .divideRatio=DL_ADC12_CLOCK_DIVIDE_4
                });
    uint32_t trigSoftware = true;
    if(config->trigsrc & ADC12_FSUB_0_CHANID_MAXIMUM){
        trigSoftware= false;
        DL_ADC12_setSubscriberChanID(adc,config->trigsrc);
    }
    if(config->sequence == ADC_SEQ_SEQUENCE){
        DL_ADC12_initSeqSample(adc,
                config->repeat,
                DL_ADC12_SAMPLING_SOURCE_AUTO,
                !trigSoftware,
                config->memStart<<16,
                config->memEnd<<24,
                config->res,
                DL_ADC12_SAMP_CONV_DATA_FORMAT_UNSIGNED
                );

    }else{
        DL_ADC12_initSingleSample(adc,
                config->repeat,
                DL_ADC12_SAMPLING_SOURCE_AUTO,
                !trigSoftware,
                config->res,
                DL_ADC12_SAMP_CONV_DATA_FORMAT_UNSIGNED
                );
        DL_ADC12_setStartAddress(adc,config->memStart<<16);
    }
    DL_ADC12_setSampleTime0(adc,20);
    // DL_ADC12_enableConversions(adc);
}

void ADC_initChannel(ADC_Regs *adc, ADC_ChanConfig *chanfig){
    DL_ADC12_configConversionMem(adc,
                (DL_ADC12_MEM_IDX)chanfig->mem,
                chanfig->channel,
                chanfig->vref,
                // 0s replace constants below as development compile had issues...
                0,//DL_ADC12_SAMPLE_TIMER_SOURCE_SCOMP0,
                0,//DL_ADC12_AVERAGING_MODE_DISABLED,
                0,//DL_ADC12_BURN_OUT_SOURCE_DISABLED,
                chanfig->trigMode,
                0//DL_ADC12_WINDOWS_COMP_MODE_DISABLED
                );
}

void ADC_startConversion(ADC_Regs *adc){
    ADC_enableConversions(adc); // Just in case not happened yet
    DL_ADC12_startConversion(adc);
}

void ADC_enableInterrupt(ADC_Regs *adc,uint32_t interruptMask){
    adc->ULLMEM.CPU_INT.IMASK |= interruptMask;

}
void ADC_disableInterrupt(ADC_Regs *adc,uint32_t interruptMask){
    adc->ULLMEM.CPU_INT.IMASK &= ~interruptMask;
}

uint32_t ADC_getActiveInterrupt(ADC_Regs *adc){
    uint8_t iidx = adc->ULLMEM.CPU_INT.IIDX;
    if(iidx==0) return 0;
    return (0x00000001 << (iidx-1));
}

uint32_t ADC_getPendingInterrupts(ADC_Regs *adc){
    return adc->ULLMEM.CPU_INT.MIS;
}

uint32_t ADC_getAllPendingInterrupts(ADC_Regs *adc){
    return adc->ULLMEM.CPU_INT.RIS;
}

void ADC_clearInterrupt(ADC_Regs *adc,uint32_t interruptMask){
    adc->ULLMEM.CPU_INT.ICLR = interruptMask;
}