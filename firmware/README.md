# Firmware

TI MSPM0G3507 nortos 超级循环。应用入口是仓库里的 `empty.c`（SDK 空工程留下的文件名，不是空程序）。

## 依赖

- MSPM0 SDK **1.30.00.03**
- Keil MDK-Lite 5.39 + ARMClang 6.21（实际编过的路径）
- Pack：`TexasInstruments.MSPM0G1X0X_G3X0X_DFP.1.3.1`
- 环境变量 `MSPM0_SDK_INSTALL_DIR`

DriverLib 静态库由 Keil 工程从 SDK 引用：

```
%MSPM0_SDK_INSTALL_DIR%\source\ti\driverlib\lib\keil\m0p\mspm0g1x0x_g3x0x\driverlib.a
```

预构建步骤调用 `%MSPM0_SDK_INSTALL_DIR%\tools\keil\syscfg.bat`。

## 源文件

| 文件 | 作用 |
| --- | --- |
| `empty.c` | 页面状态机、报警、HC-05 三段发送 |
| `empty.syscfg` | 引脚与外设，SysConfig 输入 |
| `ti_msp_dl_config.*` | SysConfig 输出，禁止手改 |
| `board.c` / `board.h` | 时钟、SysTick 延时、UART0 printf |
| `BSP/bsp_bmp180.*` | BMP180 + 软件 I2C |
| `BSP/bsp_gy30.*` | BH1750，复用上述 I2C |
| `BSP/dht11.*` | DHT11，约 1 s 读一次 |
| `BSP/OLED/` | SSD1306 软件 SPI、字库 |
| `BSP/bsp_key.*` | 四键 20 ms 消抖 |
| `BSP/bsp_bluetooth.*` | UART3 9600 发送 |
| `BSP/png.*` | 开机动画 `Showvideo()` |
| `prebuilt/env-monitor.hex` | 已验证镜像 |

## 主循环节拍

`delay_ms(10)`。DHT11 每 1 s；BMP180 与 BH1750 在同一条软件 I2C 上交替，间隔 200 ms。报警翻转 50 ms。透传每 100 ms 发一段，三轮一个周期。

## GCC / IAR / TIClang

这三个目录是 SDK 模板。它们的 makefile 只编 `empty.c`，没有 BSP，不能得到完整固件。留下来只为 SysConfig / 链接脚本参考。真要命令行构建，需要把 `BSP/*.c` 和 `BSP/OLED/oled.c` 加进 `OBJECTS`。

## 内存

Flash 128 KB，SRAM 32 KB。
