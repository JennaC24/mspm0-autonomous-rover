
/*
 * engr2350_msp432.c
 * Author: Kyle Wilt, RPI
 * Origin Date: 2025-06-05
 * Last Modified: 2025-10-28
 * Version: 0.91
 *
 */

#include"engr2350_mspm0.h"

void initPower();
void initCLKs();
void initUART();


void sysInit(){
    initPower();
    //initCLKs();
    initUART();
}

void initPower(){
    GPIO_enablePower(GPIOA);
    GPIO_enablePower(GPIOB);
    DL_UART_enablePower(UART0);
    // ... power on anything else the class might use ...
}

void initUART(){
    GPIO_initPeripheralFunction(GPIOA,DL_GPIO_PIN_10,GPIO_PA10_PF_UART0_TX);
    GPIO_initPeripheralFunction(GPIOA,DL_GPIO_PIN_11,GPIO_PA11_PF_UART0_RX);

    DL_UART_ClockConfig uartclkcfg;
    uartclkcfg.clockSel = DL_UART_CLOCK_BUSCLK;
    uartclkcfg.divideRatio = DL_UART_CLOCK_DIVIDE_RATIO_1;
    DL_UART_setClockConfig(UART0,&uartclkcfg);
    DL_UART_Config uartcfg;
    uartcfg.mode = DL_UART_MODE_NORMAL;
    uartcfg.direction = DL_UART_DIRECTION_TX_RX;
    uartcfg.flowControl = DL_UART_FLOW_CONTROL_NONE;
    uartcfg.parity = DL_UART_PARITY_NONE;
    uartcfg.wordLength = DL_UART_WORD_LENGTH_8_BITS;
    uartcfg.stopBits = DL_UART_STOP_BITS_ONE;
    DL_UART_init(UART0,&uartcfg);
    DL_UART_configBaudRate(UART0,32000000,115200);
    DL_UART_enable(UART0);

    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
}

// Functions needed for printf, putchar, getchar, and scanf to work
void write(int file,char *ptr,int len){
    int i;
    for(i = 0; i < len; i++){
        DL_UART_transmitDataBlocking(UART0, ptr[i]);
    }
}

int read(int file,char *ptr,int len){
    int i;
    for(i = 0; i < len; i++){
        ptr[i] = DL_UART_receiveDataBlocking(UART0);
        if(ptr[i] == '\n') return i+1;
    }
    return i;
}

int32_t getchar_nw(){
    // Implementation of a non-blocking getchar()
    if(DL_UART_isRXFIFOEmpty(UART0)){
        return -1;
    }
    return DL_UART_receiveData(UART0);
}

uint8_t nextF0Channel = 1;
uint32_t getNextF0_Channel(){
    if(nextF0Channel == 16) return 0;
    return nextF0Channel++;
}
