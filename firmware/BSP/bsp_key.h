#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include <stdint.h>
#include <stdbool.h>
#include "ti_msp_dl_config.h"  // 包含SysConfig生成的GPIO引脚定义

// ===================== 按键宏定义（直接调用系统配置）=====================
#define KEY_LEFT_PIN     GPIO_KEY_LEFT_PIN
#define KEY_RIGHT_PIN    GPIO_KEY_RIGHT_PIN
#define KEY_ENTER_PIN    GPIO_KEY_ENTER_PIN
#define KEY_ESC_PIN      GPIO_KEY_ESC_PIN
#define KEY_PORT         GPIO_KEY_PORT

// 按键电平读取（硬件：下拉电阻 → 按下=高电平1，松开=低电平0）
#define KEY_LEFT         DL_GPIO_readPins(KEY_PORT, KEY_LEFT_PIN)
#define KEY_RIGHT        DL_GPIO_readPins(KEY_PORT, KEY_RIGHT_PIN)
#define KEY_ENTER        DL_GPIO_readPins(KEY_PORT, KEY_ENTER_PIN)
#define KEY_ESC          DL_GPIO_readPins(KEY_PORT, KEY_ESC_PIN)

// ===================== 按键状态枚举 =====================
typedef enum {
    KEY_NONE = 0,        // 无按键按下
    KEY_LEFT_PRESSED,    // 左键按下
    KEY_RIGHT_PRESSED,   // 右键按下
    KEY_ENTER_PRESSED,   // 确认键按下
    KEY_ESC_PRESSED      // ESC键按下
} Key_State;

// ===================== 函数声明 =====================
void Key_Init(void);       // 按键初始化（下拉输入+消抖）
Key_State Key_Scan(void);  // 按键扫描（带20ms软件消抖）
void Key_Deinit(void);     // 按键反初始化（高阻态）

#endif
