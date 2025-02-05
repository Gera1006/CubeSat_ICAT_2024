cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(dht22_project)

pico_sdk_init()

add_executable(dht22
    dht22_config.c
    dht22_ejemplo.c
)

target_link_libraries(dht22 pico_stdlib)

pico_enable_stdio_usb(dht22 1)
pico_enable_stdio_uart(dht22 0)

pico_add_extra_outputs(dht22)