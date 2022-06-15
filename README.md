# chipicopwn
![chipicopwn-logo](./CHIPICOPWN.BMP)

[Bootloader exploit for Google Nest Hub (2nd Gen) (elaine)](https://fredericb.info/2022/06/breaking-secure-boot-on-google-nest-hub-2nd-gen-to-run-ubuntu.html)

## requirements
- Google Nest Hub (2nd Gen)
- Raspberry Pi Pico
- Powered USB hub or USB Y cable
- [pico-sdk](https://github.com/raspberrypi/pico-sdk) (see [Getting Started guide](https://rptl.io/pico-get-started) for installation instructions)

## supported version
- [factory firmware (2020/12) - U-Boot 2019.01-gbfc19012ea-dirty (Dec 11 2020 - 04:19:32 )](https://github.com/frederic/chipicopwn/tree/main)
- [factory firmware (2022/01, 2022/02) - U-Boot 2019.01-g9542d3593d-dirty (May 21 2021 - 20:52:42 )](https://github.com/frederic/chipicopwn/tree/fw-2022_01)

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

## usage

1. Prepare USB flash disk [as described in *elaine-bootimg*](https://github.com/frederic/elaine-bootimg)
2. Remove the lid underneath the Nest Hub base to expose USB port
3. Connect the Raspberry Pico to Nest Hub (through powered-hub or Y-cable because the USB port does not provide power)
4. Hold Volume Down + Volume Up + Mute buttons while powering on the Nest Hub
5. Once CHIPICOPWN logo appears on screen, replace the Raspberry Pico with USB flash drive

## license
- [Logo CHIPICOPWN](./CHIPICOPWN.BMP) : [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/) - created by [HotPot.ai](https://hotpot.ai/s/art-maker/328/yAUpI4GK9kpwlksMAXlQqzEbplOV)