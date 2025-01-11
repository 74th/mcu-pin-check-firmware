# Firmware for checking hand soldering (手実装の確認用 Firmware)

Firmware that tells you the change of each GPIO like `A1: H` on UART when you connect each IO and GND.
This allows you to check if each IO is soldered as expected after implementation.

Built with PlatformIO, verified build on Ubuntu AMD64 machine.

The built image can be found in [./release/](./release/).

各 IO と GND を繋ぐと、UART で `A1: H` というように各 GPIO の変化を教えてくれるファームウェア。
これで実装後に各 IO が期待通りに実装されているかどうかを確認できる。

PlatformIO で構築（例外あり）。Ubuntu AMD64 マシンにてビルドを確認済み。

ビルド済みイメージは [./release/](./release/) にあります。

## Supported MCU (対応 MCU)

| MCU                                | UART      | Framework   | Build Platform |
| ---------------------------------- | --------- | ----------- | -------------- |
| STMicro [STM32F103C8](stm32f103c8) | TX: A9    | STM32Cube   | PlatformIO     |
| STMicro [STM32G030F6](stm32g030f6) | TX: B3    | STM32Cube   | PlatformIO     |
| STMicro [STM32G431](stm32g431)     | TX: B6    | STM32Cube   | PlatformIO     |
| Espressif [ESP32](esp32)           | TX: TXD0  | Arduino     | PlatformIO     |
| Espressif [ESP32-S3](esp32s3)      | TX: TXD0  | Arduino     | PlatformIO     |
| Espressif [ESP32-C3](esp32c3)      | TX: TXD0  | Arduino     | PlatformIO     |
| Espressif [ESP32-C6](esp32c6)      | USB CDC   | Arduino     | Arduino        |
| Espressif [ESP32-H2](esp32h2)      | USB CDC   | Arduino     | Arduino        |
| WCH [CH32V203C8T6](ch32v203c8t6)   | TX: A9    | WCH SDK     | PlatformIO     |
| WCH [CH32V003F4P6](ch32v003f4p6)   | TX: D5    | WCH SDK     | PlatformIO     |
| WCH [CH32V003F4P6](ch32v003f4p6)   | SWDIO log | ch32v003fun | Make           |
| WCH [CH32X035](ch32x035)           | TX: B10   | WCH SDK     | PlatformIO     |
| Raspbery Pi [RP2040](rp2040)       | USB CDC   | PickSDK     | cmake          |
| Raspbery Pi [RP2350](rp2350)       | USB CDC   | PickSDK     | cmake          |

## License

MIT

- CH32V main file: WCH https://github.com/openwch/ch32v003/blob/main/C%2B%2B/Use%20MRS%20Create%20C%2B%2B%20project-example/CH32V003F4P6/User/main.cpp
- STM32F103 main file: STMicroelectronics
