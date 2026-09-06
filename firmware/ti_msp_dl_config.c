/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_UART_Main_backupConfig gUART_HC_05Backup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_PWM_BUZZER_init();
    SYSCFG_DL_UART_0_init();
    SYSCFG_DL_UART_HC_05_init();
    SYSCFG_DL_SYSTICK_init();
    /* Ensure backup structures have no valid state */

	gUART_HC_05Backup.backupRdy 	= false;

}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_UART_Main_saveConfiguration(UART_HC_05_INST, &gUART_HC_05Backup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_UART_Main_restoreConfiguration(UART_HC_05_INST, &gUART_HC_05Backup);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerG_reset(PWM_BUZZER_INST);
    DL_UART_Main_reset(UART_0_INST);
    DL_UART_Main_reset(UART_HC_05_INST);


    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerG_enablePower(PWM_BUZZER_INST);
    DL_UART_Main_enablePower(UART_0_INST);
    DL_UART_Main_enablePower(UART_HC_05_INST);

    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_BUZZER_C0_IOMUX,GPIO_PWM_BUZZER_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_BUZZER_C0_PORT, GPIO_PWM_BUZZER_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_BUZZER_C1_IOMUX,GPIO_PWM_BUZZER_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_BUZZER_C1_PORT, GPIO_PWM_BUZZER_C1_PIN);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_0_IOMUX_TX, GPIO_UART_0_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_0_IOMUX_RX, GPIO_UART_0_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_HC_05_IOMUX_TX, GPIO_UART_HC_05_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_HC_05_IOMUX_RX, GPIO_UART_HC_05_IOMUX_RX_FUNC);

    DL_GPIO_initDigitalOutput(DHT11_DATA_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_HC_05_STATE_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_SCL_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_SDA_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_OLED_SCL_OLED_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_OLED_SDA_OLED_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_OLED_RES_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_OLED_DC_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_OLED_CS_IOMUX);

    DL_GPIO_initDigitalInputFeatures(GPIO_KEY_LEFT_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_KEY_RIGHT_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_KEY_ENTER_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_KEY_ESC_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(GPIO_LED_PA31_IOMUX);

    DL_GPIO_clearPins(GPIOA, GPIO_LED_PA31_PIN);
    DL_GPIO_setPins(GPIOA, DHT11_DATA_PIN |
		GPIO_SCL_PIN |
		GPIO_SDA_PIN |
		GPIO_OLED_SCL_OLED_PIN |
		GPIO_OLED_SDA_OLED_PIN |
		GPIO_OLED_RES_PIN |
		GPIO_OLED_DC_PIN |
		GPIO_OLED_CS_PIN);
    DL_GPIO_enableOutput(GPIOA, DHT11_DATA_PIN |
		GPIO_SCL_PIN |
		GPIO_SDA_PIN |
		GPIO_OLED_SCL_OLED_PIN |
		GPIO_OLED_SDA_OLED_PIN |
		GPIO_OLED_RES_PIN |
		GPIO_OLED_DC_PIN |
		GPIO_OLED_CS_PIN |
		GPIO_LED_PA31_PIN);

}



SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
	/* Set default configuration */
	DL_SYSCTL_disableHFXT();
	DL_SYSCTL_disableSYSPLL();

}


/*
 * Timer clock configuration to be sourced by  / 8 (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   4000000 Hz = 4000000 Hz / (8 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gPWM_BUZZERClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 0U
};

static const DL_TimerG_PWMConfig gPWM_BUZZERConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 5000,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_BUZZER_init(void) {

    DL_TimerG_setClockConfig(
        PWM_BUZZER_INST, (DL_TimerG_ClockConfig *) &gPWM_BUZZERClockConfig);

    DL_TimerG_initPWMMode(
        PWM_BUZZER_INST, (DL_TimerG_PWMConfig *) &gPWM_BUZZERConfig);

    DL_TimerG_setCaptureCompareValue(PWM_BUZZER_INST, 2500, DL_TIMER_CC_0_INDEX);
    DL_TimerG_setCaptureCompareOutCtl(PWM_BUZZER_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_BUZZER_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptureCompareValue(PWM_BUZZER_INST, 2500, DL_TIMER_CC_1_INDEX);
    DL_TimerG_setCaptureCompareOutCtl(PWM_BUZZER_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_BUZZER_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_enableClock(PWM_BUZZER_INST);


    
    DL_TimerG_setCCPDirection(PWM_BUZZER_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );

}



static const DL_UART_Main_ClockConfig gUART_0ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_0Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void)
{
    DL_UART_Main_setClockConfig(UART_0_INST, (DL_UART_Main_ClockConfig *) &gUART_0ClockConfig);

    DL_UART_Main_init(UART_0_INST, (DL_UART_Main_Config *) &gUART_0Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 9600
     *  Actual baud rate: 9600.24
     */
    DL_UART_Main_setOversampling(UART_0_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_0_INST, UART_0_IBRD_32_MHZ_9600_BAUD, UART_0_FBRD_32_MHZ_9600_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_0_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);


    DL_UART_Main_enable(UART_0_INST);
}

static const DL_UART_Main_ClockConfig gUART_HC_05ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_HC_05Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_HC_05_init(void)
{
    DL_UART_Main_setClockConfig(UART_HC_05_INST, (DL_UART_Main_ClockConfig *) &gUART_HC_05ClockConfig);

    DL_UART_Main_init(UART_HC_05_INST, (DL_UART_Main_Config *) &gUART_HC_05Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 9600
     *  Actual baud rate: 9600.24
     */
    DL_UART_Main_setOversampling(UART_HC_05_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_HC_05_INST, UART_HC_05_IBRD_32_MHZ_9600_BAUD, UART_HC_05_FBRD_32_MHZ_9600_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_HC_05_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);


    DL_UART_Main_enable(UART_HC_05_INST);
}

SYSCONFIG_WEAK void SYSCFG_DL_SYSTICK_init(void)
{
    /* Initialize the period to 1.00 μs */
    DL_SYSTICK_init(32);
    /* Enable the SysTick and start counting */
    DL_SYSTICK_enable();
}

