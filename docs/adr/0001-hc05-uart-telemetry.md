# HC-05 UART 透传，网页走 BLE GATT

固件只把 ASCII 行写到 UART3。HC-05 在经典蓝牙上是 SPP 串口。浏览器 Web Bluetooth 只能连 BLE GATT，不能打开 SPP。

网页因此订阅常见 BLE 透传服务 `FFE0/FFE1`，并按设备名 `HC-05` 过滤。这要求实际用的模块是「BLE UART 透传」而不是纯经典 SPP；若只有经典 HC-05，需要额外的 SPP↔BLE 桥，网页无法直连。

没有在页面里写模块 MAC：MAC 是个人硬件标识，换一块板就会失效，也不该出现在公开仓库。
