
/*
 * engr2350_timers.c
 * Author: Kyle Wilt, RPI
 * Origin Date: 2025-08-06
 * Last Modified: 2025-09-25
 * Version: 0.99.2
 *
 */

#include"engr2350_timers.h"


void Timers_initTimer(GPTIMER_Regs *timer,Timers_TimerConfig *config){
    DL_Timer_enablePower(timer);
    // timer->PDBGCTL = 0; // when debugging, halt whole peripheral
    DL_Timer_setClockConfig(timer,
                &(DL_Timer_ClockConfig) {
                    (DL_TIMER_CLOCK)config->clksrc,
                    (DL_TIMER_CLOCK_DIVIDE)config->clkdivratio,
                    config->clkprescale});
    DL_Timer_initTimerMode(timer,
                &(DL_Timer_TimerConfig) {
                    .timerMode=(DL_TIMER_TIMER_MODE)config->mode,
                    .period=config->period,
                    .startTimer=DL_TIMER_STOP,
                    .genIntermInt=DL_TIMER_INTERM_INT_DISABLED,
                    .counterVal=0});
}

void Timers_startTimer(GPTIMER_Regs *timer){
    DL_Timer_startCounter(timer);
}

void Timers_stopTimer(GPTIMER_Regs *timer){
    DL_Timer_stopCounter(timer);
}

void Timers_clearCounter(GPTIMER_Regs *timer){
    timer->COUNTERREGS.CTR = 0;
}

uint16_t Timers_getCounter(GPTIMER_Regs *timer){
    return timer->COUNTERREGS.CTR;
}

void Timers_setPeriod(GPTIMER_Regs *timer,uint16_t period){
    timer->COUNTERREGS.LOAD = period;
}

void Timers_initCompare(GPTIMER_Regs *timer,Timers_CompareConfig *cmpCfg){
    volatile uint32_t * reg_cc = &timer->COUNTERREGS.CC_01[0];
    volatile uint32_t * reg_ccctl = &timer->COUNTERREGS.CCCTL_01[0];
    volatile uint32_t * reg_octl = &timer->COUNTERREGS.OCTL_01[0];
    volatile uint32_t * reg_ccact = &timer->COUNTERREGS.CCACT_01[0];



    uint32_t ccctl_value = GPTIMER_CCCTL_01_COC_COMPARE;
    uint32_t ccctl_mask = GPTIMER_CCCTL_01_COC_MASK;

    uint32_t octl_value = ((cmpCfg->invertOutput!=0)<<GPTIMER_OCTL_01_CCPOINV_OFS) 
                            | GPTIMER_OCTL_01_CCPO_FUNCVAL;
    uint32_t octl_mask = GPTIMER_OCTL_01_CCPOINV_MASK | GPTIMER_OCTL_01_CCPO_MASK;

    uint32_t ccact_mask = GPTIMER_CCACT_01_CUACT_MASK
                            | GPTIMER_CCACT_01_CDACT_MASK
                            | GPTIMER_CCACT_01_LACT_MASK
                            | GPTIMER_CCACT_01_ZACT_MASK;

    uint32_t ccrs = cmpCfg->ccrn & 0x2F; // Don't allow CCRs > 5 (G3507 has non > 3)
    timer->COMMONREGS.CCPD |= ccrs; // Sets CCPs associated with CCRs to output
    while(ccrs){
        if(ccrs & 0x01){
            DL_Common_updateReg(reg_ccctl,ccctl_value,ccctl_mask);
            DL_Common_updateReg(reg_octl,octl_value,octl_mask);
            DL_Common_updateReg(reg_ccact,cmpCfg->action,ccact_mask);
            *reg_cc = cmpCfg->value; // weirdly, this needs to be last for CC_0 *only* (doesn't set if first)
        }
        reg_cc++;
        reg_ccctl++;
        reg_octl++;
        reg_ccact++;
        ccrs >>= 1;
    }
}

void Timers_initCapture(GPTIMER_Regs *timer,Timers_CaptureConfig *capCfg){
    volatile uint32_t * reg_ccctl = &timer->COUNTERREGS.CCCTL_01[0];
    volatile uint32_t * reg_ifctl = &timer->COUNTERREGS.IFCTL_01[0];

    uint32_t ccctl_value = GPTIMER_CCCTL_01_COC_CAPTURE | capCfg->edge;
    uint32_t ccctl_mask = GPTIMER_CCCTL_01_COC_MASK | GPTIMER_CCCTL_01_CCOND_MASK;

    uint32_t ifctl_value = ((capCfg->invertInput!=0)<<GPTIMER_IFCTL_01_INV_OFS)
                            | capCfg->inputSel
                            | GPTIMER_IFCTL_01_FE_DISABLED;
    uint32_t ifctl_mask = GPTIMER_IFCTL_01_FE_MASK 
                            | GPTIMER_IFCTL_01_INV_MASK 
                            | GPTIMER_IFCTL_01_ISEL_MASK;

    uint32_t ccrs = capCfg->ccrn & 0x2F; // Don't allow CCRs > 5 (G3507 has non > 3)
    timer->COMMONREGS.CCPD &= ~ccrs; // Sets CCPs associated with CCRs to input
    while(ccrs){
        if((ccrs & 0x01)){
            DL_Common_updateReg(reg_ccctl,ccctl_value,ccctl_mask);
            DL_Common_updateReg(reg_ifctl,ifctl_value,ifctl_mask);
        }
        reg_ccctl++;
        reg_ifctl++;
        ccrs >>= 1;
    }
}

uint16_t Timers_getCCRValue(GPTIMER_Regs *timer,uint8_t ccrn){
    uint32_t ccr = ccrn & 0x2F; // Don't allow CCRs > 5 (G3507 has non > 3)
    if(!ccr) return 0;
    volatile uint32_t * reg_cc = &timer->COUNTERREGS.CC_01[0];
    while(!(ccr & 0x01)){ // Find the correct register
        reg_cc++;
        ccr>>=1;
    }
    return (*reg_cc) & 0xFFFF;
}

void Timers_setCCRValue(GPTIMER_Regs *timer,uint8_t ccrn,uint16_t value){
    uint32_t ccrs = ccrn & 0x2F; // Don't allow CCRs > 5 (G3507 has non > 3)
    if(!ccrs) return;
    volatile uint32_t * reg_cc = &timer->COUNTERREGS.CC_01[0];
    while(ccrs){
        if(ccrs & 0x01){
            *reg_cc = value;
        }
        reg_cc++;
        ccrs >>= 1;
    }
}

void Timers_enableInterrupt(GPTIMER_Regs *timer,uint32_t interruptMask){
    timer->CPU_INT.IMASK |= interruptMask;
}

void Timers_disableInterrupt(GPTIMER_Regs *timer,uint32_t interruptMask){
    timer->CPU_INT.IMASK &= ~interruptMask;
}

uint32_t Timers_getActiveInterrupt(GPTIMER_Regs *timer){
    uint8_t iidx = timer->CPU_INT.IIDX;
    if(iidx==0) return 0;
    return (0x00000001 << (iidx-1));
}

uint32_t Timers_getPendingInterrupts(GPTIMER_Regs *timer){
    return timer->CPU_INT.MIS;
}

uint32_t Timers_getAllPendingInterrupts(GPTIMER_Regs *timer){
    return timer->CPU_INT.RIS;
}

void Timers_clearInterrupt(GPTIMER_Regs *timer,uint32_t interruptMask){
    timer->CPU_INT.ICLR = interruptMask;
}
