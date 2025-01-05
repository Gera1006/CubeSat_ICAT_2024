cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(ms580314ba_project)

pico_sdk_init()

add_executable(ms580314b
    ms580314ba.c
)

target_link_libraries(ms580314ba pico_stdlib hardware_i2c)

pico_enable_stdio_usb(ms580314ba 1)
pico_enable_stdio_uart(ms580314ba 0)

pico_add_extra_outputs(ms580314ba)
