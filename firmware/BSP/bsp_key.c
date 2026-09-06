#include "bsp_key.h"
#include "stdio.h"
#include "board.h"

void Key_Init(void)
{
    DL_GPIO_enablePower(GPIO_KEY_PORT);
    
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
}

Key_State Key_Scan(void)
{
    static uint8_t key_pressed = 0;
    Key_State result = KEY_NONE;

    uint32_t pin_state = DL_GPIO_readPins(GPIO_KEY_PORT,
        GPIO_KEY_LEFT_PIN | GPIO_KEY_RIGHT_PIN | GPIO_KEY_ENTER_PIN | GPIO_KEY_ESC_PIN);

    if (pin_state != 0 && key_pressed == 0)
    {
        delay_ms(20); 
        

        pin_state = DL_GPIO_readPins(GPIO_KEY_PORT,
            GPIO_KEY_LEFT_PIN | GPIO_KEY_RIGHT_PIN | GPIO_KEY_ENTER_PIN | GPIO_KEY_ESC_PIN);

        if (pin_state != 0)
        {
            key_pressed = 1;
            if (pin_state & GPIO_KEY_LEFT_PIN)   result = KEY_LEFT_PRESSED;
            else if (pin_state & GPIO_KEY_RIGHT_PIN)  result = KEY_RIGHT_PRESSED;
            else if (pin_state & GPIO_KEY_ENTER_PIN)  result = KEY_ENTER_PRESSED;
            else if (pin_state & GPIO_KEY_ESC_PIN)    result = KEY_ESC_PRESSED;
        }
    }
    else if (pin_state == 0 && key_pressed == 1)
    {
        key_pressed = 0;
    }

    return result;
}

void Key_Deinit(void) {
    DL_GPIO_enableHiZ(GPIO_KEY_LEFT_IOMUX);
    DL_GPIO_enableHiZ(GPIO_KEY_RIGHT_IOMUX);
    DL_GPIO_enableHiZ(GPIO_KEY_ENTER_IOMUX);
    DL_GPIO_enableHiZ(GPIO_KEY_ESC_IOMUX);
}
