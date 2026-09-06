# BLE 传感器面板

单页 `index.html`。用 Web Bluetooth 订阅 BLE UART 通知，解析固件发出的 `BMP:` / `DHT:` / `LUX:` 文本。

## 运行

1. Chrome 或 Edge。
2. 用本地静态服务打开本目录（`localhost`）或 HTTPS。直接 `file://` 通常没有 Web Bluetooth。
3. 系统蓝牙先配对名为 `HC-05` 的模块。
4. 点击「扫描并连接蓝牙设备」。

## UUID

| 角色 | UUID |
| --- | --- |
| 服务 | `0000ffe0-0000-1000-8000-00805f9b34fb` |
| 通知特征 | `0000ffe1-0000-1000-8000-00805f9b34fb` |

只按广播名 `HC-05` 过滤，不绑定 MAC。若模块名不同，改 `EXPECTED_DEVICE_NAME`。

## 协议

与 `firmware/empty.c` 的 `sprintf` 一致。湿度字段拼写是固件里的 `Humidty`（缺 e），网页按这个匹配，不要“修正”正则除非同时改固件。

经典蓝牙 SPP 的 HC-05 **不能**被浏览器直连，见 `docs/adr/0001-hc05-uart-telemetry.md`。
