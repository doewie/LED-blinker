cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(led-blinker C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(led-blinker
    led_blinker.c
)

pico_enable_stdio_usb(led-blinker 1)
pico_enable_stdio_uart(led-blinker 0)

pico_add_extra_outputs(led-blinker)

target_link_libraries(led-blinker pico_stdlib hardware_i2c)