/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM_BUZZER */
#define PWM_BUZZER_INST                                                    TIMG0
#define PWM_BUZZER_INST_IRQHandler                              TIMG0_IRQHandler
#define PWM_BUZZER_INST_INT_IRQN                                (TIMG0_INT_IRQn)
#define PWM_BUZZER_INST_CLK_FREQ                                         4000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_BUZZER_C0_PORT                                            GPIOA
#define GPIO_PWM_BUZZER_C0_PIN                                    DL_GPIO_PIN_23
#define GPIO_PWM_BUZZER_C0_IOMUX                                 (IOMUX_PINCM53)
#define GPIO_PWM_BUZZER_C0_IOMUX_FUNC                IOMUX_PINCM53_PF_TIMG0_CCP0
#define GPIO_PWM_BUZZER_C0_IDX                               DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_BUZZER_C1_PORT                                            GPIOA
#define GPIO_PWM_BUZZER_C1_PIN                                    DL_GPIO_PIN_13
#define GPIO_PWM_BUZZER_C1_IOMUX                                 (IOMUX_PINCM35)
#define GPIO_PWM_BUZZER_C1_IOMUX_FUNC                IOMUX_PINCM35_PF_TIMG0_CCP1
#define GPIO_PWM_BUZZER_C1_IDX                               DL_TIMER_CC_1_INDEX



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_32_MHZ_9600_BAUD                                       (208)
#define UART_0_FBRD_32_MHZ_9600_BAUD                                        (21)
/* Defines for UART_HC_05 */
#define UART_HC_05_INST                                                    UART3
#define UART_HC_05_INST_IRQHandler                              UART3_IRQHandler
#define UART_HC_05_INST_INT_IRQN                                  UART3_INT_IRQn
#define GPIO_UART_HC_05_RX_PORT                                            GPIOB
#define GPIO_UART_HC_05_TX_PORT                                            GPIOB
#define GPIO_UART_HC_05_RX_PIN                                     DL_GPIO_PIN_3
#define GPIO_UART_HC_05_TX_PIN                                     DL_GPIO_PIN_2
#define GPIO_UART_HC_05_IOMUX_RX                                 (IOMUX_PINCM16)
#define GPIO_UART_HC_05_IOMUX_TX                                 (IOMUX_PINCM15)
#define GPIO_UART_HC_05_IOMUX_RX_FUNC                  IOMUX_PINCM16_PF_UART3_RX
#define GPIO_UART_HC_05_IOMUX_TX_FUNC                  IOMUX_PINCM15_PF_UART3_TX
#define UART_HC_05_BAUD_RATE                                              (9600)
#define UART_HC_05_IBRD_32_MHZ_9600_BAUD                                   (208)
#define UART_HC_05_FBRD_32_MHZ_9600_BAUD                                    (21)





/* Port definition for Pin Group DHT11 */
#define DHT11_PORT                                                       (GPIOA)

/* Defines for DATA: GPIOA.9 with pinCMx 20 on package pin 55 */
#define DHT11_DATA_PIN                                           (DL_GPIO_PIN_9)
#define DHT11_DATA_IOMUX                                         (IOMUX_PINCM20)
/* Port definition for Pin Group GPIO_HC_05 */
#define GPIO_HC_05_PORT                                                  (GPIOA)

/* Defines for STATE: GPIOA.7 with pinCMx 14 on package pin 49 */
#define GPIO_HC_05_STATE_PIN                                     (DL_GPIO_PIN_7)
#define GPIO_HC_05_STATE_IOMUX                                   (IOMUX_PINCM14)
/* Port definition for Pin Group GPIO */
#define GPIO_PORT                                                        (GPIOA)

/* Defines for SCL: GPIOA.0 with pinCMx 1 on package pin 33 */
#define GPIO_SCL_PIN                                             (DL_GPIO_PIN_0)
#define GPIO_SCL_IOMUX                                            (IOMUX_PINCM1)
/* Defines for SDA: GPIOA.1 with pinCMx 2 on package pin 34 */
#define GPIO_SDA_PIN                                             (DL_GPIO_PIN_1)
#define GPIO_SDA_IOMUX                                            (IOMUX_PINCM2)
/* Port definition for Pin Group GPIO_OLED */
#define GPIO_OLED_PORT                                                   (GPIOA)

/* Defines for SCL_OLED: GPIOA.12 with pinCMx 34 on package pin 5 */
#define GPIO_OLED_SCL_OLED_PIN                                  (DL_GPIO_PIN_12)
#define GPIO_OLED_SCL_OLED_IOMUX                                 (IOMUX_PINCM34)
/* Defines for SDA_OLED: GPIOA.14 with pinCMx 36 on package pin 7 */
#define GPIO_OLED_SDA_OLED_PIN                                  (DL_GPIO_PIN_14)
#define GPIO_OLED_SDA_OLED_IOMUX                                 (IOMUX_PINCM36)
/* Defines for RES: GPIOA.21 with pinCMx 46 on package pin 17 */
#define GPIO_OLED_RES_PIN                                       (DL_GPIO_PIN_21)
#define GPIO_OLED_RES_IOMUX                                      (IOMUX_PINCM46)
/* Defines for DC: GPIOA.22 with pinCMx 47 on package pin 18 */
#define GPIO_OLED_DC_PIN                                        (DL_GPIO_PIN_22)
#define GPIO_OLED_DC_IOMUX                                       (IOMUX_PINCM47)
/* Defines for CS: GPIOA.2 with pinCMx 7 on package pin 42 */
#define GPIO_OLED_CS_PIN                                         (DL_GPIO_PIN_2)
#define GPIO_OLED_CS_IOMUX                                        (IOMUX_PINCM7)
/* Port definition for Pin Group GPIO_KEY */
#define GPIO_KEY_PORT                                                    (GPIOB)

/* Defines for LEFT: GPIOB.8 with pinCMx 25 on package pin 60 */
#define GPIO_KEY_LEFT_PIN                                        (DL_GPIO_PIN_8)
#define GPIO_KEY_LEFT_IOMUX                                      (IOMUX_PINCM25)
/* Defines for RIGHT: GPIOB.19 with pinCMx 45 on package pin 16 */
#define GPIO_KEY_RIGHT_PIN                                      (DL_GPIO_PIN_19)
#define GPIO_KEY_RIGHT_IOMUX                                     (IOMUX_PINCM45)
/* Defines for ENTER: GPIOB.20 with pinCMx 48 on package pin 19 */
#define GPIO_KEY_ENTER_PIN                                      (DL_GPIO_PIN_20)
#define GPIO_KEY_ENTER_IOMUX                                     (IOMUX_PINCM48)
/* Defines for ESC: GPIOB.24 with pinCMx 52 on package pin 23 */
#define GPIO_KEY_ESC_PIN                                        (DL_GPIO_PIN_24)
#define GPIO_KEY_ESC_IOMUX                                       (IOMUX_PINCM52)
/* Port definition for Pin Group GPIO_LED */
#define GPIO_LED_PORT                                                    (GPIOA)
/* Defines for PA31: GPIOA.31 with pinCMx 6 on package pin 39 */
#define GPIO_LED_PA31_PIN                                       (DL_GPIO_PIN_31)
#define GPIO_LED_PA31_IOMUX                                       (IOMUX_PINCM6)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_BUZZER_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_HC_05_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
