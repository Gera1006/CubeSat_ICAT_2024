cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(maxm10s_project)

pico_sdk_init()

add_executable(maxm10s
    maxm10s.c
)

target_link_libraries(maxm10s pico_stdlib hardware_uart)

pico_enable_stdio_usb(maxm10s 1)
pico_enable_stdio_uart(maxm10s 0)

pico_add_extra_outputs(maxm10s)
