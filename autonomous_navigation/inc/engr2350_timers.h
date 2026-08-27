
/*
 * engr2350_timers.h
 * Author: Kyle Wilt, RPI
 * Origin Date: 2025-08-05
 * Last Modified: 2025-09-23
 * Version: 0.99
 *
 */

#ifndef ENGR2350_TIMERS_H_
#define ENGR2350_TIMERS_H_

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>

typedef enum {
    TIMER_CLOCK_BUSCLK = GPTIMER_CLKSEL_BUSCLK_SEL_ENABLE,
    TIMER_CLOCK_2X_BUSCLK = GPTIMER_CLKSEL_BUS2XCLK_SEL_ENABLE,
    TIMER_CLOCK_MFCLK = GPTIMER_CLKSEL_MFCLK_SEL_ENABLE,
    TIMER_CLOCK_LFCLK = GPTIMER_CLKSEL_LFCLK_SEL_ENABLE,
    TIMER_CLOCK_DISABLE = GPTIMER_CLKSEL_LFCLK_SEL_DISABLE,
} TIMER_CLOCK_SRC; // Same as DL_TIMER_CLOCK

typedef enum {
    TIMER_CLOCK_DIVIDE_1 = GPTIMER_CLKDIV_RATIO_DIV_BY_1,
    TIMER_CLOCK_DIVIDE_2 = GPTIMER_CLKDIV_RATIO_DIV_BY_2,
    TIMER_CLOCK_DIVIDE_3 = GPTIMER_CLKDIV_RATIO_DIV_BY_3,
    TIMER_CLOCK_DIVIDE_4 = GPTIMER_CLKDIV_RATIO_DIV_BY_4,
    TIMER_CLOCK_DIVIDE_5 = GPTIMER_CLKDIV_RATIO_DIV_BY_5,
    TIMER_CLOCK_DIVIDE_6 = GPTIMER_CLKDIV_RATIO_DIV_BY_6,
    TIMER_CLOCK_DIVIDE_7 = GPTIMER_CLKDIV_RATIO_DIV_BY_7,
    TIMER_CLOCK_DIVIDE_8 = GPTIMER_CLKDIV_RATIO_DIV_BY_8,
} TIMER_CLOCK_DIV;

typedef enum {
    TIMER_MODE_ONE_SHOT_DOWN =
        (GPTIMER_CTRCTL_CM_DOWN | GPTIMER_CTRCTL_REPEAT_REPEAT_0),
    TIMER_MODE_PERIODIC_DOWN =
        (GPTIMER_CTRCTL_CM_DOWN | GPTIMER_CTRCTL_REPEAT_REPEAT_1),
    TIMER_MODE_ONE_SHOT_UP =
        (GPTIMER_CTRCTL_CM_UP | GPTIMER_CTRCTL_REPEAT_REPEAT_0),
    TIMER_MODE_PERIODIC_UP =
        (GPTIMER_CTRCTL_CM_UP | GPTIMER_CTRCTL_REPEAT_REPEAT_1),
    TIMER_MODE_ONE_SHOT_UP_DOWN =
        (GPTIMER_CTRCTL_CM_UP_DOWN | GPTIMER_CTRCTL_REPEAT_REPEAT_0),
    TIMER_MODE_PERIODIC_UP_DOWN =
        (GPTIMER_CTRCTL_CM_UP_DOWN | GPTIMER_CTRCTL_REPEAT_REPEAT_1),
} TIMER_MODE;

typedef struct {
    TIMER_MODE mode;
    TIMER_CLOCK_SRC clksrc;
    TIMER_CLOCK_DIV clkdivratio;
    uint8_t clkprescale;
    uint32_t period;
} Timers_TimerConfig;

void Timers_initTimer(GPTIMER_Regs *timer,Timers_TimerConfig *config);
void Timers_startTimer(GPTIMER_Regs *timer);
void Timers_stopTimer(GPTIMER_Regs *timer);
void Timers_clearCounter(GPTIMER_Regs *timer);
uint16_t Timers_getCounter(GPTIMER_Regs *timer);
void Timers_setPeriod(GPTIMER_Regs *timer,uint16_t period);

#define TIMER_CCR_CCR0              (0x01)
#define TIMER_CCR_CCR1              (0x02)
#define TIMER_CCR_CCR2              (0x04)
#define TIMER_CCR_CCR3              (0x08)
#define TIMER_CCR_CCR4              (0x10)
#define TIMER_CCR_CCR5              (0x20)

// Actions available for events on a CCR.
#define TIMER_CCR_ACTION_UPCOMPARE_NONE      (0x0000)
#define TIMER_CCR_ACTION_UPCOMPARE_SET       (0x0200)
#define TIMER_CCR_ACTION_UPCOMPARE_CLEAR     (0x0400)
#define TIMER_CCR_ACTION_UPCOMPARE_TOGGLE    (0x0600)
#define TIMER_CCR_ACTION_DOWNCOMPARE_NONE    (0x0000)
#define TIMER_CCR_ACTION_DOWNCOMPARE_SET     (0x0040)
#define TIMER_CCR_ACTION_DOWNCOMPARE_CLEAR   (0x0080)
#define TIMER_CCR_ACTION_DOWNCOMPARE_TOGGLE  (0x00C0)
#define TIMER_CCR_ACTION_LOAD_NONE           (0x0000)
#define TIMER_CCR_ACTION_LOAD_SET            (0x0008)
#define TIMER_CCR_ACTION_LOAD_CLEAR          (0x0010)
#define TIMER_CCR_ACTION_LOAD_TOGGLE         (0x0018)
#define TIMER_CCR_ACTION_ZERO_NONE           (0x0000)
#define TIMER_CCR_ACTION_ZERO_SET            (0x0001)
#define TIMER_CCR_ACTION_ZERO_CLEAR          (0x0002)
#define TIMER_CCR_ACTION_ZERO_TOGGLE         (0x0003)

typedef struct {
    uint8_t ccrn; // CCR register(s) to use (bitwise OR)
    uint16_t action; // Action(s) to perform on a CCP when events occur
    uint16_t value; // Initial value of CCR register(s)
    uint8_t invertOutput; // true (1) or false (0)
}Timers_CompareConfig;

void Timers_initCompare(GPTIMER_Regs *timer,Timers_CompareConfig *cmpCfg);

#define TIMER_CCR_EDGE_NONE         (0x0000)
#define TIMER_CCR_EDGE_RISE         (0x0001)
#define TIMER_CCR_EDGE_FALL         (0x0002)
#define TIMER_CCR_EDGE_BOTH         (0x0004)

#define TIMER_CCR_INPUT_CCPn        (0x0000)
#define TIMER_CCR_INPUT_CCPu        (0x0001)
#define TIMER_CCR_INPUT_CCP0        (0x0002)
#define TIMER_CCR_INPUT_TRIG        (0x0003)
#define TIMER_CCR_INPUT_XOR         (0x0004)
#define TIMER_CCR_INPUT_FSUB0       (0x0005)
#define TIMER_CCR_INPUT_FSUB1       (0x0006)
#define TIMER_CCR_INPUT_COMP0       (0x0007)
#define TIMER_CCR_INPUT_COMP1       (0x0008)
#define TIMER_CCR_INPUT_COMP2       (0x0009)

typedef struct {
    uint8_t ccrn; // CCR register(s) to use (bitwise OR)
    uint8_t inputSel; // Input signal selection
    uint8_t edge; // Rising, Falling or Both edges to trigger on
    uint8_t invertInput; // true (1) or false (0)
}Timers_CaptureConfig;

void Timers_initCapture(GPTIMER_Regs *timer,Timers_CaptureConfig *capCfg);

uint16_t Timers_getCCRValue(GPTIMER_Regs *timer,uint8_t ccrn);
void Timers_setCCRValue(GPTIMER_Regs *timer,uint8_t ccrn,uint16_t value);


#define TIMER_INTSRC_REPC           (GPTIMER_CPU_INT_IMASK_REPC_SET)
#define TIMER_INTSRC_FAULT          (GPTIMER_CPU_INT_IMASK_F_SET)
#define TIMER_INTSRC_ZERO           (GPTIMER_CPU_INT_IMASK_Z_SET)
#define TIMER_INTSRC_LOAD           (GPTIMER_CPU_INT_IMASK_L_SET)
#define TIMER_INTSRC_CCR0_DN         (GPTIMER_CPU_INT_IMASK_CCD0_SET)
#define TIMER_INTSRC_CCR1_DN         (GPTIMER_CPU_INT_IMASK_CCD1_SET)
#define TIMER_INTSRC_CCR2_DN         (GPTIMER_CPU_INT_IMASK_CCD2_SET)
#define TIMER_INTSRC_CCR3_DN         (GPTIMER_CPU_INT_IMASK_CCD3_SET)
#define TIMER_INTSRC_CCR4_DN         (GPTIMER_CPU_INT_IMASK_CCD4_SET)
#define TIMER_INTSRC_CCR5_DN         (GPTIMER_CPU_INT_IMASK_CCD5_SET)
#define TIMER_INTSRC_CCR0_UP         (GPTIMER_CPU_INT_IMASK_CCU0_SET)
#define TIMER_INTSRC_CCR1_UP         (GPTIMER_CPU_INT_IMASK_CCU1_SET)
#define TIMER_INTSRC_CCR2_UP         (GPTIMER_CPU_INT_IMASK_CCU2_SET)
#define TIMER_INTSRC_CCR3_UP         (GPTIMER_CPU_INT_IMASK_CCU3_SET)
#define TIMER_INTSRC_CCR4_UP         (GPTIMER_CPU_INT_IMASK_CCU4_SET)
#define TIMER_INTSRC_CCR5_UP         (GPTIMER_CPU_INT_IMASK_CCU5_SET)
#define TIMER_INTSRC_OVERFLOW       (GPTIMER_CPU_INT_IMASK_TOV_SET)
#define TIMER_INTSRC_DC             (GPTIMER_CPU_INT_IMASK_DC_SET)
#define TIMER_INTSRC_QEIERR         (GPTIMER_CPU_INT_IMASK_QEIERR_SET)

void Timers_enableInterrupt(GPTIMER_Regs *timer,uint32_t interruptMask);
void Timers_disableInterrupt(GPTIMER_Regs *timer,uint32_t interruptMask);
uint32_t Timers_getActiveInterrupt(GPTIMER_Regs *timer);
uint32_t Timers_getPendingInterrupts(GPTIMER_Regs *timer);
uint32_t Timers_getAllPendingInterrupts(GPTIMER_Regs *timer);
void Timers_clearInterrupt(GPTIMER_Regs *timer,uint32_t interruptMask);

#endif
