# chipicopwn
![chipicopwn-logo](./CHIPICOPWN.BMP)

Bootloader exploit for Google Nest Hub (2nd gen)

## requirements
- Google Nest Hub (2nd Gen) - bootloader version *U-Boot 2019.01-gbfc19012ea-dirty (Dec 11 2020 - 04:19:32 )*
- Raspberry Pi Pico
- Powered USB hub
- [pico-sdk](https://github.com/raspberrypi/pico-sdk) (see [Getting Started guide](https://rptl.io/pico-get-started) for installation instructions)

## build
```shell
export PICO_SDK_PATH=<pico-sdk>/
mkdir build
cd build
cmake ..
make
```

## flash
- Boot Pico in bootloader mode (hold down BOOTSEL button)
- Copy file *chipicopwn.uf2* to Pico flash drive

## license
- [Logo CHIPICOPWN](./CHIPICOPWN.BMP) : [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/) - created by [HotPot.ai](https://hotpot.ai/s/art-maker/328/yAUpI4GK9kpwlksMAXlQqzEbplOV)