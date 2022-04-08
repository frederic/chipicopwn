cmake_minimum_required(VERSION 3.13)

set(PROJECT chipicopwn)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(${PROJECT})

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(${PROJECT})

target_sources(${PROJECT} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/msc_disk.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/usb_descriptors.c
        )

target_include_directories(${PROJECT} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(${PROJECT} pico_stdlib tinyusb_device tinyusb_board)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${PROJECT})