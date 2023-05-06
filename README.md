# Firmware for checking hand soldering (手実装の確認用 Firmware)

Firmware that tells you the change of each GPIO like `A1: H` on UART when you connect each IO and GND.
This allows you to check if each IO is soldered as expected after implementation.

Built with PlatformIO, verified build on Ubuntu AMD64 machine.

The built image can be found in [./release/](./release/).

各 IO と GND を繋ぐと、UART で `A1: H` というように各 GPIO の変化を教えてくれるファームウェア。
これで実装後に各 IO が期待通りに実装されているかどうかを確認できる。

PlatformIO で構築。Ubuntu AMD64 マシンにてビルドを確認済み。

ビルド済みイメージは [./release/](./release/) にあります。

## Supported MCU (対応 MCU)

- [STM32F103C8](stm32f103c8) (TX: A9)
- [STM32G030F6](stm32g030f6) (TX: B3)
- [ESP32](esp32) (TX: TXD0)
- [CH32V203C8T6](ch32v203c8t6) (TX: A9)
- [CH32V003F4P6](ch32v003f4p6) (TX: D5)

For RP2040 with USB CDC (USB CDC を使った RP2040 用はこちら) -> https://github.com/74th/rp2040-dev-board/tree/main/rp2040-io-tester

## License

MIT

- CH32V main file: WCH https://github.com/openwch/ch32v003/blob/main/C%2B%2B/Use%20MRS%20Create%20C%2B%2B%20project-example/CH32V003F4P6/User/main.cpp
- STM32F103 main file: STMicroelectronics
