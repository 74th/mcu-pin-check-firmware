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

| MCU                                | UART      | Framework   | Build Platform | firmware |
| ---------------------------------- | --------- | ----------- | -------------- | -------- |
| STMicro [STM32F103C8](stm32f103c8) | TX: A9    | STM32Cube   | PlatformIO     | [stm32f103c8.bin](./release/stm32f103c8.bin) |
| STMicro [STM32G030F6](stm32g030f6) | TX: B3    | STM32Cube   | PlatformIO     | [stm32g030f6.bin](./release/stm32g030f6.bin) |
| STMicro [STM32G431](stm32g431)     | TX: B6    | STM32Cube   | PlatformIO     | [stm32g431.bin](./release/stm32g431.bin) |
| Espressif [ESP32](esp32)           | TX: TXD0  | Arduino     | PlatformIO     | [esp32.bin](./release/esp32.bin)            |
| Espressif [ESP32-S3](esp32s3)      | TX: TXD0  | Arduino     | PlatformIO     | [esp32s3.bin](./release/esp32s3.bin)         |
| Espressif [ESP32-C3](esp32c3)      | TX: TXD0  | Arduino     | PlatformIO     | [esp32c3.bin](./release/esp32c3.bin)         |
| Espressif [ESP32-C6](esp32c6)      | USB CDC   | Arduino     | Arduino        | [esp32c6.bin](./release/esp32c6.bin)         |
| Espressif [ESP32-H2](esp32h2)      | USB CDC   | Arduino     | Arduino        | [esp32h2.bin](./release/esp32h2.bin)         |
| WCH [CH32V203C8T6](ch32v203c8t6)   | TX: A9    | WCH SDK     | PlatformIO     | [ch32v203c8t6.bin](./release/ch32v203c8t6.bin) |
| WCH [CH32V003F4P6](ch32v003f4p6)   | TX: D5    | WCH SDK     | PlatformIO     | [ch32v003f4p6-uart.bin](./release/ch32v003f4p6-uart.bin) |
| WCH [CH32V003F4P6](ch32v003f4p6)   | SDI log   | WCH SDK     | PlatformIO     | [ch32v003f4p6-sdi.bin](./release/ch32v003f4p6-sdi.bin) |
| WCH [CH32V003F4P6](ch32v003-swd)   | SWDIO log | ch32v003fun | Make           | [ch32v003_swdio-log.bin](./release/ch32v003_swdio-log.bin) |
| WCH [CH32X035](ch32x035)           | TX: B10   | WCH SDK     | PlatformIO     | [ch32x035.bin](./release/ch32x035.bin)       |
| Raspberry Pi [RP2040](rp2040)       | USB CDC   | Pico SDK     | cmake        | [rp2040.uf2](./release/rp2040.uf2)           |
| Raspberry Pi [RP2350](rp2350)       | USB CDC   | Pico SDK     | cmake        | [rp2350.uf2](./release/rp2350.uf2)           |

## How to write and use

### STMicro

WIP

### Espressif ESP32 Series

#### esptool.py

https://github.com/espressif/esptool

```
esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 115200 write_flash 0x10000 esp32.bin
```

#### espflash

https://github.com/esp-rs/espflash

```
espflash write-bin 0x10000 esp32.bin
```

### WCH

#### minichlink (via WCH-Link/E and swdio)

https://github.com/cnlohr/ch32v003fun/tree/master/minichlink

```
minichlink -w ./ch32v003f4p6-swdio-log.bin flash -b
```

show SWIO log

```
minichlink -T
```

#### wlink (via  WCH-Link/E and sdi)

https://github.com/ch32-rs/wlink

```
wlink flash --enable-sdi-print --watch-serial ./ch32v003f4p6-sdi.bin
```

#### wchisp (via USB Bootloader)

```
wchisp flash ./ch32v203c8t6.bin
```

### Raspberry Pi Pico Series

#### USB Driver

drag and drop `rp2040.uf2` to RPIBOOT

#### picotool

https://github.com/raspberrypi/picotool

```
picotool load ./rp2040.uf2

picotool reboot
```

## License

MIT

- CH32V main file: WCH https://github.com/openwch/ch32v003/blob/main/C%2B%2B/Use%20MRS%20Create%20C%2B%2B%20project-example/CH32V003F4P6/User/main.cpp
- STM32F103 main file: STMicroelectronics
