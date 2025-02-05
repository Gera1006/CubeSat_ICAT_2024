cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(veml6030_project)

pico_sdk_init()

add_executable(veml6030
    veml6030_config.c
    veml6030_ejemplo.c
)

target_link_libraries(veml6030 pico_stdlib hardware_i2c)

pico_enable_stdio_usb(veml6030 1)
pico_enable_stdio_uart(veml6030 0)

pico_add_extra_outputs(veml6030)
