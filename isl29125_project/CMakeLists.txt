cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(isl29125_project)

pico_sdk_init()

add_executable(isl29125
    isl29125.c
)

target_link_libraries(isl29125 pico_stdlib hardware_i2c)

pico_enable_stdio_usb(isl29125 1)
pico_enable_stdio_uart(isl29125 0)

pico_add_extra_outputs(isl29125)
