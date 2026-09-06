# 环境监测仪

手持环境监测装置：MCU 周期采集三类传感器，在 OLED 上分页展示，超阈值报警，并把 ASCII 遥测经蓝牙透传到网页。

## Language

**环境监测仪**:
本仓库的产品。BMP180、DHT11、BH1750 加 OLED、按键、蜂鸣器、LED、HC-05。
_Avoid_: 气象站（内部笔记曾用，不是对外名称）

**页面**:
OLED 一次只显示一个 `Page_t`：`PAGE_BARO`（顶栏 ATMOS）、`PAGE_TEMP_HUMI`（TEMP）、`PAGE_LIGHT`（LIGHT）、`PAGE_SETTING`（SET）。
_Avoid_: 窗口, 菜单项（设置页里的选项叫设置项）

**设置项**:
设置页里当前高亮的可改字段。`set_item == 0` 气压单位，`set_item == 1` 报警方式（蜂鸣器 / LED）。
_Avoid_: 温度单位（源码旧注释，实际切的是报警方式）

**报警**:
当前页传感器越过阈值时，`alarm_flag` 置位，按 `alarm_mode` 驱动蜂鸣器或 LED。设置页不报警。
_Avoid_: 中断（报警在主循环里轮询，不是 NVIC 报警中断）

**透传**:
HC-05 把 MCU UART3 上的 ASCII 原样送到对端，固件不组 BLE GATT 包。
_Avoid_: 蓝牙协议栈, BLE 通知（那是网页端对 FFE1 的叫法）

**软件 I2C**:
`bsp_bmp180.c` 里 bit-bang 的 PA0/PA1 总线，BH1750 复用同一套起停字节函数。
_Avoid_: I2C0 外设（本工程没有用 MSPM0 硬件 I2C）

**盾板**:
插在地猛星 M0 底板排针上的自制传感器/按键/OLED 板，对应 `hardware/PCB.eprj2`。
_Avoid_: 底板（底板是地猛星 M0 模块本身）
