#!/bin/bash
set -xe
esptool.py --chip esp32c6 merge_bin \
  -o esp32c6.bin \
  --flash_mode keep \
  --flash_freq keep \
  --flash_size keep \
  0x0000  build/esp32c6.ino.bootloader.bin \
  0x8000  build/esp32c6.ino.partitions.bin \
  0xe000  $HOME/.arduino15/packages/esp32/hardware/esp32/3.0.0-alpha3/tools/partitions/boot_app0.bin \
  0x10000 build/esp32c6.ino.bin

# python3 "/home/nnyn/.arduino15/packages/esp32/tools/esptool_py/4.6/esptool.py" --chip esp32c6 --port "/dev/ttyACM1" --baud 921600  --before default_reset --after hard_reset write_flash  -z --flash_mode keep --flash_freq keep --flash_size keep 0x0 "/home/nnyn/ghq/github.com/74th/mcu-pin-check-firmware/esp32c6/build/esp32c6.ino.bootloader.bin" 0x8000 "/home/nnyn/ghq/github.com/74th/mcu-pin-check-firmware/esp32c6/build/esp32c6.ino.partitions.bin" 0xe000 "/home/nnyn/.arduino15/packages/esp32/hardware/esp32/3.0.0-alpha3/tools/partitions/boot_app0.bin" 0x10000 "/home/nnyn/ghq/github.com/74th/mcu-pin-check-firmware/esp32c6/build/esp32c6.ino.bin"