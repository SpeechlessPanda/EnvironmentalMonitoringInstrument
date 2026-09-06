#include "board.h"
#include <stdio.h>
#include <string.h>
#include "bsp_bmp180.h"
#include "oled.h"
#include "DHT11.h"
#include "bsp_gy30.h"
#include "ti_msp_dl_config.h"
#include "bsp_key.h"
#include "bsp_bluetooth.h"
#include "ti_msp_dl_config.h"
#include "png.h"
      
typedef enum {
    PAGE_BARO = 0,
    PAGE_TEMP_HUMI,
    PAGE_LIGHT,
    PAGE_SETTING
} Page_t;

Page_t curr_page = PAGE_BARO;
volatile uint8_t pres_unit = 0;
volatile uint8_t alarm_mode = 0;
uint8_t set_item = 0;           // 当前选中的设置项（0=气压单位，1=温度单位）
uint8_t settings_edit_mode = 0; // 0=浏览模式（左右键切页面） 1=编辑模式（左右键选设置项）

uint32_t bmp_temp, bmp_pres;
int dht_temp, dht_humi;
uint32_t light_val;
char disp_buf[32];

char disp_buff[128];
uint32_t ble_tick = 0; // 蓝牙发送定时
uint8_t ble_send_step = 0;

Page_t last_page = PAGE_BARO; // 保存进入设置前的页面

volatile uint8_t  alarm_flag = 0;      // 报警标志 1=报警中 0=关闭
uint32_t alarm_tick = 0;            // 报警计时（非阻塞用）
uint8_t  alarm_state = 0;           // 报警状态 1=响/亮 0=停

void Sensor_Refresh_All(void);
void OLED_Show_Top_Nav(void);
void OLED_Show_Page(void);
void Buzzer_On(void);   // 蜂鸣器开启
void Buzzer_Off(void);  // 蜂鸣器关闭
void Led_On(void);
void Led_Off(void);

int main(void)
{
    board_init();
		// PWM初始化，默认关闭蜂鸣器
		SYSCFG_DL_init();
		DL_TimerG_startCounter(PWM_BUZZER_INST);
    Buzzer_Off();
		Led_Off();
	
    // 手动关闭UART0接收中断，避免board_init()中的配置干扰
    DL_UART_Main_disableInterrupt(UART_0_INST, DL_UART_MAIN_INTERRUPT_RX);
    NVIC_DisableIRQ(UART_0_INST_INT_IRQN);
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
	
    delay_ms(1000); // 等待系统稳定
    printf("SYSTEM = READY\r\n");
    // 等待传输完成，确保串口输出稳定
    while(DL_UART_isBusy(UART_0_INST));
	
    OLED_Init();
    OLED_Clear();
    OLED_ShowString(0, 16, (uint8_t *)"  SYSTEM READY", 16, 1);
    OLED_Refresh();
    delay_ms(1000);
		OLED_Clear();
		Showvideo();
    OLED_Clear();
    Key_Init();
    delay_ms(100);
    // 初始化所有传感器
    delay_ms(1000); // DHT11上电稳定时间
    BMP180_Get_param();
    delay_ms(100);
    GY30_Init();
    delay_ms(100);
		Bluetooth_Init();
    OLED_Show_Top_Nav();
    OLED_Refresh();
    while(1)
    {
        Key_State key = Key_Scan();

        if(key != KEY_NONE)
        {
            switch(key)
            {
                /* ---- 左键 ---- */
                case KEY_LEFT_PRESSED:
                    if (curr_page == PAGE_SETTING && settings_edit_mode)
                    {
                        /* 编辑模式：切换上一个设置项 */
                        set_item = (set_item - 1 + 2) % 2;
                    }
                    else
                    {
                        /* 浏览模式：切换上一个页面（首尾循环） */
                        settings_edit_mode = 0; // 离开设置页时退出编辑模式
                        if (curr_page == PAGE_BARO)
                            curr_page = PAGE_SETTING;
                        else
                            curr_page = curr_page - 1;
                    }
                    break;

                /* ---- 右键 ---- */
                case KEY_RIGHT_PRESSED:
										
                    if (curr_page == PAGE_SETTING && settings_edit_mode)
                    {
                        /* 编辑模式：切换下一个设置项 */
                        set_item = (set_item + 1) % 2;
                    }
                    else
                    {
                        /* 浏览模式：切换下一个页面（首尾循环） */
                        settings_edit_mode = 0; // 离开设置页时退出编辑模式
                        curr_page = (curr_page + 1) % 4;
                    }
                    break;

                /* ---- ENTER键 ---- */
                case KEY_ENTER_PRESSED:
                    if (curr_page == PAGE_SETTING && settings_edit_mode)
                    {
                        /* 编辑模式：切换单位 */
                        if (set_item == 0)
													{
                            pres_unit = !pres_unit;
													}
                        else if (set_item == 1)
												{
														alarm_mode = !alarm_mode;
												}
                    }
                    else if (curr_page == PAGE_SETTING && !settings_edit_mode)
                    {
                        /* 浏览模式下在设置页：进入编辑模式 */
                        settings_edit_mode = 1;
                        set_item = 0;
                    }
                    else
                    {
                        /* 其他页面：跳转到设置页（浏览模式） */
                        last_page = curr_page;
                        curr_page = PAGE_SETTING;
                        settings_edit_mode = 0;
                        set_item = 0;
                    }
                    break;

                /* ---- ESC键 ---- */
                case KEY_ESC_PRESSED:
                    if (curr_page == PAGE_SETTING && settings_edit_mode)
                    {
                        /* 编辑模式：退出编辑，回到浏览模式（留在设置页） */
                        settings_edit_mode = 0;
                    }
                    else
                    {
                        /* 浏览模式：返回首页 */
                        settings_edit_mode = 0;
                        curr_page = PAGE_BARO;
                    }
                    break;

                default: break;
            }

            // 页面切换时更新显示
            OLED_Clear();
            OLED_Show_Top_Nav();
						OLED_Show_Page();
            OLED_Refresh();
        }

        // 传感器数据刷新
        Sensor_Refresh_All();

				alarm_flag = 0; // 默认关闭报警
        switch(curr_page)
        {
            case PAGE_BARO:
                // 气压页：仅判断 BMP温度 > 35℃ 报警
                if(bmp_temp > 3500) alarm_flag = 1;
                break;

            case PAGE_TEMP_HUMI:
                // 温湿度页：DHT温度>35℃ OR 湿度>80% 报警
                if(dht_temp > 35 || dht_humi > 80) alarm_flag = 1;
                break;

            case PAGE_LIGHT:
                // 光强页：<50 lx OR >8000 lx 报警
                if( (light_val/100 < 50) || (light_val/100 > 8000) ) alarm_flag = 1;
                break;

            case PAGE_SETTING:
                // 设置页：不报警
                alarm_flag = 0;
                break;
        }

// ===================== 统一报警执行逻辑（响1s 停1s） =====================
        if(alarm_flag == 1)
        {
            alarm_tick++;
            if(alarm_tick >= 5) // 10ms×5 = 0.05秒
            {
                alarm_tick = 0;
                alarm_state = !alarm_state;
                if(alarm_mode == 0)
                {
										// 蜂鸣器报警
                    alarm_state ? Buzzer_On() : Buzzer_Off();
                }
                else
                {
                    // LED报警
                     alarm_state ? Led_On() : Led_Off();
                }
            }
        }
        else
        {
            // 报警关闭：复位 + 关闭蜂鸣器
            alarm_tick = 0;
            alarm_state = 0;
            Buzzer_Off();
						Led_Off();
        }
				// ===================== 3段式蓝牙发送（标题不拆分，无阻塞） =====================
				if(curr_page != PAGE_SETTING)
				{
						ble_tick++;
						if(ble_tick >= 10) 
						{
								ble_tick = 0;
								// 分3次发送，标题完整不拆分
								switch(ble_send_step)
								{
										case 0:
												// 第1段：BMP 完整数据（标题+温度+气压）
												sprintf(disp_buff,"BMP:\nTemp: %d.%02d C\nPress: %d.%02d kPa\n",
																bmp_temp/100, bmp_temp%100,
																bmp_pres/1000, (bmp_pres%1000)/10);
												BLE_send_String((uint8_t *)disp_buff);
												break;
										case 1:
												// 第2段：DHT 完整数据（标题+温度+湿度）
												sprintf(disp_buff,"DHT:\nTemp: %d C\nHumidty: %d %%\n",
																dht_temp, dht_humi);
												BLE_send_String((uint8_t *)disp_buff);
												break;
										case 2:
												// 第3段：LUX 完整数据（标题+光照）
												sprintf(disp_buff,"LUX:\nLight: %d lx\n",
																light_val/100);
												BLE_send_String((uint8_t *)disp_buff);
												break;
								}
								// 循环 0→1→2→0
								ble_send_step = (ble_send_step + 1) % 3;
						}
				}
        // 显示页面
        OLED_Show_Page();
        OLED_Refresh();

        delay_ms(10);
    }
}

// 传感器刷新函数
void Sensor_Refresh_All(void)
{
    static uint16_t main_counter = 0;
    static uint16_t dht_counter = 0;
    static uint8_t other_sensor_step = 0;

    main_counter++;
    if (main_counter < 10) // 每100ms执行一次
    {
        return;
    }
    main_counter = 0;
    dht_counter++;

    // DHT11每1秒读取一次
    if (dht_counter >= 10)
    {
        dht_counter = 0;
        unsigned int dht_result = DHT11_Read_Data();
        dht_temp = (int)Get_temperature();
        dht_humi = (int)Get_humidity();
    }

    // 其他传感器分时采集，不影响DHT11
    switch(other_sensor_step)
    {
        case 0:
            // 大气压传感器（每200ms更新一次）
            bmp_temp = BMP180_Get_Temperature() * 100;
            bmp_pres = BMP180_Get_Pressure();
            other_sensor_step = 1;
            break;

        case 1:
            // 光强传感器（每200ms更新一次）
            light_val = (uint32_t)(Multiple_read_BH1750() * 100);
            other_sensor_step = 0;
            break;
    }
}

void OLED_Show_Top_Nav(void)
{
    OLED_ShowString(0,   0, (uint8_t *)"ATMOS",  8, (curr_page==0)?0:1);
    OLED_ShowString(32,  0, (uint8_t *)"TEMP",    8, (curr_page==1)?0:1);
    OLED_ShowString(64,  0, (uint8_t *)"LIGHT",   8, (curr_page==2)?0:1);
    OLED_ShowString(96,  0, (uint8_t *)" SET",     8, (curr_page==3)?0:1);
}

void OLED_Show_Page(void)
{
    // 清除显示区域
    OLED_ShowString(0, 16, (uint8_t *)"                ", 16, 1);
    OLED_ShowString(0, 32, (uint8_t *)"                ", 16, 1);
    OLED_ShowString(0, 48, (uint8_t *)"                ", 16, 1);

    switch(curr_page)
    {
        case PAGE_BARO:
            // 大气压页面显示
						sprintf(disp_buf, "Temp: %d.%02d C", bmp_temp/100, bmp_temp%100);
						OLED_ShowString(0, 16, (uint8_t *)disp_buf, 16, 1);
				
            if(pres_unit == 0)
                sprintf(disp_buf, "Press: %d.%02d kPa", bmp_pres/1000, (bmp_pres%1000)/10);
            else
            {
                uint32_t atm_int = bmp_pres / 101325;
                uint32_t atm_dec = (bmp_pres % 101325) * 100 / 101325;
                sprintf(disp_buf, "Press: %d.%02d atm", atm_int, atm_dec);
            }
            OLED_ShowString(0, 32, (uint8_t *)disp_buf, 16, 1);
            break;

        case PAGE_TEMP_HUMI:
            // 温湿度页面显示
            sprintf(disp_buf, "Temp: %d C", dht_temp);
            OLED_ShowString(0, 16, (uint8_t *)disp_buf, 16, 1);
						
            sprintf(disp_buf, "Humidty: %d %%", dht_humi);
            OLED_ShowString(0, 32, (uint8_t *)disp_buf, 16, 1);
            break;

        case PAGE_LIGHT:
            // 光强页面显示
            sprintf(disp_buf, "Light: %d lx", light_val/100);
            OLED_ShowString(0, 16, (uint8_t *)disp_buf, 16, 1);
            break;

        case PAGE_SETTING:
            if(settings_edit_mode)
            {
                /* 编辑模式：显示>标记，ENTER切换单位，ESC退出 */
                sprintf(disp_buf, "%cPress: %s",
                        (set_item==0)?'>':' ', pres_unit?"atm":"kPa");
                OLED_ShowString(0, 16, (uint8_t *)disp_buf, 16, 1);

                sprintf(disp_buf, "%cMode: %s", 
												(set_item==1)?'>':' ', alarm_mode?"LED":"BUZZER");
                OLED_ShowString(0, 32, (uint8_t *)disp_buf, 16, 1);
                OLED_ShowString(0, 48, (uint8_t *)"ENTER=SW ESC=X", 16, 1);
            }
            else
            {
                /* 浏览模式：无标记，提示按ENTER进入编辑 */
                sprintf(disp_buf, " Press: %s", pres_unit?"atm":"kPa");
                OLED_ShowString(0, 16, (uint8_t *)disp_buf, 16, 1);

                sprintf(disp_buf, " Mode: %s", alarm_mode?"LED":"BUZZER");
                OLED_ShowString(0, 32, (uint8_t *)disp_buf, 16, 1);

                OLED_ShowString(0, 48, (uint8_t *)"ENTER=EDIT", 16, 1);
            }
            break;
    }
}
void Buzzer_On(void)
{
    // 开启PWM定时器 + 设置占空比发声
    DL_TimerG_startCounter(PWM_BUZZER_INST);
    DL_TimerG_setCaptureCompareValue(PWM_BUZZER_INST, 2500, GPIO_PWM_BUZZER_C1_IDX);
}

void Buzzer_Off(void)
{
    // 1. 占空比设为0
    DL_TimerG_setCaptureCompareValue(PWM_BUZZER_INST, 0, GPIO_PWM_BUZZER_C1_IDX);
    // 2. 停止PWM定时器
    DL_TimerG_stopCounter(PWM_BUZZER_INST);
    // 3. 强制拉低引脚
    DL_GPIO_clearPins(GPIO_PWM_BUZZER_C1_PORT, GPIO_PWM_BUZZER_C1_PIN);
}
void Led_On(void){DL_GPIO_setPins(GPIO_LED_PORT, GPIO_LED_PA31_PIN);}
void Led_Off(void){DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_PA31_PIN);}
