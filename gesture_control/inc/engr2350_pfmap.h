
/*
 * engr2350_pfmap.h
 * Author: Kyle Wilt, RPI
 * Origin Date: 2025-06-11
 * Last Modified: 2025-10-21
 * Version: 0.93
 *
 */

// These defines are copied and renamed from mspm0g350x.h

/* IOMUX_PINCM1[PF] Bits */
#define GPIO_PA0_PF_UNCONNECTED                   ((uint32_t)0X00000000)
#define GPIO_PA0_PF_DIO                           ((uint32_t)0X00000001)
#define GPIO_PA0_PF_UART0_TX                      ((uint32_t)0X00000002)
#define GPIO_PA0_PF_I2C0_SDA                      ((uint32_t)0X00000003)
#define GPIO_PA0_PF_TIMA0_C0                      ((uint32_t)0X00000004)
#define GPIO_PA0_PF_TIMA_FAULT1                   ((uint32_t)0X00000005)
#define GPIO_PA0_PF_TIMG8_C1                      ((uint32_t)0X00000006)
#define GPIO_PA0_PF_SYSCTL_FCC_IN                 ((uint32_t)0X00000007)

/* IOMUX_PINCM2[PF] Bits */
#define GPIO_PA1_PF_UNCONNECTED                   ((uint32_t)0X00000000)
#define GPIO_PA1_PF_DIO                           ((uint32_t)0X00000001)
#define GPIO_PA1_PF_UART0_RX                      ((uint32_t)0X00000002)
#define GPIO_PA1_PF_I2C0_SCL                      ((uint32_t)0X00000003)
#define GPIO_PA1_PF_TIMA0_C1                      ((uint32_t)0X00000004)
#define GPIO_PA1_PF_TIMA_FAULT2                   ((uint32_t)0X00000005)
#define GPIO_PA1_PF_TIMG8_IDX                     ((uint32_t)0X00000006)
#define GPIO_PA1_PF_TIMG8_C0                      ((uint32_t)0X00000007)

/* IOMUX_PINCM3[PF] Bits */
#define GPIO_PA28_PF_UNCONNECTED                   ((uint32_t)0X00000000)
#define GPIO_PA28_PF_DIO                           ((uint32_t)0X00000001)
#define GPIO_PA28_PF_UART0_TX                      ((uint32_t)0X00000002)
#define GPIO_PA28_PF_I2C0_SDA                      ((uint32_t)0X00000003)
#define GPIO_PA28_PF_TIMA0_C3                      ((uint32_t)0X00000004)
#define GPIO_PA28_PF_TIMA_FAULT0                   ((uint32_t)0X00000005)
#define GPIO_PA28_PF_TIMG7_C0                      ((uint32_t)0X00000006)
#define GPIO_PA28_PF_TIMA1_C0                      ((uint32_t)0X00000007)

/* IOMUX_PINCM4[PF] Bits */
#define GPIO_PA29_PF_UNCONNECTED                   ((uint32_t)0X00000000)
#define GPIO_PA29_PF_DIO                           ((uint32_t)0X00000001)
#define GPIO_PA29_PF_I2C1_SCL                      ((uint32_t)0X00000002)
#define GPIO_PA29_PF_UART2_RTS                     ((uint32_t)0X00000003)
#define GPIO_PA29_PF_TIMG8_C0                      ((uint32_t)0X00000004)
#define GPIO_PA29_PF_TIMG6_C0                      ((uint32_t)0X00000005)

/* IOMUX_PINCM5[PF] Bits */
#define GPIO_PA30_PF_UNCONNECTED                   ((uint32_t)0X00000000)
#define GPIO_PA30_PF_DIO                           ((uint32_t)0X00000001)
#define GPIO_PA30_PF_I2C1_SDA                      ((uint32_t)0X00000002)
#define GPIO_PA30_PF_UART2_CTS                     ((uint32_t)0X00000003)
#define GPIO_PA30_PF_TIMG8_C1                      ((uint32_t)0X00000004)
#define GPIO_PA30_PF_TIMG6_C1                      ((uint32_t)0X00000005)

/* IOMUX_PINCM6[PF] Bits */
#define GPIO_PA31_PF_UNCONNECTED                   ((uint32_t)0X00000000)
#define GPIO_PA31_PF_DIO                           ((uint32_t)0X00000001)
#define GPIO_PA31_PF_UART0_RX                      ((uint32_t)0X00000002)
#define GPIO_PA31_PF_I2C0_SCL                      ((uint32_t)0X00000003)
#define GPIO_PA31_PF_TIMA0_C3_CMPL                 ((uint32_t)0X00000004)
#define GPIO_PA31_PF_TIMG12_C1                     ((uint32_t)0X00000005)
#define GPIO_PA31_PF_SYSCTL_CLK_OUT                ((uint32_t)0X00000006)
#define GPIO_PA31_PF_TIMG7_C1                      ((uint32_t)0X00000007)
#define GPIO_PA31_PF_TIMA1_C1                      ((uint32_t)0X00000008)

/* IOMUX_PINCM7[PF] Bits */
#define GPIO_PA2_PF_UNCONNECTED                   ((uint32_t)0X00000000)
#define GPIO_PA2_PF_DIO                           ((uint32_t)0X00000001)
#define GPIO_PA2_PF_TIMG8_C1                      ((uint32_t)0X00000002)
#define GPIO_PA2_PF_SPI0_CS0                      ((uint32_t)0X00000003)
#define GPIO_PA2_PF_TIMG7_C1                      ((uint32_t)0X00000004)
#define GPIO_PA2_PF_SPI1_CS0                      ((uint32_t)0X00000005)

/* IOMUX_PINCM8[PF] Bits */
#define GPIO_PA3_PF_UNCONNECTED                   ((uint32_t)0X00000000)
#define GPIO_PA3_PF_DIO                           ((uint32_t)0X00000001)
#define GPIO_PA3_PF_TIMG8_C0                      ((uint32_t)0X00000002)
#define GPIO_PA3_PF_SPI0_CS1_POCI1                ((uint32_t)0X00000003)
#define GPIO_PA3_PF_UART2_CTS                     ((uint32_t)0X00000004)
#define GPIO_PA3_PF_TIMA0_C2                      ((uint32_t)0X00000005)
#define GPIO_PA3_PF_COMP1_OUT                     ((uint32_t)0X00000006)
#define GPIO_PA3_PF_TIMG7_C0                      ((uint32_t)0X00000007)
#define GPIO_PA3_PF_TIMA0_C1                      ((uint32_t)0X00000008)
#define GPIO_PA3_PF_I2C1_SDA                      ((uint32_t)0X00000009)

/* IOMUX_PINCM9[PF] Bits */
#define GPIO_PA4_PF_UNCONNECTED                   ((uint32_t)0X00000000)
#define GPIO_PA4_PF_DIO                           ((uint32_t)0X00000001)
#define GPIO_PA4_PF_TIMG8_C1                      ((uint32_t)0X00000002)
#define GPIO_PA4_PF_SPI0_POCI                     ((uint32_t)0X00000003)
#define GPIO_PA4_PF_UART2_RTS                     ((uint32_t)0X00000004)
#define GPIO_PA4_PF_TIMA0_C3                      ((uint32_t)0X00000005)
#define GPIO_PA4_PF_SYSCTL_LFCLKIN                ((uint32_t)0X00000006)
#define GPIO_PA4_PF_TIMG7_C1                      ((uint32_t)0X00000007)
#define GPIO_PA4_PF_TIMA0_C1_CMPL                 ((uint32_t)0X00000008)
#define GPIO_PA4_PF_I2C1_SCL                      ((uint32_t)0X00000009)

/* IOMUX_PINCM10[PF] Bits */
#define GPIO_PA5_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA5_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA5_PF_TIMG8_C0                     ((uint32_t)0X00000002)
#define GPIO_PA5_PF_SPI0_PICO                    ((uint32_t)0X00000003)
#define GPIO_PA5_PF_TIMA_FAULT1                  ((uint32_t)0X00000004)
#define GPIO_PA5_PF_TIMG0_C0                     ((uint32_t)0X00000005)
#define GPIO_PA5_PF_TIMG6_C0                     ((uint32_t)0X00000006)
#define GPIO_PA5_PF_SYSCTL_FCC_IN                ((uint32_t)0X00000007)

/* IOMUX_PINCM11[PF] Bits */
#define GPIO_PA6_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA6_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA6_PF_TIMG8_C1                     ((uint32_t)0X00000002)
#define GPIO_PA6_PF_SPI0_SCLK                    ((uint32_t)0X00000003)
#define GPIO_PA6_PF_TIMA_FAULT0                  ((uint32_t)0X00000004)
#define GPIO_PA6_PF_TIMG0_C1                     ((uint32_t)0X00000005)
#define GPIO_PA6_PF_SYSCTL_HFCLKIN               ((uint32_t)0X00000006)
#define GPIO_PA6_PF_TIMG6_C1                     ((uint32_t)0X00000007)
#define GPIO_PA6_PF_TIMA0_C2_CMPL                ((uint32_t)0X00000008)

/* IOMUX_PINCM12[PF] Bits */
#define GPIO_PB0_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB0_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB0_PF_UART0_TX                     ((uint32_t)0X00000002)
#define GPIO_PB0_PF_SPI1_CS2_POCI2               ((uint32_t)0X00000003)
#define GPIO_PB0_PF_TIMA1_C0                     ((uint32_t)0X00000004)
#define GPIO_PB0_PF_TIMA0_C2                     ((uint32_t)0X00000005)

/* IOMUX_PINCM13[PF] Bits */
#define GPIO_PB1_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB1_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB1_PF_UART0_RX                     ((uint32_t)0X00000002)
#define GPIO_PB1_PF_SPI1_CS3_CD_POCI3            ((uint32_t)0X00000003)
#define GPIO_PB1_PF_TIMA1_C1                     ((uint32_t)0X00000004)
#define GPIO_PB1_PF_TIMA0_C2_CMPL                ((uint32_t)0X00000005)

/* IOMUX_PINCM14[PF] Bits */
#define GPIO_PA7_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA7_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA7_PF_COMP0_OUT                    ((uint32_t)0X00000002)
#define GPIO_PA7_PF_SYSCTL_CLK_OUT               ((uint32_t)0X00000003)
#define GPIO_PA7_PF_TIMG8_C0                     ((uint32_t)0X00000004)
#define GPIO_PA7_PF_TIMA0_C2                     ((uint32_t)0X00000005)
#define GPIO_PA7_PF_TIMG8_IDX                    ((uint32_t)0X00000006)
#define GPIO_PA7_PF_TIMG7_C1                     ((uint32_t)0X00000007)
#define GPIO_PA7_PF_TIMA0_C1                     ((uint32_t)0X00000008)

/* IOMUX_PINCM15[PF] Bits */
#define GPIO_PB2_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB2_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB2_PF_UART3_TX                     ((uint32_t)0X00000002)
#define GPIO_PB2_PF_UART2_CTS                    ((uint32_t)0X00000003)
#define GPIO_PB2_PF_I2C1_SCL                     ((uint32_t)0X00000004)
#define GPIO_PB2_PF_TIMA0_C3                     ((uint32_t)0X00000005)
#define GPIO_PB2_PF_UART1_CTS                    ((uint32_t)0X00000006)
#define GPIO_PB2_PF_TIMG6_C0                     ((uint32_t)0X00000007)
#define GPIO_PB2_PF_TIMA1_C0                     ((uint32_t)0X00000008)

/* IOMUX_PINCM16[PF] Bits */
#define GPIO_PB3_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB3_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB3_PF_UART3_RX                     ((uint32_t)0X00000002)
#define GPIO_PB3_PF_UART2_RTS                    ((uint32_t)0X00000003)
#define GPIO_PB3_PF_I2C1_SDA                     ((uint32_t)0X00000004)
#define GPIO_PB3_PF_TIMA0_C3_CMPL                ((uint32_t)0X00000005)
#define GPIO_PB3_PF_UART1_RTS                    ((uint32_t)0X00000006)
#define GPIO_PB3_PF_TIMG6_C1                     ((uint32_t)0X00000007)
#define GPIO_PB3_PF_TIMA1_C1                     ((uint32_t)0X00000008)

/* IOMUX_PINCM17[PF] Bits */
#define GPIO_PB4_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB4_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB4_PF_UART1_TX                     ((uint32_t)0X00000002)
#define GPIO_PB4_PF_UART3_CTS                    ((uint32_t)0X00000003)
#define GPIO_PB4_PF_TIMA1_C0                     ((uint32_t)0X00000004)
#define GPIO_PB4_PF_TIMA0_C2                     ((uint32_t)0X00000005)
#define GPIO_PB4_PF_TIMA1_C0_CMPL                ((uint32_t)0X00000006)

/* IOMUX_PINCM18[PF] Bits */
#define GPIO_PB5_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB5_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB5_PF_UART1_RX                     ((uint32_t)0X00000002)
#define GPIO_PB5_PF_UART3_RTS                    ((uint32_t)0X00000003)
#define GPIO_PB5_PF_TIMA1_C1                     ((uint32_t)0X00000004)
#define GPIO_PB5_PF_TIMA0_C2_CMPL                ((uint32_t)0X00000005)
#define GPIO_PB5_PF_TIMA1_C1_CMPL                ((uint32_t)0X00000006)

/* IOMUX_PINCM19[PF] Bits */
#define GPIO_PA8_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA8_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA8_PF_UART1_TX                     ((uint32_t)0X00000002)
#define GPIO_PA8_PF_SPI0_CS0                     ((uint32_t)0X00000003)
#define GPIO_PA8_PF_UART0_RTS                    ((uint32_t)0X00000004)
#define GPIO_PA8_PF_TIMA0_C0                     ((uint32_t)0X00000005)
#define GPIO_PA8_PF_TIMA1_C0_CMPL                ((uint32_t)0X00000006)

/* IOMUX_PINCM20[PF] Bits */
#define GPIO_PA9_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA9_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA9_PF_UART1_RX                     ((uint32_t)0X00000002)
#define GPIO_PA9_PF_SPI0_PICO                    ((uint32_t)0X00000003)
#define GPIO_PA9_PF_UART0_CTS                    ((uint32_t)0X00000004)
#define GPIO_PA9_PF_TIMA0_C1                     ((uint32_t)0X00000005)
#define GPIO_PA9_PF_RTC_RTC_OUT                  ((uint32_t)0X00000006)
#define GPIO_PA9_PF_TIMA0_C0_CMPL                ((uint32_t)0X00000007)
#define GPIO_PA9_PF_TIMA1_C1_CMPL                ((uint32_t)0X00000008)
#define GPIO_PA9_PF_SYSCTL_CLK_OUT               ((uint32_t)0X00000009)

/* IOMUX_PINCM21[PF] Bits */
#define GPIO_PA10_PF_UNCONNECTED                 ((uint32_t)0X00000000)
#define GPIO_PA10_PF_DIO                         ((uint32_t)0X00000001)
#define GPIO_PA10_PF_UART0_TX                    ((uint32_t)0X00000002)
#define GPIO_PA10_PF_SPI0_POCI                   ((uint32_t)0X00000003)
#define GPIO_PA10_PF_I2C0_SDA                    ((uint32_t)0X00000004)
#define GPIO_PA10_PF_TIMA1_C0                    ((uint32_t)0X00000005)
#define GPIO_PA10_PF_TIMG12_C0                   ((uint32_t)0X00000006)
#define GPIO_PA10_PF_TIMA0_C2                    ((uint32_t)0X00000007)
#define GPIO_PA10_PF_I2C1_SDA                    ((uint32_t)0X00000008)
#define GPIO_PA10_PF_SYSCTL_CLK_OUT              ((uint32_t)0X00000009)

/* IOMUX_PINCM22[PF] Bits */
#define GPIO_PA11_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA11_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA11_PF_UART0_RX                     ((uint32_t)0X00000002)
#define GPIO_PA11_PF_SPI0_SCLK                    ((uint32_t)0X00000003)
#define GPIO_PA11_PF_I2C0_SCL                     ((uint32_t)0X00000004)
#define GPIO_PA11_PF_TIMA1_C1                     ((uint32_t)0X00000005)
#define GPIO_PA11_PF_COMP0_OUT                    ((uint32_t)0X00000006)
#define GPIO_PA11_PF_TIMA0_C2_CMPL                ((uint32_t)0X00000007)
#define GPIO_PA11_PF_I2C1_SCL                     ((uint32_t)0X00000008)

/* IOMUX_PINCM23[PF] Bits */
#define GPIO_PB6_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB6_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB6_PF_UART1_TX                     ((uint32_t)0X00000002)
#define GPIO_PB6_PF_SPI1_CS0                     ((uint32_t)0X00000003)
#define GPIO_PB6_PF_SPI0_CS1_POCI1               ((uint32_t)0X00000004)
#define GPIO_PB6_PF_TIMG8_C0                     ((uint32_t)0X00000005)
#define GPIO_PB6_PF_UART2_CTS                    ((uint32_t)0X00000006)
#define GPIO_PB6_PF_TIMG6_C0                     ((uint32_t)0X00000007)
#define GPIO_PB6_PF_TIMA1_C0_CMPL                ((uint32_t)0X00000008)

/* IOMUX_PINCM24[PF] Bits */
#define GPIO_PB7_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB7_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB7_PF_UART1_RX                     ((uint32_t)0X00000002)
#define GPIO_PB7_PF_SPI1_POCI                    ((uint32_t)0X00000003)
#define GPIO_PB7_PF_SPI0_CS2_POCI2               ((uint32_t)0X00000004)
#define GPIO_PB7_PF_TIMG8_C1                     ((uint32_t)0X00000005)
#define GPIO_PB7_PF_UART2_RTS                    ((uint32_t)0X00000006)
#define GPIO_PB7_PF_TIMG6_C1                     ((uint32_t)0X00000007)
#define GPIO_PB7_PF_TIMA1_C1_CMPL                ((uint32_t)0X00000008)

/* IOMUX_PINCM25[PF] Bits */
#define GPIO_PB8_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB8_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB8_PF_UART1_CTS                    ((uint32_t)0X00000002)
#define GPIO_PB8_PF_SPI1_PICO                    ((uint32_t)0X00000003)
#define GPIO_PB8_PF_TIMA0_C0                     ((uint32_t)0X00000004)
#define GPIO_PB8_PF_COMP1_OUT                    ((uint32_t)0X00000005)

/* IOMUX_PINCM26[PF] Bits */
#define GPIO_PB9_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB9_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB9_PF_UART1_RTS                    ((uint32_t)0X00000002)
#define GPIO_PB9_PF_SPI1_SCLK                    ((uint32_t)0X00000003)
#define GPIO_PB9_PF_TIMA0_C1                     ((uint32_t)0X00000004)
#define GPIO_PB9_PF_TIMA0_C0_CMPL                ((uint32_t)0X00000005)

/* IOMUX_PINCM27[PF] Bits */
#define GPIO_PB10_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB10_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB10_PF_TIMG0_C0                     ((uint32_t)0X00000002)
#define GPIO_PB10_PF_TIMG8_C0                     ((uint32_t)0X00000003)
#define GPIO_PB10_PF_COMP1_OUT                    ((uint32_t)0X00000004)
#define GPIO_PB10_PF_TIMG6_C0                     ((uint32_t)0X00000005)

/* IOMUX_PINCM28[PF] Bits */
#define GPIO_PB11_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB11_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB11_PF_TIMG0_C1                     ((uint32_t)0X00000002)
#define GPIO_PB11_PF_TIMG8_C1                     ((uint32_t)0X00000003)
#define GPIO_PB11_PF_SYSCTL_CLK_OUT               ((uint32_t)0X00000004)
#define GPIO_PB11_PF_TIMG6_C1                     ((uint32_t)0X00000005)

/* IOMUX_PINCM29[PF] Bits */
#define GPIO_PB12_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB12_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB12_PF_UART3_TX                     ((uint32_t)0X00000002)
#define GPIO_PB12_PF_TIMA0_C2                     ((uint32_t)0X00000003)
#define GPIO_PB12_PF_TIMA_FAULT1                  ((uint32_t)0X00000004)
#define GPIO_PB12_PF_TIMA0_C1                     ((uint32_t)0X00000005)

/* IOMUX_PINCM30[PF] Bits */
#define GPIO_PB13_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB13_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB13_PF_UART3_RX                     ((uint32_t)0X00000002)
#define GPIO_PB13_PF_TIMA0_C3                     ((uint32_t)0X00000003)
#define GPIO_PB13_PF_TIMG12_C0                    ((uint32_t)0X00000004)
#define GPIO_PB13_PF_TIMA0_C1_CMPL                ((uint32_t)0X00000005)

/* IOMUX_PINCM31[PF] Bits */
#define GPIO_PB14_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB14_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB14_PF_SPI1_CS3_CD_POCI3            ((uint32_t)0X00000002)
#define GPIO_PB14_PF_SPI1_POCI                    ((uint32_t)0X00000003)
#define GPIO_PB14_PF_SPI0_CS3_CD_POCI3            ((uint32_t)0X00000004)
#define GPIO_PB14_PF_TIMG12_C1                    ((uint32_t)0X00000005)
#define GPIO_PB14_PF_TIMG8_IDX                    ((uint32_t)0X00000006)
#define GPIO_PB14_PF_TIMA0_C0                     ((uint32_t)0X00000007)

/* IOMUX_PINCM32[PF] Bits */
#define GPIO_PB15_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB15_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB15_PF_UART2_TX                     ((uint32_t)0X00000002)
#define GPIO_PB15_PF_SPI1_PICO                    ((uint32_t)0X00000003)
#define GPIO_PB15_PF_UART3_CTS                    ((uint32_t)0X00000004)
#define GPIO_PB15_PF_TIMG8_C0                     ((uint32_t)0X00000005)
#define GPIO_PB15_PF_TIMG7_C0                     ((uint32_t)0X00000006)

/* IOMUX_PINCM33[PF] Bits */
#define GPIO_PB16_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB16_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB16_PF_UART2_RX                     ((uint32_t)0X00000002)
#define GPIO_PB16_PF_SPI1_SCLK                    ((uint32_t)0X00000003)
#define GPIO_PB16_PF_UART3_RTS                    ((uint32_t)0X00000004)
#define GPIO_PB16_PF_TIMG8_C1                     ((uint32_t)0X00000005)
#define GPIO_PB16_PF_TIMG7_C1                     ((uint32_t)0X00000006)

/* IOMUX_PINCM34[PF] Bits */
#define GPIO_PA12_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA12_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA12_PF_UART3_CTS                    ((uint32_t)0X00000002)
#define GPIO_PA12_PF_SPI0_SCLK                    ((uint32_t)0X00000003)
#define GPIO_PA12_PF_TIMG0_C0                     ((uint32_t)0X00000004)
#define GPIO_PA12_PF_CANFD0_CANTX                 ((uint32_t)0X00000005)
#define GPIO_PA12_PF_TIMA0_C3                     ((uint32_t)0X00000006)
#define GPIO_PA12_PF_SYSCTL_FCC_IN                ((uint32_t)0X00000007)

/* IOMUX_PINCM35[PF] Bits */
#define GPIO_PA13_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA13_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA13_PF_UART3_RTS                    ((uint32_t)0X00000002)
#define GPIO_PA13_PF_SPI0_POCI                    ((uint32_t)0X00000003)
#define GPIO_PA13_PF_UART3_RX                     ((uint32_t)0X00000004)
#define GPIO_PA13_PF_TIMG0_C1                     ((uint32_t)0X00000005)
#define GPIO_PA13_PF_CANFD0_CANRX                 ((uint32_t)0X00000006)
#define GPIO_PA13_PF_TIMA0_C3_CMPL                ((uint32_t)0X00000007)

/* IOMUX_PINCM36[PF] Bits */
#define GPIO_PA14_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA14_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA14_PF_UART0_CTS                    ((uint32_t)0X00000002)
#define GPIO_PA14_PF_SPI0_PICO                    ((uint32_t)0X00000003)
#define GPIO_PA14_PF_UART3_TX                     ((uint32_t)0X00000004)
#define GPIO_PA14_PF_TIMG12_C0                    ((uint32_t)0X00000005)
#define GPIO_PA14_PF_SYSCTL_CLK_OUT               ((uint32_t)0X00000006)

/* IOMUX_PINCM37[PF] Bits */
#define GPIO_PA15_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA15_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA15_PF_UART0_RTS                    ((uint32_t)0X00000002)
#define GPIO_PA15_PF_SPI1_CS2_POCI2               ((uint32_t)0X00000003)
#define GPIO_PA15_PF_I2C1_SCL                     ((uint32_t)0X00000004)
#define GPIO_PA15_PF_TIMA1_C0                     ((uint32_t)0X00000005)
#define GPIO_PA15_PF_TIMG8_IDX                    ((uint32_t)0X00000006)
#define GPIO_PA15_PF_TIMA1_C0_CMPL                ((uint32_t)0X00000007)
#define GPIO_PA15_PF_TIMA0_C2                     ((uint32_t)0X00000008)

/* IOMUX_PINCM38[PF] Bits */
#define GPIO_PA16_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA16_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA16_PF_COMP2_OUT                    ((uint32_t)0X00000002)
#define GPIO_PA16_PF_SPI1_POCI                    ((uint32_t)0X00000003)
#define GPIO_PA16_PF_I2C1_SDA                     ((uint32_t)0X00000004)
#define GPIO_PA16_PF_TIMA1_C1                     ((uint32_t)0X00000005)
#define GPIO_PA16_PF_TIMA1_C1_CMPL                ((uint32_t)0X00000006)
#define GPIO_PA16_PF_TIMA0_C2_CMPL                ((uint32_t)0X00000007)
#define GPIO_PA16_PF_SYSCTL_FCC_IN                ((uint32_t)0X00000008)

/* IOMUX_PINCM39[PF] Bits */
#define GPIO_PA17_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA17_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA17_PF_UART1_TX                     ((uint32_t)0X00000002)
#define GPIO_PA17_PF_SPI1_SCLK                    ((uint32_t)0X00000003)
#define GPIO_PA17_PF_I2C1_SCL                     ((uint32_t)0X00000004)
#define GPIO_PA17_PF_TIMA0_C3                     ((uint32_t)0X00000005)
#define GPIO_PA17_PF_TIMG7_C0                     ((uint32_t)0X00000006)
#define GPIO_PA17_PF_TIMA1_C0                     ((uint32_t)0X00000007)

/* IOMUX_PINCM40[PF] Bits */
#define GPIO_PA18_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA18_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA18_PF_UART1_RX                     ((uint32_t)0X00000002)
#define GPIO_PA18_PF_SPI1_PICO                    ((uint32_t)0X00000003)
#define GPIO_PA18_PF_I2C1_SDA                     ((uint32_t)0X00000004)
#define GPIO_PA18_PF_TIMA0_C3_CMPL                ((uint32_t)0X00000005)
#define GPIO_PA18_PF_TIMG7_C1                     ((uint32_t)0X00000006)
#define GPIO_PA18_PF_TIMA1_C1                     ((uint32_t)0X00000007)

/* IOMUX_PINCM41[PF] Bits */
#define GPIO_PA19_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA19_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA19_PF_DEBUGSS_SWDIO                ((uint32_t)0X00000002)

/* IOMUX_PINCM42[PF] Bits */
#define GPIO_PA20_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA20_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA20_PF_DEBUGSS_SWCLK                ((uint32_t)0X00000002)

/* IOMUX_PINCM43[PF] Bits */
#define GPIO_PB17_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB17_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB17_PF_UART2_TX                     ((uint32_t)0X00000002)
#define GPIO_PB17_PF_SPI0_PICO                    ((uint32_t)0X00000003)
#define GPIO_PB17_PF_SPI1_CS1_POCI1               ((uint32_t)0X00000004)
#define GPIO_PB17_PF_TIMA1_C0                     ((uint32_t)0X00000005)
#define GPIO_PB17_PF_TIMA0_C2                     ((uint32_t)0X00000006)

/* IOMUX_PINCM44[PF] Bits */
#define GPIO_PB18_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB18_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB18_PF_UART2_RX                     ((uint32_t)0X00000002)
#define GPIO_PB18_PF_SPI0_SCLK                    ((uint32_t)0X00000003)
#define GPIO_PB18_PF_SPI1_CS2_POCI2               ((uint32_t)0X00000004)
#define GPIO_PB18_PF_TIMA1_C1                     ((uint32_t)0X00000005)
#define GPIO_PB18_PF_TIMA0_C2_CMPL                ((uint32_t)0X00000006)

/* IOMUX_PINCM45[PF] Bits */
#define GPIO_PB19_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB19_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB19_PF_COMP2_OUT                    ((uint32_t)0X00000002)
#define GPIO_PB19_PF_SPI0_POCI                    ((uint32_t)0X00000003)
#define GPIO_PB19_PF_TIMG8_C1                     ((uint32_t)0X00000004)
#define GPIO_PB19_PF_UART0_CTS                    ((uint32_t)0X00000005)
#define GPIO_PB19_PF_TIMG7_C1                     ((uint32_t)0X00000006)

/* IOMUX_PINCM46[PF] Bits */
#define GPIO_PA21_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA21_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA21_PF_UART2_TX                     ((uint32_t)0X00000002)
#define GPIO_PA21_PF_TIMG8_C0                     ((uint32_t)0X00000003)
#define GPIO_PA21_PF_UART1_CTS                    ((uint32_t)0X00000004)
#define GPIO_PA21_PF_TIMA0_C0                     ((uint32_t)0X00000005)
#define GPIO_PA21_PF_TIMG6_C0                     ((uint32_t)0X00000006)

/* IOMUX_PINCM47[PF] Bits */
#define GPIO_PA22_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA22_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA22_PF_UART2_RX                     ((uint32_t)0X00000002)
#define GPIO_PA22_PF_TIMG8_C1                     ((uint32_t)0X00000003)
#define GPIO_PA22_PF_UART1_RTS                    ((uint32_t)0X00000004)
#define GPIO_PA22_PF_TIMA0_C1                     ((uint32_t)0X00000005)
#define GPIO_PA22_PF_SYSCTL_CLK_OUT               ((uint32_t)0X00000006)
#define GPIO_PA22_PF_TIMA0_C0_CMPL                ((uint32_t)0X00000007)
#define GPIO_PA22_PF_TIMG6_C1                     ((uint32_t)0X00000008)

/* IOMUX_PINCM48[PF] Bits */
#define GPIO_PB20_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB20_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB20_PF_SPI0_CS2_POCI2               ((uint32_t)0X00000002)
#define GPIO_PB20_PF_SPI1_CS0                     ((uint32_t)0X00000003)
#define GPIO_PB20_PF_TIMA0_C2                     ((uint32_t)0X00000004)
#define GPIO_PB20_PF_TIMG12_C0                    ((uint32_t)0X00000005)
#define GPIO_PB20_PF_TIMA_FAULT1                  ((uint32_t)0X00000006)
#define GPIO_PB20_PF_TIMA0_C1                     ((uint32_t)0X00000007)
#define GPIO_PB20_PF_TIMA1_C1_CMPL                ((uint32_t)0X00000008)

/* IOMUX_PINCM49[PF] Bits */
#define GPIO_PB21_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB21_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB21_PF_SPI1_POCI                    ((uint32_t)0X00000002)
#define GPIO_PB21_PF_TIMG8_C0                     ((uint32_t)0X00000003)

/* IOMUX_PINCM50[PF] Bits */
#define GPIO_PB22_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB22_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB22_PF_SPI1_PICO                    ((uint32_t)0X00000002)
#define GPIO_PB22_PF_TIMG8_C1                     ((uint32_t)0X00000003)

/* IOMUX_PINCM51[PF] Bits */
#define GPIO_PB23_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB23_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB23_PF_SPI1_SCLK                    ((uint32_t)0X00000002)
#define GPIO_PB23_PF_COMP0_OUT                    ((uint32_t)0X00000003)
#define GPIO_PB23_PF_TIMA_FAULT0                  ((uint32_t)0X00000004)

/* IOMUX_PINCM52[PF] Bits */
#define GPIO_PB24_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB24_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB24_PF_SPI0_CS3_CD_POCI3            ((uint32_t)0X00000002)
#define GPIO_PB24_PF_SPI0_CS1_POCI1               ((uint32_t)0X00000003)
#define GPIO_PB24_PF_TIMA0_C3                     ((uint32_t)0X00000004)
#define GPIO_PB24_PF_TIMG12_C1                    ((uint32_t)0X00000005)
#define GPIO_PB24_PF_TIMA0_C1_CMPL                ((uint32_t)0X00000006)
#define GPIO_PB24_PF_TIMA1_C0_CMPL                ((uint32_t)0X00000007)

/* IOMUX_PINCM53[PF] Bits */
#define GPIO_PA23_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA23_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA23_PF_UART2_TX                     ((uint32_t)0X00000002)
#define GPIO_PA23_PF_SPI0_CS3_CD_POCI3            ((uint32_t)0X00000003)
#define GPIO_PA23_PF_TIMA0_C3                     ((uint32_t)0X00000004)
#define GPIO_PA23_PF_TIMG0_C0                     ((uint32_t)0X00000005)
#define GPIO_PA23_PF_UART3_CTS                    ((uint32_t)0X00000006)
#define GPIO_PA23_PF_TIMG7_C0                     ((uint32_t)0X00000007)
#define GPIO_PA23_PF_TIMG8_C0                     ((uint32_t)0X00000008)

/* IOMUX_PINCM54[PF] Bits */
#define GPIO_PA24_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA24_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA24_PF_UART2_RX                     ((uint32_t)0X00000002)
#define GPIO_PA24_PF_SPI0_CS2_POCI2               ((uint32_t)0X00000003)
#define GPIO_PA24_PF_TIMA0_C3_CMPL                ((uint32_t)0X00000004)
#define GPIO_PA24_PF_TIMG0_C1                     ((uint32_t)0X00000005)
#define GPIO_PA24_PF_UART3_RTS                    ((uint32_t)0X00000006)
#define GPIO_PA24_PF_TIMG7_C1                     ((uint32_t)0X00000007)
#define GPIO_PA24_PF_TIMA1_C1                     ((uint32_t)0X00000008)

/* IOMUX_PINCM55[PF] Bits */
#define GPIO_PA25_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA25_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA25_PF_UART3_RX                     ((uint32_t)0X00000002)
#define GPIO_PA25_PF_SPI1_CS3_CD_POCI3            ((uint32_t)0X00000003)
#define GPIO_PA25_PF_TIMG12_C1                    ((uint32_t)0X00000004)
#define GPIO_PA25_PF_TIMA0_C3                     ((uint32_t)0X00000005)
#define GPIO_PA25_PF_TIMA0_C1_CMPL                ((uint32_t)0X00000006)

/* IOMUX_PINCM56[PF] Bits */
#define GPIO_PB25_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB25_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB25_PF_UART0_CTS                    ((uint32_t)0X00000002)
#define GPIO_PB25_PF_SPI0_CS0                     ((uint32_t)0X00000003)
#define GPIO_PB25_PF_TIMA_FAULT2                  ((uint32_t)0X00000004)

/* IOMUX_PINCM57[PF] Bits */
#define GPIO_PB26_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB26_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB26_PF_UART0_RTS                    ((uint32_t)0X00000002)
#define GPIO_PB26_PF_SPI0_CS1_POCI1               ((uint32_t)0X00000003)
#define GPIO_PB26_PF_TIMA0_C3                     ((uint32_t)0X00000004)
#define GPIO_PB26_PF_TIMG6_C0                     ((uint32_t)0X00000005)
#define GPIO_PB26_PF_TIMA1_C0                     ((uint32_t)0X00000006)

/* IOMUX_PINCM58[PF] Bits */
#define GPIO_PB27_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PB27_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PB27_PF_COMP2_OUT                    ((uint32_t)0X00000002)
#define GPIO_PB27_PF_SPI1_CS1_POCI1               ((uint32_t)0X00000003)
#define GPIO_PB27_PF_TIMA0_C3_CMPL                ((uint32_t)0X00000004)
#define GPIO_PB27_PF_TIMG6_C1                     ((uint32_t)0X00000005)
#define GPIO_PB27_PF_TIMA1_C1                     ((uint32_t)0X00000006)

/* IOMUX_PINCM59[PF] Bits */
#define GPIO_PA26_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA26_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA26_PF_UART3_TX                     ((uint32_t)0X00000002)
#define GPIO_PA26_PF_SPI1_CS0                     ((uint32_t)0X00000003)
#define GPIO_PA26_PF_TIMG8_C0                     ((uint32_t)0X00000004)
#define GPIO_PA26_PF_TIMA_FAULT0                  ((uint32_t)0X00000005)
#define GPIO_PA26_PF_CANFD0_CANTX                 ((uint32_t)0X00000006)
#define GPIO_PA26_PF_TIMG7_C0                     ((uint32_t)0X00000007)

/* IOMUX_PINCM60[PF] Bits */
#define GPIO_PA27_PF_UNCONNECTED                  ((uint32_t)0X00000000)
#define GPIO_PA27_PF_DIO                          ((uint32_t)0X00000001)
#define GPIO_PA27_PF_RTC_RTC_OUT                  ((uint32_t)0X00000002)
#define GPIO_PA27_PF_SPI1_CS1_POCI1               ((uint32_t)0X00000003)
#define GPIO_PA27_PF_TIMG8_C1                     ((uint32_t)0X00000004)
#define GPIO_PA27_PF_TIMA_FAULT2                  ((uint32_t)0X00000005)
#define GPIO_PA27_PF_CANFD0_CANRX                 ((uint32_t)0X00000006)
#define GPIO_PA27_PF_TIMG7_C1                     ((uint32_t)0X00000007)
