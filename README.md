# 手実装の確認用 Firmware

各 IO と GND を繋ぐと、UART で `A1: H` というように各 GPIO の変化を教えてくれるファームウェア。
これで実装後に各 IO が期待通りに実装されているかどうかを確認できる。

PlatformIO で構築。Ubuntu AMD64 マシンにてビルドを確認済み。

ビルド済みイメージは [./release/](./release/) にあります。

## 対応 MCU

- STM32F103C8
- CH32V203C8T6
- CH32V003F4P6

RP2040 用はこちら → https://github.com/74th/rp2040-dev-board/tree/main/rp2040-io-tester
