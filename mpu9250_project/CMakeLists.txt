cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(mpu9250_project)

pico_sdk_init()

add_executable(mpu9250
    mpu9250_config.c
    mpu9250_ejemplo.c
)

target_link_libraries(mpu9250 pico_stdlib hardware_i2c)

pico_enable_stdio_usb(mpu9250 1)
pico_enable_stdio_uart(mpu9250 0)

pico_add_extra_outputs(mpu9250)
