# AGENTS.md

环境监测仪固件在 `firmware/`，网页在 `web/index.html`。用语见 `CONTEXT.md`。

## 构建

Keil 工程：`firmware/keil/empty_LP_MSPM0G3507_nortos_keil.uvprojx`。需要环境变量 `MSPM0_SDK_INSTALL_DIR` 指向 MSPM0 SDK 1.30.00.03。预编译镜像：`firmware/prebuilt/env-monitor.hex`。

## 配置

改引脚或 UART 只编辑 `firmware/empty.syscfg`，再用 SysConfig 生成 `ti_msp_dl_config.c` / `.h`。不要手改这两个生成文件。`firmware/keil/` 里不要再放一份旧的 `ti_msp_dl_config.*`。

## 源码地图

- `firmware/empty.c`：超级循环，页面、报警、三段式透传
- `firmware/BSP/`：传感器、按键、OLED、HC-05、开机动画
- `firmware/board.c`：`board_init`、`delay_us` / `delay_ms`、`printf` → UART0
- BMP180 与 BH1750 共享软件 I2C；DHT11 读数期间关中断

## 网页

`web/index.html` 按设备名 `HC-05` 过滤，UUID 为 FFE0/FFE1。不要写回模块 MAC 或配对 PIN。

## 编码与提交

C/H 用 UTF-8 LF。不要提交 `_local/`、Keil `Objects/`、`*.uvguix.*`、课程 Word/PPT、演示 MP4。
